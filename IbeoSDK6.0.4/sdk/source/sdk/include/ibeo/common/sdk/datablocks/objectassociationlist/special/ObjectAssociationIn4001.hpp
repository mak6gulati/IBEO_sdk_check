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
//! \date Apr 26, 2016
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class ObjectAssociationIn4001
{
public:
    ObjectAssociationIn4001()          = default;
    virtual ~ObjectAssociationIn4001() = default;

    //==============================================================================

public: // getter
    uint32_t getReferenceObjId() const { return m_refObjId; }
    uint32_t getDutObjId() const { return m_dutObjId; }
    NTPTime getTimestampFirst() const { return m_timestampFirst; }
    NTPTime getTimestampLast() const { return m_timestampLast; }
    float getCertainty() const { return m_certainty; }

public: // setter
    void setRefObjId(const uint32_t newReferenceObjectId) { m_refObjId = newReferenceObjectId; }
    void setDutObjId(const uint32_t newDutObjectId) { m_dutObjId = newDutObjectId; }
    void setTimestampFirst(const NTPTime newTimestampFirst) { m_timestampFirst = newTimestampFirst; }
    void setTimestampLast(const NTPTime newTimestampLast) { m_timestampLast = newTimestampLast; }
    void setCertainty(const float newCertainty) { m_certainty = newCertainty; }

public:
    static std::streamsize getSerializedSize_static() { return 28; }

public:
    virtual std::streamsize getSerializedSize() const { return getSerializedSize_static(); }
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

protected:
    uint32_t m_refObjId{0};
    uint32_t m_dutObjId{0};
    NTPTime m_timestampFirst{};
    NTPTime m_timestampLast{};
    float m_certainty{0.0F};
}; // ObjectAssociation4001Entry

//==============================================================================

inline bool operator==(const ObjectAssociationIn4001& lhs, const ObjectAssociationIn4001& rhs)
{
    return lhs.getReferenceObjId() == rhs.getReferenceObjId() && lhs.getDutObjId() == rhs.getDutObjId()
           && lhs.getTimestampFirst() == rhs.getTimestampFirst() && lhs.getTimestampLast() == rhs.getTimestampLast()
           && fuzzyFloatEqualT<6>(lhs.getCertainty(), rhs.getCertainty());
}

//==============================================================================

inline bool operator!=(const ObjectAssociationIn4001& lhs, const ObjectAssociationIn4001& rhs) { return !(lhs == rhs); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
