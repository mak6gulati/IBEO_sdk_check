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
//! \date Apr 28, 2016
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelIn6503.hpp>

#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize ObjectLabelIn6503::getSerializedSize() const
{
    return serializedSize(m_objBox) + std::streamsize(2 * sizeof(uint8_t)) + std::streamsize(sizeof(uint32_t))
           + std::streamsize(sizeof(uint64_t)) + std::streamsize(sizeof(float))
           + std::streamsize((2 + nbOfReserved) * sizeof(uint16_t)) + m_userData.getSerializedSize();
}

//==============================================================================

bool ObjectLabelIn6503::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, this->m_objBox);
    ibeo::common::sdk::readBE(is, this->m_weight);
    ibeo::common::sdk::readBE(is, this->m_classification);
    ibeo::common::sdk::readBE(is, this->m_id);
    ibeo::common::sdk::readBE(is, this->m_trackingId);
    ibeo::common::sdk::readBE(is, this->m_displayMagnificationFactor);
    ibeo::common::sdk::readBE(is, this->m_objectFlags);
    ibeo::common::sdk::readBE(is, this->m_isInOnKeyframe);
    for (auto& reserved : this->m_reserved)
    {
        ibeo::common::sdk::readBE(is, reserved);
    }

    m_userData.deserialize(is);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ObjectLabelIn6503::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, this->m_objBox);
    ibeo::common::sdk::writeBE(os, this->m_weight);
    ibeo::common::sdk::writeBE(os, this->m_classification);
    ibeo::common::sdk::writeBE(os, this->m_id);
    ibeo::common::sdk::writeBE(os, this->m_trackingId);
    ibeo::common::sdk::writeBE(os, this->m_displayMagnificationFactor);
    ibeo::common::sdk::writeBE(os, this->m_objectFlags);
    ibeo::common::sdk::writeBE(os, this->m_isInOnKeyframe);
    for (auto reserved : this->m_reserved)
    {
        ibeo::common::sdk::writeBE(os, reserved);
    }

    m_userData.serialize(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool operator==(const ObjectLabelIn6503& lhs, const ObjectLabelIn6503& rhs)
{
    if (lhs.getObjBox() != rhs.getObjBox() || lhs.getWeight() != rhs.getWeight()
        || lhs.getClassification() != rhs.getClassification() || lhs.getId() != rhs.getId()
        || lhs.getTrackingId() != rhs.getTrackingId()
        || lhs.getDisplayMagnificationFactor() != rhs.getDisplayMagnificationFactor()
        || lhs.getObjectFlags() != rhs.getObjectFlags() || lhs.getIsInOnKeyframe() != rhs.getIsInOnKeyframe())
        return false;

    if (lhs.getUserData() != rhs.getUserData())
        return false;

    for (uint16_t r = 0; r < ObjectLabelIn6503::nbOfReserved; ++r)
    {
        if (lhs.getReserved(r) != rhs.getReserved(r))
            return false;
    }
    return true;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
