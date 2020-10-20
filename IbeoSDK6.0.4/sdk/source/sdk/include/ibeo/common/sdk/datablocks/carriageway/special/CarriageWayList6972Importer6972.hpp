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

#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6972.hpp>
#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<CarriageWayList6972, DataTypeId::DataType_CarriageWayList6972>
  : public RegisteredImporter<CarriageWayList6972, DataTypeId::DataType_CarriageWayList6972>
{
public:
    Importer()                = default;
    Importer(const Importer&) = delete;
    Importer& operator=(const Importer&) = delete;

public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

    //========================================
    //!\brief convert data from source to target type (deserialization)
    //!\param[in, out] is      Input data stream
    //!\param[out]     c       Output container.
    //!\param[in]      header  Ibeo DataHeader
    //!\return \c true if serialization succeed, else: false
    //!\note This method is to be called from outside for deserialization.
    //----------------------------------------
    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;

    static bool deserialize(std::istream& is, lanes::CarriageWayIn6972& cw);
    static bool deserialize(std::istream& is, lanes::CarriageWaySegmentIn6972& cws);
    static bool deserialize(std::istream& is, lanes::LaneIn6972& lane);
    static bool deserialize(std::istream& is, lanes::LaneSegmentIn6972& laneSeg);
    static bool deserialize(std::istream& is, lanes::LaneSupportPointIn6972& point);
}; //CarriageWayList6972Importer6972

//==============================================================================

using CarriageWayList6972Importer6972 = Importer<CarriageWayList6972, DataTypeId::DataType_CarriageWayList6972>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
