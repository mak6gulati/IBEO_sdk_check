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
//!\date 09.November 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/trafficlight/TrafficLightStateList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<TrafficLightStateList, DataTypeId::DataType_TrafficLight3600>
  : public RegisteredImporter<TrafficLightStateList, DataTypeId::DataType_TrafficLight3600>
{
public:
    Importer()                = default;
    Importer(const Importer&) = delete;
    Importer& operator=(const Importer&) = delete;

public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;

}; // TrafficLightStateListImporter3600

//==============================================================================

using TrafficLightStateListImporter3600 = Importer<TrafficLightStateList, DataTypeId::DataType_TrafficLight3600>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
