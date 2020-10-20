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
//! \date Apr 24, 2014
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2271.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

std::streamsize ObjectIn2271::getSerializedSize() const
{
    return std::streamsize(sizeof(uint32_t)) + 3 * std::streamsize(sizeof(uint8_t))
           + m_unfilteredObjectData.getSerializedSize() + m_filteredObjectData.getSerializedSize()
           + std::streamsize(sizeof(uint32_t));
}

//==============================================================================

bool ObjectIn2271::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_objectId);
    ibeo::common::sdk::readBE(is, m_internal);
    ibeo::common::sdk::readBE(is, m_interfaceFlags);
    uint8_t attrFlags;
    ibeo::common::sdk::readBE(is, attrFlags);

    // attention has(Un)FilteredAttributes/Contours methods are not
    // to be used here since their data source has not be read yet.
    m_unfilteredObjectData.setIsValid((attrFlags & static_cast<uint8_t>(AttributeFlags::UnfilteredAttributesAvailable))
                                      == static_cast<uint8_t>(AttributeFlags::UnfilteredAttributesAvailable));

    m_unfilteredObjectData.setHasContourPoints(
        (attrFlags & static_cast<uint8_t>(AttributeFlags::UnfilteredContourAvailable))
        == static_cast<uint8_t>(AttributeFlags::UnfilteredContourAvailable));

    if (!m_unfilteredObjectData.deserialize(is))
    {
        return false;
    }

    m_filteredObjectData.setIsValid((attrFlags & static_cast<uint8_t>(AttributeFlags::FilteredAttributesAvailable))
                                    == static_cast<uint8_t>(AttributeFlags::FilteredAttributesAvailable));

    m_filteredObjectData.setHasContourPoints(
        (attrFlags & static_cast<uint8_t>(AttributeFlags::FilteredContourAvailable))
        == static_cast<uint8_t>(AttributeFlags::FilteredContourAvailable));

    m_filteredObjectData.deserialize(is);

    ibeo::common::sdk::readBE(is, m_reserved);
    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ObjectIn2271::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_objectId);
    ibeo::common::sdk::writeBE(os, m_internal);
    ibeo::common::sdk::writeBE(os, m_interfaceFlags);
    ibeo::common::sdk::writeBE(os, getAttributeFlags());

    m_unfilteredObjectData.serialize(os);
    m_filteredObjectData.serialize(os);
    ibeo::common::sdk::writeBE(os, m_reserved);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

uint8_t ObjectIn2271::getAttributeFlags() const
{
    uint8_t attrFlags = static_cast<uint8_t>(AttributeFlags::NoAttributes);

    if (hasUnfilteredAttributes())
    {
        attrFlags |= static_cast<uint8_t>(AttributeFlags::UnfilteredAttributesAvailable);
    }
    if (hasUnfilteredContour())
    {
        attrFlags |= static_cast<uint8_t>(AttributeFlags::UnfilteredContourAvailable);
    }

    if (hasFilteredAttributes())
    {
        attrFlags |= static_cast<uint8_t>(AttributeFlags::FilteredAttributesAvailable);
    }
    if (hasFilteredContour())
    {
        attrFlags |= static_cast<uint8_t>(AttributeFlags::FilteredContourAvailable);
    }

    return attrFlags;
}

//==============================================================================

void ObjectIn2271::setAttributeFlags(const uint8_t attrFlags)
{
    m_unfilteredObjectData.setIsValid((attrFlags & static_cast<uint8_t>(AttributeFlags::UnfilteredAttributesAvailable))
                                      == static_cast<uint8_t>(AttributeFlags::UnfilteredAttributesAvailable));

    m_unfilteredObjectData.setHasContourPoints(
        (attrFlags & static_cast<uint8_t>(AttributeFlags::UnfilteredContourAvailable))
        == static_cast<uint8_t>(AttributeFlags::UnfilteredContourAvailable));

    m_filteredObjectData.setIsValid((attrFlags & static_cast<uint8_t>(AttributeFlags::FilteredAttributesAvailable))
                                    == static_cast<uint8_t>(AttributeFlags::FilteredAttributesAvailable));

    m_filteredObjectData.setHasContourPoints(
        (attrFlags & static_cast<uint8_t>(AttributeFlags::FilteredContourAvailable))
        == static_cast<uint8_t>(AttributeFlags::FilteredContourAvailable));
}

//==============================================================================

bool operator==(const ObjectIn2271& lhs, const ObjectIn2271& rhs)
{
    return (lhs.getObjectId() == rhs.getObjectId()) && (lhs.getInternal() == rhs.getInternal())
           && (lhs.getInterfaceFlags() == rhs.getInterfaceFlags()) && (lhs.getReserved() == rhs.getReserved())
           && (lhs.getAttributeFlags() == rhs.getAttributeFlags())
           && (lhs.getUnfilteredObjectData() == rhs.getUnfilteredObjectData())
           && (lhs.getFilteredObjectData() == rhs.getFilteredObjectData());
}

//==============================================================================

bool operator!=(const ObjectIn2271& lhs, const ObjectIn2271& rhs) { return !(lhs == rhs); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
