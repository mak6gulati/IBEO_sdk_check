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
//!\date Jan 22, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301SerializedSize6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301Importer6301.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/scan/ScannerInfo.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::DeviceStatus6301;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_DeviceStatus6301>;
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
class IbeoEcu;
class IbeoScala;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
            registeredImporterInitial)));

//==============================================================================

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_DeviceStatus6301>::getSerializedSize(const DataContainerBase& c) const
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

    return DeviceStatus6301SerializedSize6301::getSerializedSize(*container);
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6301>::deserialize(std::istream& is,
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

    if (!deserialize(is, container->m_serialNumberOfScanner))
    {
        return false;
    }
    uint8_t st;
    ibeo::common::sdk::readLE(is, st);
    container->m_scannerType = ScannerType(st);
    ibeo::common::sdk::readLE(is, container->m_reserved0);

    if (!deserialize(is, container->m_fpgaVersion))
    {
        return false;
    }
    if (!deserialize(is, container->m_dspVersion))
    {
        return false;
    }
    if (!deserialize(is, container->m_hostVersion))
    {
        return false;
    }

    ibeo::common::sdk::readLE(is, container->m_fpgaModusRegister);
    ibeo::common::sdk::readLE(is, container->m_reserved1);

    ibeo::common::sdk::readLE(is, container->m_sensorTemperature);
    ibeo::common::sdk::readLE(is, container->m_frequency);
    ibeo::common::sdk::readLE(is, container->m_apdTableVoltage);
    for (unsigned int s = 0; s < C::nbOfApdSectors; ++s)
    {
        ibeo::common::sdk::readLE(is, container->m_adaptiveApdVoltage[s]);
    }
    ibeo::common::sdk::readLE(is, container->m_minApdVoltageOffset);
    ibeo::common::sdk::readLE(is, container->m_maxApdVoltageOffset);

    ibeo::common::sdk::readLE(is, container->m_reserved2);
    ibeo::common::sdk::readLE(is, container->m_reserved3);

    ibeo::common::sdk::readLE(is, container->m_noiseMeasurementThreshold);
    ibeo::common::sdk::readLE(is, container->m_referenceNoise);
    for (unsigned int s = 0; s < C::nbOfApdSectors; ++s)
    {
        ibeo::common::sdk::readLE(is, container->m_actualNoise[s]);
    }

    for (unsigned int r = 0; r < C::nbOfReservedA; ++r)
    {
        ibeo::common::sdk::readLE(is, container->m_reservedA[r]);
    }

    return (!is.fail()) && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6301>::deserialize(std::istream& is, SerialNumberIn6301& sn)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readLE(is, sn.m_month);
    ibeo::common::sdk::readLE(is, sn.m_year);
    ibeo::common::sdk::readLE(is, sn.m_cnt1);
    ibeo::common::sdk::readLE(is, sn.m_cnt0);
    ibeo::common::sdk::readLE(is, sn.m_null);

    return (!is.fail())
           && ((streamposToInt64(is.tellg()) - startPos) == DeviceStatus6301SerializedSize6301::getSerializedSize(sn));
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6301>::deserialize(std::istream& is, Version448In6301& version)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readLE(is, version.m_version);
    ibeo::common::sdk::readLE(is, version.m_year);
    ibeo::common::sdk::readLE(is, version.m_month);
    ibeo::common::sdk::readLE(is, version.m_day);
    ibeo::common::sdk::readLE(is, version.m_hour);
    ibeo::common::sdk::readLE(is, version.m_minute);

    return (!is.fail())
           && ((streamposToInt64(is.tellg()) - startPos)
               == DeviceStatus6301SerializedSize6301::getSerializedSize(version));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
