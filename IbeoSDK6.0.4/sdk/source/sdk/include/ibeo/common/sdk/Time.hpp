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
//!\date Jul 4, 2012
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/io_prototypes.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/noncopyable.hpp>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <time.h>
#include <string.h>
#include <assert.h>

#if defined _WIN32 && defined(IBEOSDKLIBDLL_SHARED)
#    pragma warning(push)
#    pragma warning(disable : 4251)
#endif // _WIN32 && IBEOSDKLIBDLL_SHARED

#ifdef _WIN32
#    if _MSC_VER < 1800 //VS 2013 is not tested 1900 == VS 2015
struct timespec
{
    time_t tv_sec;
    time_t tv_nsec;
};
#    endif //  before VS 2013

using nanoseconds_t = time_t;
#else // _WIN32
using nanoseconds_t = long int;
#endif // _WIN32

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace time {
//==============================================================================

//==============================================================================
//!\brief Return the real-time clock of the system.
//!\return The current UTC time
//!\sa ibeo::localTime()
//------------------------------------------------------------------------------
boost::posix_time::ptime universalTime();

//==============================================================================
//!\brief Return the real-time clock of the system.
//!\return The current UTC time
//!\sa ibeo::universalTime()
//------------------------------------------------------------------------------
boost::posix_time::ptime localTime();

//==============================================================================
} // namespace time
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class TimeConversion : private boost::noncopyable
{
public:
    TimeConversion();
    TimeConversion(const std::string& formatStr);
    ~TimeConversion();

public:
    const char* toString(const timespec ts, const int secPrecision = 0) const;
    const char* toString(const tm& ltime, const nanoseconds_t nanoseconds, const int secPrecision = 0) const;
    const char* toString(const time_t secs) const;
    //	const char* toString(const long int secs, const uint32_t nSecs, const uint32_t nbOfDigits) const;
    std::string toString(const boost::posix_time::ptime ts, const int secPrecision = 0) const;

    std::string toStdString(const time_t secs) const;

protected:
    static const int szDefaultFmt = 18;
    static const char defaultFmt[szDefaultFmt];

    static const int szTimeStr = 64;

protected:
    char* fmt;
    mutable char timeStr[szTimeStr];
}; // TimeConversion

//==============================================================================

class IBEOSDK_API NTPTime
{
public:
    static NTPTime getInvalidTime()
    {
        NTPTime t;
        t.setInvalid();
        return t;
    }

public:
    NTPTime() : m_Time(0) {}
    NTPTime(const uint64_t time) : m_Time(time) {}
    NTPTime(const uint32_t sec, const uint32_t frac) : m_Time(0) { this->set(sec, frac); }

    NTPTime(const boost::posix_time::ptime& timestamp);

public: // Assignment operators
    NTPTime& operator=(const uint64_t u)
    {
        m_Time = u;
        return *this;
    }
    NTPTime& operator+=(const NTPTime& Q)
    {
        m_Time += Q.m_Time;
        return *this;
    }
    NTPTime& operator-=(const NTPTime& Q)
    {
        m_Time -= Q.m_Time;
        return *this;
    }

public: // Cast operators
    operator uint64_t() const { return this->m_Time; }

public: // comparison operators
    bool operator==(const NTPTime& other) const { return (m_Time == other.m_Time); }
    bool operator!=(const NTPTime& other) const { return (m_Time != other.m_Time); }
    bool operator>=(const NTPTime& other) const { return (m_Time >= other.m_Time); }
    bool operator>(const NTPTime& other) const { return (m_Time > other.m_Time); }
    bool operator<=(const NTPTime& other) const { return (m_Time <= other.m_Time); }
    bool operator<(const NTPTime& other) const { return (m_Time < other.m_Time); }

public: // arithmetic operators
    NTPTime operator+(const NTPTime& other) const
    {
        NTPTime result = *this;
        result += other;
        return result;
    }

    NTPTime operator-(const NTPTime& other) const
    {
        NTPTime result = *this;
        result -= other;
        return result;
    }

public:
    //! returns the current time in seconds.
    uint32_t getSeconds() const { return ((uint32_t)(m_Time >> 32)); }
    //! returns the fractional part of the second
    uint32_t getFracSeconds() const { return ((uint32_t)(m_Time & 0xFFFFFFFF)); }
    //! returns the current time in milli seconds. take care for possible overflow.
    uint32_t getMilliseconds() const
    {
        const uint64_t t = 1000 * m_Time;
        return (uint32_t)((t >> 32) & 0xFFFFFFFF);
    }
    //! returns the current time in micro seconds. take care for possible overflow.
    uint32_t getMicroseconds() const
    {
        const uint64_t t = 125 * m_Time / 536871;
        return (uint32_t)(t & 0xFFFFFFFF);
    }
    //! returns the current time in nano seconds.
    uint64_t getNanoseconds() const
    {
        return static_cast<uint64_t>(round(static_cast<double>(m_Time) / nanosecondsToSecondFractionNTP));
    }
    // TODO find faster algorithm avoiding double?
    //! returns the time in seconds and microseconds (micros: 0..1000 0000). conversion error: 0.. -7.6 us.
    void getTime_s_us(uint32_t& sec, uint32_t& us) const
    {
        sec = getSeconds();
        us  = getFracSeconds() / 4295;
    }
    uint64_t getTime(void) const { return m_Time; }

public:
    //! set the time in seconds and microseconds (micros: 0..1000 0000)
    //! This routine uses the factorization: 2^32/10^6 = 4096 + 256 - 1825/32
    void setTime_s_us(const uint32_t sec, const uint32_t us)
    {
        m_Time = ((uint64_t)sec << 32) | ((us << 12) - ((us * 1852) >> 5) + (us << 8));
    }

