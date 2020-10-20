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
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2225.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Ibeo FUSION SYSTEM/ECU object data:
//! ObjectList has now a timestamp that should have the midTimestamp of the corresponding scan
//!
//! Object data available from Ibeo FUSION SYSTEM and Ibeo AppBase2 (ECU).
//! Each data block starts with a header followed by the object list.
//! Each object has a list of contour points.
//! The Sigma values are calculated using a Kalman filter by taking into account the object age.
//! All positions and angles are given in the vehicle / reference coordinate system.
//!
//! General data type: \ref ibeo::common::sdk::ObjectList
class ObjectList2225 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using ObjectVector = std::vector<ObjectIn2225>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.objectlist2225"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    ObjectList2225();
    virtual ~ObjectList2225();

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    NTPTime getTimestamp() const { return m_timestamp; }

    uint16_t getNbOfObjects() const { return static_cast<uint16_t>(m_objects.size()); }
    const ObjectVector& getObjects() const { return m_objects; }
    ObjectVector& getObjects() { return m_objects; }

    IBEOSDK_DEPRECATED NTPTime getScanStartTimestamp() const { return m_timestamp; }

public: // setter
    void setTimestamp(const NTPTime newTimeStamp) { m_timestamp = newTimeStamp; }
    void setObjects(const ObjectVector& newObjects) { m_objects = newObjects; }

    IBEOSDK_DEPRECATED void setScanStartTimestamp(const NTPTime newScanStartTimeStamp)
    {
        m_timestamp = newScanStartTimeStamp;
    }

protected:
    NTPTime m_timestamp{0};
    ObjectVector m_objects{};
}; // ObjectList2225

//==============================================================================

//==============================================================================

bool operator==(const ObjectList2225& lhs, const ObjectList2225& rhs);
bool operator!=(const ObjectList2225& lhs, const ObjectList2225& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
