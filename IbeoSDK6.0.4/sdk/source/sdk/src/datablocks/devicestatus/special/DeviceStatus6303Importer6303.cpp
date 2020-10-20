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

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303SerializedSize6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303Importer6303.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::DeviceStatus6303;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_DeviceStatus6303>;
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

std::streamsize Importer<C, DataTypeId::DataType_DeviceStatus6303>::getSerializedSize(const DataContainerBase& c) const
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

    return DeviceStatus6303SerializedSize6303::getSerializedSize(*container);
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6303>::deserialize(std::istream& is,
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

    container->clear();

    if (!deserialize(is, container->serialNumberOfScanner))
    {
        return false;
    }

    readBE(is, container->scannerType);
    readBE(is, container->deviceId);

    if (!deserialize(is, container->fpgaVersion))
    {
        return false;
    }
    if (!deserialize(is, container->hostVersion))
    {
        return false;
    }

    readBE(is, container->fpgaStatusRegister);
    readBE(is, container->fpgaOperationRegister);

    readBE(is, container->scanPeriod);

    readBE(is, container->sensorTemperatureApd0);
    readBE(is, container->sensorTemperatureApd1);
    readBE(is, container->minApdVoltageOffset);
    readBE(is, container->maxApdVoltageOffset);

    readBE(is, container->noiseMeasurementThreshold);
    readBE(is, container->referenceNoise);

    uint16_t nbOfVariableContentEntries = 0;
    readBE(is, nbOfVariableContentEntries);

    bool contentsAreOk    = true;
    bool allContentsAdded = true;
    C::ContentDescrDeserializer cdd;
    for (int i = 0; i < nbOfVariableContentEntries; ++i)
    {
        if (!cdd.deserialize(is))
        {
            contentsAreOk = false;
        }
        if (!container->addContent(cdd))
        {
            allContentsAdded = false;
        }
    } // for i

    return (!is.fail()) && contentsAreOk && allContentsAdded
           && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6303>::deserialize(std::istream& is, SerialNumberIn6303& sn)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, sn.m_month);
    ibeo::common::sdk::readBE(is, sn.m_year);
    ibeo::common::sdk::readBE(is, sn.m_cnt1);
    ibeo::common::sdk::readBE(is, sn.m_cnt0);
    ibeo::common::sdk::readBE(is, sn.m_null);

    return (!is.fail())
           && ((streamposToInt64(is.tellg()) - startPos) == DeviceStatus6303SerializedSize6303::getSerializedSize(sn));
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6303>::deserialize(std::istream& is, Version448In6303& version)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, version.m_version);
    ibeo::common::sdk::readBE(is, version.m_year);
    ibeo::common::sdk::readBE(is, version.m_month);
    ibeo::common::sdk::readBE(is, version.m_day);
    ibeo::common::sdk::readBE(is, version.m_hour);
    ibeo::common::sdk::readBE(is, version.m_minute);

    return (!is.fail())
           && ((streamposToInt64(is.tellg()) - startPos)
               == DeviceStatus6303SerializedSize6303::getSerializedSize(version));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
