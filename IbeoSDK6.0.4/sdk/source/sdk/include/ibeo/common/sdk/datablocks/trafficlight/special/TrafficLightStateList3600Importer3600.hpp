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

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/trafficlight/special/TrafficLightStateList3600.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<TrafficLightStateList3600, DataTypeId::DataType_TrafficLight3600>
  : public RegisteredImporter<TrafficLightStateList3600, DataTypeId::DataType_TrafficLight3600>
{
public:
    Importer() : RegisteredImporter() {}
    Importer(const Importer&) = delete;
    Importer& operator=(const Importer&) = delete;

public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;

}; // TrafficLightStateList3600Importer3600

//==============================================================================

using TrafficLightStateList3600Importer3600
    = Importer<TrafficLightStateList3600, DataTypeId::DataType_TrafficLight3600>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
