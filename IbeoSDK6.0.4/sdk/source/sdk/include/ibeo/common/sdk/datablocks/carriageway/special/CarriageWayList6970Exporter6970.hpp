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
//!\date Apr 4, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6970.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<CarriageWayList6970, DataTypeId::DataType_CarriageWayList6970>
  : public TypedExporter<CarriageWayList6970, DataTypeId::DataType_CarriageWayList6970>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;

private:
    static bool serialize(std::ostream& os, const lanes::CarriageWayIn6970& cw);
    static bool serialize(std::ostream& os, const lanes::CarriageWaySegmentIn6970& cws);
    static bool serialize(std::ostream& os, const lanes::LaneIn6970& lane);
    static bool serialize(std::ostream& os, const lanes::LaneSegmentIn6970& laneSeg);
    static bool serialize(std::ostream& os, const lanes::LaneSupportPointIn6970& point);
}; // CarriageWayList6970Exporter6970

//==============================================================================

using CarriageWayList6970Exporter6970 = Exporter<CarriageWayList6970, DataTypeId::DataType_CarriageWayList6970>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
