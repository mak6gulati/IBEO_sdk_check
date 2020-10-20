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
//!\date Aug 29, 2018
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/datablocks/trafficlight/special/TrafficLightStateList3600Exporter3600.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::TrafficLightStateList3600;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_TrafficLight3600>::getSerializedSize(const DataContainerBase& c) const
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

    return static_cast<std::streamsize>(container->m_trafficLightStates.size())
               * TrafficLightStateIn3600::getSerializedSize_static()
           + 8;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_TrafficLight3600>::serialize(std::ostream& os, const DataContainerBase& c) const
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
    writeBE(os, container->m_trafficLightStates.size());

    for (uint64_t i = 0; i < container->m_trafficLightStates.size(); ++i)
    {
        container->m_trafficLightStates[i].serialize(os);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
