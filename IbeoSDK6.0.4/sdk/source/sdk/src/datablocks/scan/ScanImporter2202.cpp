//==============================================================================
//!\file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date March 23, 2018
//------------------------------------------------------------------------------
//==============================================================================
//\!TODO: The ScanImporter2002 is incomplete. The function to calculate scan-point locations for curved mirrors
//\!TODO: are not implemented yet. At the moment the coordinates are always linear. Will be added in the future.

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/ScanImporter2202.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/ScanPointIn2202.hpp>
#include <ibeo/common/sdk/ScannerProperties.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/Math.hpp>
//==============================================================================
namespace {
using C  = ibeo::common::sdk::Scan;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Scan2202>;
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
class IbeoLux;
class IbeoTrackingBox;
class IbeoScala;
class IbeoEcu;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoLux>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoTrackingBox>::getInstance().registerImporter(
            ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
                ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
                    registeredImporterInitial)))));
//==============================================================================

void ScanImporter2202::toGeneralPointFlags(ScanPoint& scanPoint, const uint8_t flags)
{
    uint16_t generalFlags{0};

    if ((flags & static_cast<uint8_t>(ScanPointIn2202::Flags::Transparent))
        == static_cast<uint8_t>(ScanPointIn2202::Flags::Transparent))
    {
        generalFlags = generalFlags | static_cast<uint16_t>(ScanPoint::Flags::Transparent);
    }

    if ((flags & static_cast<uint8_t>(ScanPointIn2202::Flags::Dirt))
        == static_cast<uint8_t>(ScanPointIn2202::Flags::Dirt))
    {
        generalFlags = generalFlags | static_cast<uint16_t>(ScanPoint::Flags::Dirt);
    }

    if ((flags & static_cast<uint8_t>(ScanPointIn2202::Flags::Ground))
        == static_cast<uint8_t>(ScanPointIn2202::Flags::Ground))
    {
        generalFlags = generalFlags | static_cast<uint16_t>(ScanPoint::Flags::Ground);
    }

    if ((flags & static_cast<uint8_t>(ScanPointIn2202::Flags::Rain))
        == static_cast<uint8_t>(ScanPointIn2202::Flags::Rain))
    {
        generalFlags = generalFlags | static_cast<uint16_t>(ScanPoint::Flags::Rain);
    }

    scanPoint.setFlags(generalFlags);
}

//==============================================================================

float ScanImporter2202::getVerticalAngle(const bool isRearMirrorSide, const uint8_t layer, const float vBeamDivergence)
{
    const uint8_t numberLayers
        = ScannerProperties::getScannerProperties(static_cast<uint16_t>(ScannerType::Lux)).getNbOfLayers();
    assert(numberLayers % 2 == 0);
    const float effMirrorTilt   = 0.0F; //TODO: Add here the banana function for curved mirrors
    const float mirrorDirection = isRearMirrorSide ? 1.0F : -1.0F;
    const float layerOffset     = (0.5F * (numberLayers - 1.0F) - layer) * vBeamDivergence;
    const float vAngle          = layerOffset + mirrorDirection * 2.F * effMirrorTilt;
    return vAngle;
}

//==============================================================================

