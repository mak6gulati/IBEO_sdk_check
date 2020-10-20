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

//==============================================================================

#include <ibeo/common/sdk/datablocks/timerecord/TimeRecord9000.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

TimeRecord9000::TimeRecord9000() : SpecializedDataContainer{} {}

//==============================================================================

TimeRecord9000::~TimeRecord9000() {}

//==============================================================================

bool TimeRecord9000::setTimesAndFixeModes(const NTPTimeVector& externalTimes,
                                          const NTPTimeVector& internalTimes,
                                          const FixModeVector& fixModes)
{
    if ((externalTimes.size() == internalTimes.size()) && (internalTimes.size() == fixModes.size()))
    {
        this->m_externalClockTimes = externalTimes;
        this->m_internalClockTimes = internalTimes;
        this->m_fixModes           = fixModes;
        return true;
    }

    return false;
}

//==============================================================================

//==============================================================================

bool operator==(const TimeRecord9000& lhs, const TimeRecord9000& rhs)
{
    return (lhs.getInternalClockType() == rhs.getInternalClockType())
           && (lhs.getExternalClockType() == rhs.getExternalClockType())
           && (lhs.getInternalClockTimes() == rhs.getInternalClockTimes())
           && (lhs.getExternalClockTimes() == rhs.getExternalClockTimes()) && (lhs.getFixModes() == rhs.getFixModes());
}

//==============================================================================

bool operator!=(const TimeRecord9000& lhs, const TimeRecord9000& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
