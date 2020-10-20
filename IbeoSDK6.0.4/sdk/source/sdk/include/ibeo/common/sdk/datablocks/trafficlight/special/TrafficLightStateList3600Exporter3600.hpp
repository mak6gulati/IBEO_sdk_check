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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/trafficlight/special/TrafficLightStateList3600.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<TrafficLightStateList3600, DataTypeId::DataType_TrafficLight3600>
  : public TypedExporter<TrafficLightStateList3600, DataTypeId::DataType_TrafficLight3600>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;

}; // TrafficLightStateList3600Exporter3600

//==============================================================================

using TrafficLightStateList3600Exporter3600
    = Exporter<TrafficLightStateList3600, DataTypeId::DataType_TrafficLight3600>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
