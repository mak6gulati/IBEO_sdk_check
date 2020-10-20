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
//!\date Jul 31, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6972.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<CarriageWayList6972, DataTypeId::DataType_CarriageWayList6972>
  : public TypedExporter<CarriageWayList6972, DataTypeId::DataType_CarriageWayList6972>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;

    static bool serialize(std::ostream& os, const lanes::CarriageWayIn6972& cw);
    static bool serialize(std::ostream& os, const lanes::CarriageWaySegmentIn6972& cws);
    static bool serialize(std::ostream& os, const lanes::LaneIn6972& lane);
    static bool serialize(std::ostream& os, const lanes::LaneSegmentIn6972& laneSeg);
    static bool serialize(std::ostream& os, const lanes::LaneSupportPointIn6972& point);
}; // CarriageWayList6972Exporter6972

//==============================================================================

using CarriageWayList6972Exporter6972 = Exporter<CarriageWayList6972, DataTypeId::DataType_CarriageWayList6972>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
