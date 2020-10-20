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
//! \date Jan 13, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/MeasurementList.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Ibeo FUSION SYSTEM/ECU measurement list:
//! Measurement List (generic)
//!
//! Measurement List data to represent dynamic measurements provided by an Ibeo sensor system.
//!
//! All angles, position and distances are given in the ISO 8855 / DIN 70000 coordinate system.
class MeasurementList2821 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.measurementlist2821"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    MeasurementList2821();
    virtual ~MeasurementList2821();

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    uint32_t getMicroseconds() const { return m_microseconds; }
    NTPTime getTimestamp() const { return m_timestamp; }

    const std::string& getListName() const { return m_listName; }
    std::string& getListName() { return m_listName; }
    const std::string& getGroupName() const { return m_groupName; }
    std::string& getGroupName() { return m_groupName; }
    const MeasurementList& getMeasList() const { return m_mList; }
    MeasurementList& getMeasList() { return m_mList; }

public:
    void setMicroseconds(const uint32_t newMicroseconds) { m_microseconds = newMicroseconds; }
    void setTimestamp(const NTPTime newTimestamp) { m_timestamp = newTimestamp; }
    void setListName(const std::string& newListName) { m_listName = newListName; }
    void setGroupName(const std::string& newGroupName) { m_groupName = newGroupName; }
    void setMeasurementList(const MeasurementList& newMeasurementList) { m_mList = newMeasurementList; }

protected:
    uint32_t m_microseconds{0};
    NTPTime m_timestamp{};
    std::string m_listName{};
    std::string m_groupName{};
    MeasurementList m_mList{};
}; // MeasurementList2821Container

//==============================================================================

bool operator==(const MeasurementList2821& lhs, const MeasurementList2821& rhs);
inline bool operator!=(const MeasurementList2821& lhs, const MeasurementList2821& rhs) { return !(rhs == lhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
