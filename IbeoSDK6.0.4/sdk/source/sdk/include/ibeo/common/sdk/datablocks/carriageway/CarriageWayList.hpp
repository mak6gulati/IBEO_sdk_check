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

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayTemplate.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/CarriageWay.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief List of carriageways containing a list of lane segments.
//!
//! Special data type: \ref ibeo::common::sdk::CarriageWayList6972
class CarriageWayList : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.carriagewaylist"};

    using CarriageWays = std::vector<typename lanes::CarriageWayTemplate<lanes::LaneSegment>::Ptr>;

    // in C++14 this could be a constexpr
    static uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    CarriageWayList();
    virtual ~CarriageWayList() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    const CarriageWays& getCarriageWays() const { return m_carriageWays; }
    CarriageWays& getCarriageWays() { return m_carriageWays; }

private:
    CarriageWays m_carriageWays{};
}; // CarriageWayList

//==============================================================================

bool operator==(const CarriageWayList& lhs, const CarriageWayList& rhs);

inline bool operator!=(const CarriageWayList& lhs, const CarriageWayList& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
