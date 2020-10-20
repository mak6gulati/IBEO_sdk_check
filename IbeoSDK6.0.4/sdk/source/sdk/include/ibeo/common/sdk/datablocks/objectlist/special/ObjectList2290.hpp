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
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2290.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Same as DataTypeObjectList (0x2280) but holds only reference objects.
//!
//! General data type: \ref ibeo::common::sdk::ObjectList
class ObjectList2290 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using ObjectVector = std::vector<ObjectIn2290>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.objectlist2290"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    ObjectList2290();
    virtual ~ObjectList2290();

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
}; // ObjectList2290

//==============================================================================

bool operator==(const ObjectList2290& lhs, const ObjectList2290& rhs);
bool operator!=(const ObjectList2290& lhs, const ObjectList2290& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
