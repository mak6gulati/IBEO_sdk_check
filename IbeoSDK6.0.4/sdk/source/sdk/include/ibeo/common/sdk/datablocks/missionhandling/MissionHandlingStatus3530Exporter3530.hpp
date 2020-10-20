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
//!\date 02.November 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/missionhandling/MissionHandlingStatus3530.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<MissionHandlingStatus3530, DataTypeId::DataType_MissionHandlingStatus3530>
  : public TypedExporter<MissionHandlingStatus3530, DataTypeId::DataType_MissionHandlingStatus3530>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // MissionHandlingStatus3530

//==============================================================================

using MissionHandlingStatus3530Exporter3530
    = Exporter<ibeo::common::sdk::MissionHandlingStatus3530, DataTypeId::DataType_MissionHandlingStatus3530>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
