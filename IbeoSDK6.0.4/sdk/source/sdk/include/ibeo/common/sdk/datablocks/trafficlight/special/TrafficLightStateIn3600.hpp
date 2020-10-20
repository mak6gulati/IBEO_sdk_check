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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Time.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! Traffic light state, including the phase's absolute and relative
//! interval length if supported by the traffic light
class TrafficLightStateIn3600
{
public:
    //! Representation of all possible traffic light phases
    enum class Phase : uint8_t //uint8_t but serialized as uint32_t
    {
        Red      = 0, //!< Traffic light signals "red".
        RedAmber = 1, //!< Traffic light signals "red" and "amber". Just after "red" phase, presumably only in Germany
        Amber    = 2, //!< Traffic light signals "amber". After "green" phase
        Green    = 3, //!< Traffic light signals "green".
        Off      = 4 //!< Traffic light signals nothing or "amber" blinking.
    };

public:
    //! \brief Returns the serialized size
    //! \return Serialized size
    static std::streamsize getSerializedSize_static()
    {
        return 2 * std::streamsize(sizeof(uint32_t)) + 5 * std::streamsize(sizeof(NTPTime));
    }

public:
    TrafficLightStateIn3600()  = default;
    ~TrafficLightStateIn3600() = default;

public:
    //! \brief Get the size of the serialization.
    //! \return Number of bytes used by the serialization of this data class.
    virtual std::streamsize getSerializedSize() const;

    //! \brief Deserialize data from the given stream \a is into this class.
    //! \param[in, out] is Stream that provides the serialized data to fill this class. On exit
    //!                 the \a is get pointer will be behind the read data.
    //! \return Whether the operation was successful.
    virtual bool deserialize(std::istream& is);

    //! \brief Serialize data into the given stream \a os.
    //! \param[out] os Stream that receive the serialized data from this class.
    //! \return Whether the operation was successful.
    virtual bool serialize(std::ostream& os) const;

public: //getter and setter
    //! \brief Gets id.
    //! \return id
    uint32_t getId() const { return m_id; }

    //! \brief Sets id.
    //! \param[in] id Desired id
    void setId(const uint32_t id) { m_id = id; }

    //! \brief Gets phase.
    //! \return phase
    Phase getPhase() const { return m_phase; }

    //! \brief Sets phase.
    //! \param[in] phase Desired phase
    void setPhase(const Phase phase) { m_phase = phase; }

    //! \brief Gets timestamp set by traffic light when generating message.
    //! \return Timestamp from traffic light
    NTPTime getTimestampFromTrafficLight() const { return m_timestampFromTrafficLight; }

    //! \brief Sets timestamp set by traffic light when generating message
    //! \param[in] Desired timestamp from traffic light
    void setTimestampFromTrafficLight(const NTPTime timestampFromTrafficLight)
    {
        m_timestampFromTrafficLight = timestampFromTrafficLight;
    }

    //! \brief Gets phase's absolute time interval begin.
    //! \return Phase's absolute time interval begin
    NTPTime getTimeIntervalAbsoluteBegin() const { return m_timeIntervalAbsoluteBegin; }

    //! \brief Sets phase's absolute time interval begin.
    //! \param[in] Desired phase's absolute time interval begin
    void setTimeIntervalAbsoluteBegin(const NTPTime timeIntervalAbsoluteBegin)
    {
        m_timeIntervalAbsoluteBegin = timeIntervalAbsoluteBegin;
    }

    //! \brief Gets phase's absolute time interval end.
    //! \return Phase's absolute time interval end
    NTPTime getTimeIntervalAbsoluteEnd() const { return m_timeIntervalAbsoluteEnd; }

    //! \brief Sets phase's absolute time interval end.
    //! \param[in] Desired phase's absolute time interval end
    void setTimeIntervalAbsoluteEnd(const NTPTime timeIntervalAbsoluteEnd)
    {
        m_timeIntervalAbsoluteEnd = timeIntervalAbsoluteEnd;
    }

    //! \brief Gets phase's relative time interval begin.
    //! \return Phase's relative time interval begin
    NTPTime getTimeIntervalRelativeBegin() const { return m_timeIntervalRelativeBegin; }

    //! \brief Sets phase's relative time interval begin.
    //! \param[in] Desired phase's relative time interval begin
    void setTimeIntervalRelativeBegin(const NTPTime timeIntervalRelativeBegin)
    {
        m_timeIntervalRelativeBegin = timeIntervalRelativeBegin;
    }

    //! \brief Gets phase's relative time interval end.
    //! \return Phase's relative time interval end
    NTPTime getTimeIntervalRelativeEnd() const { return m_timeIntervalRelativeEnd; }

    //! \brief Sets phase's relative time interval end.
    //! \param timeIntervalRelativeEnd Desired phase's relative time interval end
    void setTimeIntervalRelativeEnd(const NTPTime timeIntervalRelativeEnd)
    {
        m_timeIntervalRelativeEnd = timeIntervalRelativeEnd;
    }

private:
    uint32_t m_id{0}; //!< Unique identifier
    Phase m_phase{Phase::Off}; //!< Current phase
    NTPTime m_timestampFromTrafficLight{}; //!< timestamp set by the traffic light when it is sending its phase

    NTPTime m_timeIntervalAbsoluteBegin{}; //!< absolute time interval begin in which the phase is valid.
        //!< Only sent if supported by the traffic light.
    NTPTime m_timeIntervalAbsoluteEnd{}; //!< absolute time interval end in which the phase is valid.
        //!< Only sent if supported by the traffic light.
    NTPTime m_timeIntervalRelativeBegin{}; //!< Relative time interval begin in which the phase is valid.
        //!< Only sent if supported by the traffic light.
    NTPTime m_timeIntervalRelativeEnd{}; //!< Absolute time interval end in which the phase is valid.
        //!< Only sent if supported by the traffic light.

}; // TrafficLightState

//==============================================================================

bool operator==(const TrafficLightStateIn3600& lhs, const TrafficLightStateIn3600& rhs);
bool operator!=(const TrafficLightStateIn3600& lhs, const TrafficLightStateIn3600& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
