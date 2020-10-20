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

#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringSystemStatus6705Exporter6705.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::SystemMonitoringSystemStatus6705;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_SystemMonitoringSystemStatus6705>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_SystemMonitoringSystemStatus6705>::serialize(std::ostream& os,
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

    const boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));

    // convert ptime to int64
    const boost::posix_time::time_duration lastUpdateFromEpoch = container->m_lastUpdateTimestamp - epoch;
    const uint64_t lastUpdateMilliseconds = static_cast<uint64_t>(lastUpdateFromEpoch.total_milliseconds());

    ibeo::common::sdk::writeBE(os, lastUpdateMilliseconds);

    ibeo::common::sdk::writeBE(os, container->m_state);
    ibeo::common::sdk::writeBE(os, container->m_stateInformation);
    ibeo::common::sdk::writeBE(os, container->m_currentCpuUsage);
    ibeo::common::sdk::writeBE(os, container->m_currentRamUsage);
    ibeo::common::sdk::writeBE(os, container->m_currentHddUsage);
    ibeo::common::sdk::writeBE(os, container->m_hddWarningLevelPercent);
    ibeo::common::sdk::writeBE(os, container->m_hddErrorLevelPercent);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
