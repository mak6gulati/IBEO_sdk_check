//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 15, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelIn6503.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <array>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief List of object labels
//!
//! General data type: \ref ibeo::common::sdk::ObjectLabelList
class ObjectLabelList6503 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const uint32_t nbOfReserved{10};

public: //type definitions
    using LabelVector   = std::vector<ObjectLabelIn6503>;
    using ReservedArray = std::array<uint16_t, nbOfReserved>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.objectlabellist6503"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    ObjectLabelList6503() : SpecializedDataContainer() {}
    virtual ~ObjectLabelList6503() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // getter
    uint32_t getTimeOffsetUs() const { return m_timeOffsetUs; }
    NTPTime getTimestamp() const { return m_timestamp; }
    uint32_t getScanNumber() const { return m_scanNumber; }
    NTPTime getScanMidTimestamp() const { return m_scanMidTimestamp; }
    uint16_t getReserved(const uint32_t idx) const { return m_reserved.at(idx); }

    const LabelVector& getLabels() const { return m_labels; }
    LabelVector& getLabels() { return m_labels; }

public: // setter
    void setTimeOffsetUs(const uint32_t newTimeOffsetUs) { m_timeOffsetUs = newTimeOffsetUs; }
    void setTimestamp(const NTPTime newTimestamp) { m_timestamp = newTimestamp; }
    void setScanNumber(const uint32_t newScanNumber) { m_scanNumber = newScanNumber; }
    void setScanMidTimestamp(const NTPTime newScanMidTimestamp) { m_scanMidTimestamp = newScanMidTimestamp; }
    void setReserved(const uint32_t idx, const uint16_t newReservedValue) { m_reserved.at(idx) = newReservedValue; }
    // use getLabels

protected:
    uint32_t m_timeOffsetUs{0};
    NTPTime m_timestamp{0};
    uint32_t m_scanNumber{0};
    NTPTime m_scanMidTimestamp{0};
    ReservedArray m_reserved{{}};
    //uint16_t m_nbOfLabels
    LabelVector m_labels{};
}; // ObjectLabelList6503Container

//==============================================================================

bool operator==(const ObjectLabelList6503& lhs, const ObjectLabelList6503& rhs);
bool operator!=(const ObjectLabelList6503& lhs, const ObjectLabelList6503& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
