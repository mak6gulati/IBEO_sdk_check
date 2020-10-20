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
//!\date Jan 23, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/logpolygonlist2d/LogPolygonList2d.hpp>
#include <ibeo/common/sdk/datablocks/logpolygonlist2d/special/LogPolygonList2dFloat6817.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief List of informational polygons with text label
//!
//! Special data types: \ref ibeo::common::sdk::LogPolygonList2dFloat6817
class LogPolygonList2d : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

    friend bool operator==(const LogPolygonList2d& lhs, const LogPolygonList2d& rhs);

public:
    using LogPolygonType       = LogPolygon2d<float>;
    using LogPolygonListVector = std::vector<LogPolygonType>;
    using iterator             = LogPolygonListVector::iterator;
    using const_iterator       = LogPolygonListVector::const_iterator;

public:
    constexpr static const char* const containerType{"ibeo.sdk.generalcontainer.logpolygonlist2d"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    LogPolygonList2d() : DataContainerBase{} {}
    virtual ~LogPolygonList2d() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    const LogPolygonListVector& getLogList() const { return m_delegate.getLogList(); }
    void setLogList(const LogPolygonListVector& logList) { m_delegate.setLogList(logList); }

private:
    LogPolygonList2dFloat6817 m_delegate;
}; // LogPolygonList2d

//==============================================================================

inline bool operator==(const LogPolygonList2d& lhs, const LogPolygonList2d& rhs)
{
    return (lhs.m_delegate == rhs.m_delegate);
}

inline bool operator!=(const LogPolygonList2d& lhs, const LogPolygonList2d& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
