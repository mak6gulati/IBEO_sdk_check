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
//!\date 14.November 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/datablocks/RegisteredDataBlock.hpp>
#include <ibeo/common/sdk/datablocks/PositionWgs84.hpp>
#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>
//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! GPS way point list
//! this data type was generated with the interface to BestMile for fleet management in mind [https://developer.bestmile.com/v1/docs/performing-a-mission#section-mission-fields-overview], it's similar to Waypoints field
class PositionWgs84Sequence : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const char* const containerType{"ibeo.sdk.generalcontaienr.positionwgs84sequence"};
    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }
    static constexpr uint8_t nbOfReserved = 4;

public:
    using ArrayOfReserved = std::array<uint32_t, nbOfReserved>;

public:
    enum SourceType : uint8_t
    {
        Mission = 0,
        Unknown = 255
    };

public:
    PositionWgs84Sequence();
    ~PositionWgs84Sequence() override = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    void setPositionSequence(const std::vector<PositionWgs84>& positionSequence)
    {
        this->m_positionSequence = positionSequence;
    }
    void setTimestamp(const NTPTime& timestamp) { this->m_timestamp = timestamp; }
    void setSourceType(const SourceType sourceType) { this->m_sourceType = sourceType; }
    void setId(const uint32_t id) { this->m_id = id; }
    const std::vector<PositionWgs84>& getPositionSequence() const { return m_positionSequence; }
    NTPTime getTimestamp() const { return m_timestamp; }
    SourceType getSourceType() const { return m_sourceType; }
    uint32_t getId() const { return m_id; }
    uint32_t getReserved(const uint_fast8_t idx) const { return m_reserved.at(idx); }
    ArrayOfReserved getReserved() const { return m_reserved; }

protected:
    std::vector<PositionWgs84> m_positionSequence{0}; //!< Sequence of wgs84 positions
    NTPTime m_timestamp{}; //!< Timestamp of of this data type
    SourceType m_sourceType{SourceType::Unknown}; //!< Indicates source of this data type
    uint32_t m_id{0}; //!< Identifier of position sequence

private:
    ArrayOfReserved m_reserved{{}};

}; //PositionWgs84

//==============================================================================

bool operator==(const PositionWgs84Sequence& lhs, const PositionWgs84Sequence& rhs);
bool operator!=(const PositionWgs84Sequence& lhs, const PositionWgs84Sequence& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
