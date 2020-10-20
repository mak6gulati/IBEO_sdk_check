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
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301Exporter6301.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::DeviceStatus6301;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_DeviceStatus6301>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_DeviceStatus6301>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    if (!serialize(os, container->m_serialNumberOfScanner))
    {
        return false;
    }
    uint8_t st = static_cast<uint8_t>(container->m_scannerType);
    writeLE(os, st);
    writeLE(os, container->m_reserved0);

    if (!serialize(os, container->m_fpgaVersion))
    {
        return false;
    }
    if (!serialize(os, container->m_dspVersion))
    {
        return false;
    }
    if (!serialize(os, container->m_hostVersion))
    {
        return false;
    }

    writeLE(os, container->m_fpgaModusRegister);
    writeLE(os, container->m_reserved1);

    writeLE(os, container->m_sensorTemperature);
    writeLE(os, container->m_frequency);
    writeLE(os, container->m_apdTableVoltage);
    for (unsigned int s = 0; s < C::nbOfApdSectors; ++s)
    {
        writeLE(os, container->m_adaptiveApdVoltage[s]);
    }
    writeLE(os, container->m_minApdVoltageOffset);
    writeLE(os, container->m_maxApdVoltageOffset);

    writeLE(os, container->m_reserved2);
    writeLE(os, container->m_reserved3);

    writeLE(os, container->m_noiseMeasurementThreshold);
    writeLE(os, container->m_referenceNoise);
    for (unsigned int s = 0; s < C::nbOfApdSectors; ++s)
    {
        writeLE(os, container->m_actualNoise[s]);
    }

    for (unsigned int r = 0; r < C::nbOfReservedA; ++r)
    {
        writeLE(os, container->m_reservedA[r]);
    }

    return (!os.fail()) && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6301>::serialize(std::ostream& os, const SerialNumberIn6301& sn)
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeLE(os, sn.m_month);
    ibeo::common::sdk::writeLE(os, sn.m_year);
    ibeo::common::sdk::writeLE(os, sn.m_cnt1);
    ibeo::common::sdk::writeLE(os, sn.m_cnt0);
    ibeo::common::sdk::writeLE(os, sn.m_null);

    return (!os.fail())
           && ((streamposToInt64(os.tellp()) - startPos) == DeviceStatus6301SerializedSize6301::getSerializedSize(sn));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6301>::serialize(std::ostream& os, const Version448In6301& version)
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeLE(os, version.m_version);
    ibeo::common::sdk::writeLE(os, version.m_year);
    ibeo::common::sdk::writeLE(os, version.m_month);
    ibeo::common::sdk::writeLE(os, version.m_day);
    ibeo::common::sdk::writeLE(os, version.m_hour);
    ibeo::common::sdk::writeLE(os, version.m_minute);

    return (!os.fail())
           && ((streamposToInt64(os.tellp()) - startPos)
               == DeviceStatus6301SerializedSize6301::getSerializedSize(version));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
