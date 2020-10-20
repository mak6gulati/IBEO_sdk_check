//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringDeviceStatus6701Exporter6701.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::SystemMonitoringDeviceStatus6701;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_SystemMonitoringDeviceStatus6701>::getSerializedSize(const DataContainerBase& c) const
{
    try
    {
        (void)dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return serializedSize;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_SystemMonitoringDeviceStatus6701>::serialize(std::ostream& os,
                                                                                   const DataContainerBase& c) const
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

    ibeo::common::sdk::writeBE(os, container->m_deviceId);
    ibeo::common::sdk::writeBE(os, container->m_type);
    ibeo::common::sdk::writeBE(os, container->m_typeInformation);
    ibeo::common::sdk::writeBE(os, container->m_state);
    ibeo::common::sdk::writeBE(os, container->m_stateInformation);

    const boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));

    // convert ptime to int64
    const boost::posix_time::time_duration updateMissingFromEpoch = container->m_updateMissing - epoch;
    const uint64_t updateMissingMilliseconds = static_cast<uint64_t>(updateMissingFromEpoch.total_milliseconds());

    ibeo::common::sdk::writeBE(os, updateMissingMilliseconds);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
