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
//!\date Jan 17, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2280.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Ibeo FUSION SYSTEM/ECU object data:
//! List of objects with extended tracking information (generic)
//!
//! Object data available from Ibeo FUSION SYSTEM and Ibeo ECU connected with Ibeo Laserscanners.
//! Each data block starts with the IbeoDataHeader followed by the object list.
//! For each object list this header is preceded.
//!
//! Each object has a list of contour points. Subtypes are described below.
//
//! All positions and angles are given in the vehicle / reference coordinate system.
//
//! In general, positions, lengths, distances and sizes are coded in meters. In general, angles are coded in radians.
//!
//! Note: depending on the configuration of the fusion system, the ECU can provide object data of type 0x2281.
//!
//! General data type: \ref ibeo::common::sdk::ObjectList
class ObjectList2280 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using ObjectVector = std::vector<ObjectIn2280>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.objectlist2280"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    ObjectList2280();
    virtual ~ObjectList2280();

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // getter
    NTPTime getTimestamp() const { return m_timestamp; }

    uint16_t getNbOfObjects() const { return static_cast<uint16_t>(m_objects.size()); }
    const ObjectVector& getObjects() const { return m_objects; }
    ObjectVector& getObjects() { return m_objects; }

public: // setter
    void setTimestamp(const NTPTime& timestamp) { m_timestamp = timestamp; }
    void setObjects(const ObjectVector& objects) { m_objects = objects; }

protected:
    NTPTime m_timestamp;
    // number of objects uint16_t
    ObjectVector m_objects;
}; // ObjectList2280

//==============================================================================

bool operator==(const ObjectList2280& lhs, const ObjectList2280& rhs);
bool operator!=(const ObjectList2280& lhs, const ObjectList2280& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
