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
//! \date Jan 25, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/objectlabellist/ObjectLabel.hpp>
#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelList6503.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <array>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief List of object labels
//!
//! Special data type: \ref ibeo::common::sdk::OBjectLabelList6503
class ObjectLabelList : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

    friend bool operator==(const ObjectLabelList& lhs, const ObjectLabelList& rhs);

public:
    constexpr static const uint32_t nbOfReserved{10};

public: //type definitions
    using LabelVector   = std::vector<ObjectLabel>;
    using ReservedArray = std::array<uint16_t, nbOfReserved>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.generalcontainer.objectlabellist"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    ObjectLabelList() : DataContainerBase() {}
    virtual ~ObjectLabelList() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // getter
    uint32_t getTimeOffsetUs() const { return m_delegate.getTimeOffsetUs(); }
    NTPTime getTimestamp() const { return m_delegate.getTimestamp(); }
    uint32_t getScanNumber() const { return m_delegate.getScanNumber(); }
    NTPTime getScanMidTimestamp() const { return m_delegate.getScanMidTimestamp(); }
    uint16_t getReserved(const uint32_t idx) const { return m_delegate.getReserved(idx); }

    const LabelVector& getLabels() const { return m_delegate.getLabels(); }
    LabelVector& getLabels() { return m_delegate.getLabels(); }

public: // setter
    void setTimeOffsetUs(const uint32_t newTimeOffsetUs) { m_delegate.setTimeOffsetUs(newTimeOffsetUs); }
    void setTimestamp(const NTPTime newTimestamp) { m_delegate.setTimestamp(newTimestamp); }
    void setScanNumber(const uint32_t newScanNumber) { m_delegate.setScanNumber(newScanNumber); }
    void setScanMidTimestamp(const NTPTime newScanMidTimestamp) { m_delegate.setScanMidTimestamp(newScanMidTimestamp); }
    void setReserved(const uint32_t idx, const uint16_t newReservedValue)
    {
        m_delegate.setReserved(idx, newReservedValue);
    }
    // use getLabels

private:
    ObjectLabelList6503 m_delegate;
}; // ObjectLabelList

//==============================================================================

inline bool operator==(const ObjectLabelList& lhs, const ObjectLabelList& rhs)
{
    return lhs.m_delegate == rhs.m_delegate;
}

inline bool operator!=(const ObjectLabelList& lhs, const ObjectLabelList& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
