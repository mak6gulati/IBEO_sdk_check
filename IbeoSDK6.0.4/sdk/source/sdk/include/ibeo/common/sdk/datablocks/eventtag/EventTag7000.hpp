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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/PositionWgs84.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <array>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Event Tag
class EventTag7000 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    static const uint8_t nbOfReserved = 16;

public:
    using ReservedArray = std::array<char, nbOfReserved>;

    enum class TagClass : uint16_t
    {
        Unknown    = 0x0000,
        Pedestrian = 0x0001
    };

    enum class Flags : uint8_t
    {
        IsEnd   = 0x01,
        IsPulse = 0x02
    };

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.eventtag7000"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    EventTag7000();
    virtual ~EventTag7000();

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    NTPTime getTagStart() const { return m_tagStart; }
    NTPTime getTagEnd() const { return m_tagEnd; }
    uint8_t getFlags() const { return m_flags; }
    TagClass getTagClass() const { return m_tagClass; }
    uint32_t getTagId() const { return m_tagId; }
    const std::string& getTagString() const { return m_tagString; }
    std::string& getTagString() { return m_tagString; }
    const PositionWgs84& getWgs84() const { return m_wgs84; }
    PositionWgs84& getWgs84() { return m_wgs84; }
    uint64_t getRoiWidth() const { return m_roiWidth; }
    uint64_t getRoiLength() const { return m_roiLength; }

    bool isEndOfEvent() const { return ((m_flags & static_cast<uint8_t>(Flags::IsEnd)) != 0); }
    bool isPulseEvent() const { return ((m_flags & static_cast<uint8_t>(Flags::IsPulse)) != 0); }

    char getReserved(const uint8_t idx) const { return m_reserved.at(idx); }
    const ReservedArray& getReserved() const { return m_reserved; }

public:
    void setTagStart(const NTPTime newTagStart) { m_tagStart = newTagStart; }
    void setTagEnd(const NTPTime newTagEnd) { m_tagEnd = newTagEnd; }
    void setFlags(const uint8_t newFlags) { m_flags = newFlags; }
    void setTagClass(const TagClass newTagClass) { m_tagClass = newTagClass; }
    void setTagId(const uint32_t newTagId) { m_tagId = newTagId; }
    void setTagString(const std::string& newTagString) { m_tagString = newTagString; }
    void setWgs84(const PositionWgs84& newWgs84) { m_wgs84 = newWgs84; }
    void setRoiWidth(const uint64_t newRoiWidth) { m_roiWidth = newRoiWidth; }
    void setRoiLength(const uint64_t newRoiLength) { m_roiLength = newRoiLength; }

    void setIsEndOfEvent() { m_flags |= static_cast<uint8_t>(Flags::IsEnd); }
    void unsetIsEndOfEvent() { m_flags &= static_cast<uint8_t>(~static_cast<uint8_t>(Flags::IsEnd)); }

    void setIsPulseEvent() { m_flags |= static_cast<uint8_t>(Flags::IsPulse); }
    void unsetIsPulseEvent() { m_flags &= static_cast<uint8_t>(~static_cast<uint8_t>(Flags::IsPulse)); }

protected:
    NTPTime m_tagStart{};
    NTPTime m_tagEnd{};
    uint8_t m_flags{0U};
    TagClass m_tagClass{TagClass::Unknown};
    uint32_t m_tagId{0U};
    std::string m_tagString{};
    PositionWgs84 m_wgs84{};
    uint64_t m_roiWidth{0U};
    uint64_t m_roiLength{0U};
    ReservedArray m_reserved{{0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}};
}; // EventTag7000

//==============================================================================

bool operator==(const EventTag7000& lhs, const EventTag7000& rhs);
bool operator!=(const EventTag7000& lhs, const EventTag7000& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
