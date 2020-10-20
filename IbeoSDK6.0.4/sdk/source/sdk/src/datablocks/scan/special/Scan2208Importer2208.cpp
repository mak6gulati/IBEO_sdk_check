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
//!\date Jan 14, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2208Importer2208.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::Scan2208;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Scan2208>;
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
class IbeoMiniLux;
class IbeoLuxHr;
class IbeoScala;
class IbeoEcu;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoMiniLux>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoLuxHr>::getInstance().registerImporter(
            ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
                ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
                    registeredImporterInitial)))));

//==============================================================================

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Scan2208>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize sz = 52;
    for (const auto& subscan : container->getSubScans())
    {
        sz += std::streamsize(subscan.getSerializedSize());
    }
    return sz;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Scan2208>::deserialize(std::istream& is,
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

    container->setDataHeader(dh);

    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, container->m_scanNumber);

    uint16_t tmp;
    readBE(is, tmp);
    container->m_scannerType = ScannerType(tmp);

    readBE(is, container->m_scannerStatus);
    readBE(is, container->m_angleTicksPerRotation);
    readBE(is, container->m_processingFlags);
    readBE(is, container->m_mountingPosition);

    for (auto& threshold : container->m_thresholds)
    {
        readBE(is, threshold);
    }

    for (auto& reserved : container->m_reserved)
    {
        readBE(is, reserved);
    }

    readBE(is, container->m_deviceId);

    uint8_t nbOfSubScans;
    readBE(is, nbOfSubScans);
    container->m_subScans.resize(nbOfSubScans);
    for (auto& subscan : container->getSubScans())
    {
        if (!subscan.deserialize(is))
        {
            return false;
        }
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
