//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Dec 19, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayList.hpp>
#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<CarriageWayList, DataTypeId::DataType_CarriageWayList6970>
  : public RegisteredImporter<CarriageWayList, DataTypeId::DataType_CarriageWayList6970>
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

private:
    static bool deserialize(std::istream& is, lanes::CarriageWay& cw);
    static bool deserialize(std::istream& is, lanes::CarriageWaySegment& cws);
    static bool deserialize(std::istream& is, lanes::Lane& lane);
    static bool deserialize(std::istream& is, lanes::LaneSegment& laneSeg);
    static bool deserialize(std::istream& is, lanes::LaneSupportPoint& point);
}; //CarriageWayListImporter6970

//==============================================================================

using CarriageWayListImporter6970 = Importer<CarriageWayList, DataTypeId::DataType_CarriageWayList6970>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