    void set(const uint64_t& u) { m_Time = u; }
    void set(const uint32_t sec, const uint32_t frac)
    {
        m_Time = sec;
        m_Time = m_Time << 32;
        m_Time |= frac;
    }

    void setInvalid() { m_Time = uint64_t(NOT_A_DATE_TIME) << 32; }

    void setSeconds(const uint32_t u) { m_Time = static_cast<uint64_t>(u) << 32; }
    //! This routine uses the factorization
    //! 2^32/10^6 = 4096 + 256 - 1825/32
    void setMicroseconds(const uint32_t u)
    {
        const uint64_t t = (static_cast<uint64_t>(u) * 1825) >> 5;
        m_Time           = (static_cast<uint64_t>(u) << 12) + (static_cast<uint64_t>(u) << 8) - t;
    }
    void setMicroseconds(const uint64_t u)
    {
        const uint64_t t = (u * 1825) >> 5;
        m_Time           = (u << 12) + (u << 8) - t;
    }
    void setMilliseconds(const uint32_t u) { m_Time = static_cast<uint64_t>(u) * 536870912 / 125; }
    void setNanoseconds(const uint64_t u)
    {
        m_Time = static_cast<uint64_t>(round(static_cast<double>(u) * nanosecondsToSecondFractionNTP));
    }
    // TODO find faster algorithm avoiding double?

    void addSeconds(const uint32_t s)
    {
        NTPTime t;
        t.setSeconds(s);
        *this += t;
    }
    void addMilliseconds(const uint32_t m)
    {
        NTPTime t;
        t.setMilliseconds(m);
        *this += t;
    }
    void addMicroseconds(const uint32_t u)
    {
        NTPTime t;
        t.setMicroseconds(u);
        *this += t;
    }
    void addNanoseconds(const uint64_t n)
    {
        NTPTime t;
        t.setNanoseconds(n);
        *this += t;
    }
    void subSeconds(const uint32_t s)
    {
        NTPTime t;
        t.setSeconds(s);
        *this -= t;
    }
    void subMilliseconds(const uint32_t m)
    {
        NTPTime t;
        t.setMilliseconds(m);
        *this -= t;
    }
    void subMicroseconds(const uint32_t u)
    {
        NTPTime t;
        t.setMicroseconds(u);
        *this -= t;
    }
    void subNanoseconds(const uint64_t n)
    {
        NTPTime t;
        t.setNanoseconds(n);
        *this -= t;
    }

public:
    //	timespec toTimeSpec() const; // NTP epoch 1-1-1900, Posix epoch 1-1-1970
    boost::posix_time::time_duration toTimeDurationSinceEpoch() const;
    boost::posix_time::ptime toPtime() const;

    //! Returns true if this timestamp does not represent an actual
    //! time, and toPTime() would return a
    //! boost::posix_time::not_a_date_time.
    bool is_not_a_date_time() const;

    void setFromPTime(const boost::posix_time::ptime& timestamp);

protected:
    static double round(const double v);

private:
    //========================================
    //!\brief Constants to convert fractions of a second: 1/(2^32) s (NTP) to nanoseconds (1e-9 s).
    //!
    //! For efficiency, the NTP epoch and factors to convert between ns and 1/(2^32)s
    //! are saved in static variables that are computed only once at system initialization.
    //! \sa epoch()
    //----------------------------------------
    static const double secondFractionNTPtoNanoseconds;
    static const double nanosecondsToSecondFractionNTP;
    //! Representation of a not_a_date_time value in the serialization
    static const uint32_t NOT_A_DATE_TIME;
    static const uint64_t NOT_A_DATE_TIME64;
    static const boost::posix_time::ptime m_epoch;

protected:
    uint64_t m_Time; //!< NTP time in 1/2^32 seconds (~233 ps)

public: // friend functions for serialization
    template<typename TT>
    friend void readBE(std::istream& is, TT& value);
    template<typename TT>
    friend void readLE(std::istream& is, TT& value);
    template<typename TT>
    friend void writeBE(std::ostream& os, const TT& value);
    template<typename TT>
    friend void writeLE(std::ostream& os, const TT& value);
}; // NTPTime

//==============================================================================

template<>
inline void readBE<NTPTime>(std::istream& is, NTPTime& t)
{
    ibeo::common::sdk::readBE(is, t.m_Time);
}

//==============================================================================
template<>
inline void readLE<NTPTime>(std::istream& is, NTPTime& t)
{
    ibeo::common::sdk::readLE(is, t.m_Time);
}

//==============================================================================
template<>
inline void writeBE<NTPTime>(std::ostream& os, const NTPTime& t)
{
    ibeo::common::sdk::writeBE(os, t.m_Time);
}

//==============================================================================
template<>
inline void writeLE<NTPTime>(std::ostream& os, const NTPTime& t)
{
    ibeo::common::sdk::writeLE(os, t.m_Time);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

#if defined _WIN32 && defined(IBEOSDKLIBDLL_SHARED)
#    pragma warning(pop)
#endif // _WIN32 && IBEOSDKLIBDLL_SHARED
