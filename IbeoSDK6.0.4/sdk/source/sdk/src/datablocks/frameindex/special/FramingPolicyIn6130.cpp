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
//!\date May 11, 2015
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/frameindex/special/FramingPolicyIn6130.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

constexpr uint8_t FramingPolicyIn6130::deviceIdAny;

//==============================================================================

std::streamsize FramingPolicyIn6130::getSerializedSize() const
{
    return std::streamsize(1 + 2 + (m_triggers.size() * 3));
}

//==============================================================================

bool FramingPolicyIn6130::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_triggerInNewFrame);

    uint16_t numTriggers = 0;
    ibeo::common::sdk::readBE(is, numTriggers);

    uint16_t tmpDataType = 0;
    uint8_t tmpDeviceId  = 0;

    m_triggers.clear();
    for (std::size_t i = 0; i < numTriggers; ++i)
    {
        ibeo::common::sdk::readBE(is, tmpDataType);
        ibeo::common::sdk::readBE(is, tmpDeviceId);
        m_triggers.insert(
            std::pair<ibeo::common::sdk::DataTypeId, uint8_t>(ibeo::common::sdk::DataTypeId(tmpDataType), tmpDeviceId));
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool FramingPolicyIn6130::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_triggerInNewFrame);
    ibeo::common::sdk::writeBE(os, uint16_t(m_triggers.size()));

    for (const Trigger& trigger : m_triggers)
    {
        ibeo::common::sdk::writeBE(os, static_cast<uint16_t>(trigger.first));
        ibeo::common::sdk::writeBE(os, trigger.second);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool FramingPolicyIn6130::isTrigger(const ibeo::common::sdk::DataTypeId dataType, const uint8_t fromDeviceID) const
{
    TriggerSet::const_iterator it = m_triggers.find(dataType);
    return ((it != m_triggers.end()) && (it->second == deviceIdAny || it->second == fromDeviceID));
}

//==============================================================================

bool operator==(const FramingPolicyIn6130& lhs, const FramingPolicyIn6130& rhs)
{
    return (lhs.getTriggerInNewFrame() == rhs.getTriggerInNewFrame()) && (lhs.getTriggers() == rhs.getTriggers());
}

//==============================================================================

bool operator!=(const FramingPolicyIn6130& lhs, const FramingPolicyIn6130& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
