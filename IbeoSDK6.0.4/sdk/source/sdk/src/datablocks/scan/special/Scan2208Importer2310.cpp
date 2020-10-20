//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Jan 14, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2208Importer2310.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2310Importer2310.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::Scan2208;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Scan2310>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
// Specializations for RegisteredImporter
//==============================================================================

//generate link between data-type-id/importer and importer create function <dtid, ImpHash> ==> Imp::create

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

//registering ... (create map)
//add all device that can receive any datatype that can be imported to GeneralDataTypeContainer
class IdcFile;
class IbeoScala;
class IbeoEcu;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial)));

//==============================================================================

bool Importer<C, DataTypeId::DataType_Scan2310>::to2208Scan(Scan2208& scan, const Scan2310& sfrdContainer)
{
    scan.setScanNumber(sfrdContainer.getReserved00());
    scan.setScannerType(ScannerType::ScalaB2);
    scan.setScannerStatus(0); // TODO
    scan.setAngleTicksPerRotation(11520);
    scan.setProcessingFlags(0); // TODO
    scan.setMountingPosition(Scan2208::MountingPositionIn2208());
    // TODO: threshold 0 - 6
    scan.setDeviceId(uint8_t(sfrdContainer.getHeader().getDeviceId()));
    Scan2208::SubScanVector& subScans = scan.getSubScans();
    subScans.resize(1);
    SubScanIn2208& sub = subScans[0];

    sub.setStartScanTimestamp(sfrdContainer.getScanStartTime());
    sub.setEndScanTimestamp(sfrdContainer.getScanEndTime());
    sub.setStartScanAngle(int16_t(72.5 * 32)); // TODO
    sub.setEndScanAngle(int16_t(-72.5 * 32)); // TODO
    sub.setFlags(0); // TODO
    sub.setMirrorSide(uint8_t(sfrdContainer.getTrailer().getMirrorSide())); // TODO
    sub.setMirrorTilt(uint16_t(0.4 * 500)); // TODO
    sub.getScanPoints().clear();
    sub.getScanPoints().resize(sfrdContainer.getPoints().size()); // TODO

    std::vector<ScanPointIn2310>::const_iterator srcPtIter = sfrdContainer.getPoints().begin();
    SubScanIn2208::PointVector::iterator targetPtIter      = sub.getScanPoints().begin();
    for (; targetPtIter != sub.getScanPoints().end(); ++targetPtIter, ++srcPtIter)
    {
        // TODO all
        targetPtIter->setThresholdId(0);
        targetPtIter->setEchoId(srcPtIter->getEchoId());
        targetPtIter->setReserved(0);
        targetPtIter->setLayerId(srcPtIter->getChannelId());
        targetPtIter->setFlags(to2208Flags(uint16_t(((srcPtIter->getFlagsHigh()) << 8) | (srcPtIter->getFlagsLow()))));
        targetPtIter->setHorizontalAngle(srcPtIter->getAngle());
        targetPtIter->setRadialDistance(srcPtIter->getRadialDistance());
        targetPtIter->setEchoPulseWidth(srcPtIter->getEchoPulseWidth());
        targetPtIter->setPfValue(0);
    }
    return true;
}

//==============================================================================

uint16_t Importer<C, DataTypeId::DataType_Scan2310>::to2208Flags(const uint16_t rawFlags)
{
    // Transparent
    // Rain
    // Ground
    // Dirt
    // HighTresholdH1
    // ...
    // HighTresholdH2
    uint16_t flags2208 = rawFlags & 0x009f; // first 5 flags and flag 7 have the same meaning

    if ((rawFlags & static_cast<uint16_t>(ScanPointBaseIn2310::RawFlags::NearRange))
        == static_cast<uint16_t>(ScanPointBaseIn2310::RawFlags::NearRange))
        setFlag(flags2208, uint16_t(ScanPointIn2208::Flags::NearRange));

    if ((rawFlags & static_cast<uint16_t>(ScanPointBaseIn2310::RawFlags::Noise))
        == static_cast<uint16_t>(ScanPointBaseIn2310::RawFlags::Noise))
        setFlag(flags2208, uint16_t(ScanPointIn2208::Flags::Noise));

    // unmapped: CandidateInvalid
    // unmapped: RainStep1Done
    // unmapped: RainStep2Done

    // unmapped: GroundStep1Done
    // unmapped: GroundStep2Done
    // unmapped: BlueValidCaculated
    // unmapped: Flushed

    return flags2208;
}

//==============================================================================

void Importer<C, DataTypeId::DataType_Scan2310>::setFlag(uint16_t& flagsToBeModified, const uint16_t flagToSet)
{
    flagsToBeModified = uint16_t(flagsToBeModified | flagToSet);
}

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Scan2310>::getSerializedSize(const DataContainerBase& container) const
{
    // no check for container type here

    return m_sfrdImporter.getSerializedSize(container);
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Scan2310>::deserialize(std::istream& is,
                                                             DataContainerBase& c,
                                                             const IbeoDataHeader& dh) const
{
    C* scan2208Container{nullptr};
    try
    {
        scan2208Container = &dynamic_cast<C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    Scan2310 sfrdContainer;
    if (m_sfrdImporter.deserialize(is, sfrdContainer, dh))
    {
        return to2208Scan(*scan2208Container, sfrdContainer);
    }
    else
    {
        return false;
    }
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