void ScanImporter2202::convertScanPoint2202(const ibeo::common::sdk::ScanPointIn2202& scanPoint2202,
                                            ibeo::common::sdk::ScanPoint& scanPoint,
                                            const bool isRearMirrorSide,
                                            const float degreesPerTick)
{
    const float vBeamDivergence
        = ScannerProperties::getScannerProperties(static_cast<uint16_t>(ScannerType::Lux)).getVerticalBeamDivergence();
    const float distAccuracy
        = ScannerProperties::getScannerProperties(static_cast<uint16_t>(ScannerType::Lux)).getDistanceAccuracy();
    const uint8_t layer = scanPoint2202.getLayer();
    const float dist    = scanPoint2202.getDistanceCm() * distAccuracy;
    const float hAngle  = scanPoint2202.getHorizontalAngleTicks() * degreesPerTick * deg2radf;
    const float vAngle  = getVerticalAngle(isRearMirrorSide, layer, vBeamDivergence);
    const float diag    = dist * std::cos(vAngle);

    scanPoint.setPosX(diag * std::cos(hAngle));
    scanPoint.setPosY(diag * std::sin(hAngle));
    scanPoint.setPosZ(dist * -std::sin(vAngle));
    scanPoint.setLayer(scanPoint2202.getLayer());
    scanPoint.setEcho(scanPoint2202.getEcho());
    scanPoint.setEpw(scanPoint2202.getEchoPulseWidthCm() * distAccuracy);
    toGeneralPointFlags(scanPoint, scanPoint2202.getFlags());
}

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Scan2202>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return std::streamsize(3 * sizeof(uint16_t) + 2 * sizeof(NTPTime))
           + std::streamsize(1 * sizeof(uint16_t) + 3 * sizeof(int16_t))
           + std::streamsize(container->m_scanPoints.size()) * ScanPointIn2202::getSerializedSize_static()
           + std::streamsize(3 * sizeof(int16_t) + 3 * sizeof(uint16_t) + sizeof(uint16_t));
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Scan2202>::deserialize(std::istream& is,
                                                             DataContainerBase& c,
                                                             const IbeoDataHeader& dh) const
{
    C* container{nullptr};
    try
    {
        container = &dynamic_cast<C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(is.tellg());

    ScannerInfo scannerInfo;

    container->m_scanPoints.clear();
    readLE(is, container->m_scanNumber);

    uint16_t scannerStatus;
    readLE(is, scannerStatus);
    scannerInfo.setScannerStatus(static_cast<uint32_t>(scannerStatus)); // lower bits are same

    uint16_t syncPhaseOffset;
    readLE(is, syncPhaseOffset);

    readLE(is, container->m_scanStartTime);
    NTPTime endTime;
    readLE(is, endTime);
    uint32_t endTimeDiff       = static_cast<uint32_t>(endTime - container->m_scanStartTime); //Working atm
    container->m_endTimeOffset = endTimeDiff;

    int16_t angleTicksPerRotation;
    readLE(is, angleTicksPerRotation);

    constexpr float degreePerRotation = 360.0F;
    //    const float ticksPerDegree        = static_cast<float>(angleTicksPerRotation) / degreePerRotation;
    const float degreesPerTick = degreePerRotation / static_cast<float>(angleTicksPerRotation);

    int16_t startAngle;
    readLE(is, startAngle);
    scannerInfo.setStartAngle(startAngle * degreesPerTick * deg2radf);
    int16_t endAngle;
    readLE(is, endAngle);
    scannerInfo.setEndAngle(endAngle * degreesPerTick * deg2radf);

    uint16_t nbScanPts;
    readLE(is, nbScanPts);

    int16_t yawAngleTicks;
    readLE(is, yawAngleTicks);
    scannerInfo.setYawAngle(yawAngleTicks * degreesPerTick * deg2radf);

    int16_t pitchAngleTicks;
    readLE(is, pitchAngleTicks);
    scannerInfo.setPitchAngle(pitchAngleTicks * degreesPerTick * deg2radf);

    int16_t rollAngleTicks;
    readLE(is, rollAngleTicks);
    scannerInfo.setRollAngle(rollAngleTicks * degreesPerTick * deg2radf);

    int16_t posX;
    readLE(is, posX);
    scannerInfo.setOffsetX(posX / 100.0F); // [m]

    int16_t posY;
    readLE(is, posY);
    scannerInfo.setOffsetY(posY / 100.0F); // [m]

    int16_t posZ;
    readLE(is, posZ);
    scannerInfo.setOffsetZ(posZ / 100.0F); // [m]
    container->m_scannerInfos.push_back(scannerInfo);

    uint16_t flags;
    readLE(is, flags);

    container->m_flags = static_cast<uint32_t>(flags);

    bool isRearMirrorSide = container->isRearMirrorSide();

    ScanPointIn2202 scanPoint2202;
    container->m_scanPoints.resize(nbScanPts);

    for (auto& scanPoint : container->m_scanPoints)
    {
        scanPoint2202.deserialize(is);
        convertScanPoint2202(scanPoint2202, scanPoint, isRearMirrorSide, degreesPerTick);
        scanPoint.setDeviceId(dh.getDeviceId());
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

// for test
bool operator==(const Scan& lhs, const Scan2202& rhs)
{
    if (lhs.getStartTimestamp() != rhs.getStartTimestamp())
    {
        return false;
    }
    auto offset = static_cast<uint32_t>(rhs.getEndTimestamp() - rhs.getStartTimestamp());
    if (lhs.getEndTimeOffset() != offset)
    {
        return false;
    }
    if (lhs.getFlags() != rhs.getFlags())
    {
        return false;
    }

    if (lhs.getScanNumber() != rhs.getScanNumber())
    {
        return false;
    }

    auto status = lhs.getScannerInfos().front(); // there is only one info for imported 2202
    if (static_cast<uint16_t>(status.getScannerStatus()) != rhs.getScannerStatus())
    {
        return false;
    }
    constexpr float degreePerRotation = 360.0F;
    // const float ticksPerDegree        = static_cast<float>(rhs.getAngleTicksPerRotation()) / degreePerRotation;
    const float degreesPerTick = degreePerRotation / static_cast<float>(rhs.getAngleTicksPerRotation());
    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(status.getStartAngle(),
                                                rhs.getStartAngleTicks() * degreesPerTick * deg2radf)
        || !ibeo::common::sdk::fuzzyFloatEqualT<7>(status.getEndAngle(),
                                                   rhs.getEndAngleTicks() * degreesPerTick * deg2radf))
    {
        return false;
    }
    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(status.getYawAngle(),
                                                rhs.getMountingPositionYawAngleTicks() * degreesPerTick * deg2radf)
        || !ibeo::common::sdk::fuzzyFloatEqualT<7>(status.getPitchAngle(),
                                                   rhs.getMountingPositionPitchAngleTicks() * degreesPerTick * deg2radf)
        || !ibeo::common::sdk::fuzzyFloatEqualT<7>(status.getRollAngle(),
                                                   rhs.getMountingPositionRollAngleTicks() * degreesPerTick * deg2radf))
    {
        return false;
    }
    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(status.getOffsetX(), rhs.getMountingPositionCmX() / 100.0F)
        || !ibeo::common::sdk::fuzzyFloatEqualT<7>(status.getOffsetY(), rhs.getMountingPositionCmY() / 100.0F)
        || !ibeo::common::sdk::fuzzyFloatEqualT<7>(status.getOffsetZ(), rhs.getMountingPositionCmZ() / 100.0F))
    {
        return false;
    }
    if (lhs.getNumberOfScanPoints() != static_cast<uint32_t>(rhs.getNumberOfScanPoints()))
    {
        return false;
    }

    // finally check all the scanpoints
    for (Scan::ScanPointVector::size_type i = 0; i < lhs.getNumberOfScanPoints(); i++)
    {
        const auto lhspoint = lhs.getScanPoints()[i];
        const auto rhspoint = rhs.getScanPoints()[i];
        ScanPoint rhsconvertedpoint;
        Importer<Scan, DataTypeId::DataType_Scan2202>::convertScanPoint2202(
            rhspoint, rhsconvertedpoint, rhs.isRearMirrorSide(), degreesPerTick);
        if (lhspoint.getPositionX() != rhsconvertedpoint.getPositionX()
            || lhspoint.getPositionY() != rhsconvertedpoint.getPositionY()
            || lhspoint.getPositionZ() != rhsconvertedpoint.getPositionZ())
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
