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

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayTemplate.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayIn6972.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief List of carriageways containing a list of lane segments.
class CarriageWayList6972 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.carriagewaylist6972"};

    using CarriageWays = std::vector<typename lanes::CarriageWayTemplate<lanes::LaneSegmentIn6972>::Ptr>;

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    CarriageWayList6972();
    virtual ~CarriageWayList6972() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    const CarriageWays& getCarriageWays() const { return m_carriageWays; }
    CarriageWays& getCarriageWays() { return m_carriageWays; }

private:
    CarriageWays m_carriageWays{};
}; // CarriageWayList6972

//==============================================================================

bool operator==(const CarriageWayList6972& lhs, const CarriageWayList6972& rhs);

inline bool operator!=(const CarriageWayList6972& lhs, const CarriageWayList6972& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
