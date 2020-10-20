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
//!\date Aug 29, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/trafficlight/special/TrafficLightStateIn3600.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize TrafficLightStateIn3600::getSerializedSize() const
{ //note: NTPTime is serialized as unit64
    return 2 * std::streamsize(sizeof(uint32_t)) + 5 * std::streamsize(sizeof(uint64_t));
}

//==============================================================================

bool TrafficLightStateIn3600::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, m_id);
    uint32_t rd32;
    readBE(is, rd32);
    m_phase = TrafficLightStateIn3600::Phase(rd32);
    readBE(is, m_timestampFromTrafficLight);
    readBE(is, m_timeIntervalAbsoluteBegin);
    readBE(is, m_timeIntervalAbsoluteEnd);
    readBE(is, m_timeIntervalRelativeBegin);
    readBE(is, m_timeIntervalRelativeEnd);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool TrafficLightStateIn3600::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, m_id);
    writeBE(os, static_cast<uint32_t>(m_phase));
    writeBE(os, m_timestampFromTrafficLight);
    writeBE(os, m_timeIntervalAbsoluteBegin);
    writeBE(os, m_timeIntervalAbsoluteEnd);
    writeBE(os, m_timeIntervalRelativeBegin);
    writeBE(os, m_timeIntervalRelativeEnd);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool operator==(const TrafficLightStateIn3600& lhs, const TrafficLightStateIn3600& rhs)
{
    return lhs.getId() == rhs.getId() && lhs.getPhase() == rhs.getPhase()
           && lhs.getTimestampFromTrafficLight() == rhs.getTimestampFromTrafficLight()
           && lhs.getTimeIntervalAbsoluteBegin() == rhs.getTimeIntervalAbsoluteBegin()
           && lhs.getTimeIntervalAbsoluteEnd() == rhs.getTimeIntervalAbsoluteEnd()
           && lhs.getTimeIntervalRelativeBegin() == rhs.getTimeIntervalRelativeBegin()
           && lhs.getTimeIntervalRelativeEnd() == rhs.getTimeIntervalRelativeEnd();
}

//==============================================================================

bool operator!=(const TrafficLightStateIn3600& lhs, const TrafficLightStateIn3600& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
