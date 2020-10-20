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
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303Exporter6303.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::DeviceStatus6303;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_DeviceStatus6303>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_DeviceStatus6303>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    const int64_t startPos = streamposToInt64(os.tellp());

    if (!serialize(os, container->serialNumberOfScanner))
    {
        return false;
    }

    writeBE(os, container->scannerType);
    writeBE(os, container->deviceId);

    if (!serialize(os, container->fpgaVersion))
    {
        return false;
    }
    if (!serialize(os, container->hostVersion))
    {
        return false;
    }

    writeBE(os, container->fpgaStatusRegister);
    writeBE(os, container->fpgaOperationRegister);

    writeBE(os, container->scanPeriod);

    writeBE(os, container->sensorTemperatureApd0);
    writeBE(os, container->sensorTemperatureApd1);
    writeBE(os, container->minApdVoltageOffset);
    writeBE(os, container->maxApdVoltageOffset);

    writeBE(os, container->noiseMeasurementThreshold);
    writeBE(os, container->referenceNoise);

    const uint16_t nbOfContentsEnries = uint16_t(container->m_contentEntries.size());
    writeBE(os, nbOfContentsEnries);

    C::ContentDescrVector::const_iterator contentsEntryIter = container->m_contentEntries.begin();
    for (; contentsEntryIter != container->m_contentEntries.end(); ++contentsEntryIter)
    {
        if (!contentsEntryIter->serialize(os))
        {
            return false;
        } // if
    } // for contentsEntryIter

    return (!os.fail()) && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6303>::serialize(std::ostream& os, const SerialNumberIn6303& sn)
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, sn.m_month);
    ibeo::common::sdk::writeBE(os, sn.m_year);
    ibeo::common::sdk::writeBE(os, sn.m_cnt1);
    ibeo::common::sdk::writeBE(os, sn.m_cnt0);
    ibeo::common::sdk::writeBE(os, sn.m_null);

    return (!os.fail())
           && ((streamposToInt64(os.tellp()) - startPos) == DeviceStatus6303SerializedSize6303::getSerializedSize(sn));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6303>::serialize(std::ostream& os, const Version448In6303& version)
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, version.m_version);
    ibeo::common::sdk::writeBE(os, version.m_year);
    ibeo::common::sdk::writeBE(os, version.m_month);
    ibeo::common::sdk::writeBE(os, version.m_day);
    ibeo::common::sdk::writeBE(os, version.m_hour);
    ibeo::common::sdk::writeBE(os, version.m_minute);

    return (!os.fail())
           && ((streamposToInt64(os.tellp()) - startPos)
               == DeviceStatus6303SerializedSize6303::getSerializedSize(version));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
