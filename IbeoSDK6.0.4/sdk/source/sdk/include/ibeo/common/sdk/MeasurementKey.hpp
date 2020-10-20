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
//! \date Jul 29, 2014
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/misc/Unconvertable.hpp>

#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/bufferIO.hpp>

#include <boost/functional/hash.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

class Measurement;

//==============================================================================

class MeasurementKey : public ibeo::common::sdk::ComparableUnconvertable<uint16_t>
{
public:
    static bool compare(const Measurement& m, const MeasurementKey key);

public:
    //======================================================================
    //! \brief Ids of some DataTypes. For convenience.
    //-------------------------------------------------------------------
    enum KeyValues
    {
        Key_Undefined = 0,

        VelocityX                = 1, ///< [m/s] in vehicle coordinate system ("Forward velocity"); (double)
        YawRate                  = 2, ///< [rad/s] in vehicle coordinate system; (double)
        CrossAcceleration        = 4, ///< [m/s^2] in vehicle coordinate system; (double)
        LongitudinalAcceleration = 6, ///< [m/s^2] in vehicle coordinate system; (double)
        RollAngle                = 7, ///< [rad]; (double)
        PitchAngle               = 8, ///< [rad]; (double)

        VerticalAcceleration = 43, ///< [m/s^2] in vehicle coordinate system; (double)
        PitchRate            = 44, ///< [rad/s] in vehicle coordinate system; (double)
        RollRate             = 45, ///< [rad/s] in vehicle coordinate system; (double)

        VelocityNorth = 49, ///!< [m/s]; (double)
        VelocityUp    = 50, ///!< [m/s]; (double)
        VelocityWest  = 51, ///!< [m/s]; (double)

        Latitude  = 60, ///< [rad] WGS84-Latitude; (double)
        Longitude = 61, ///< [rad] WGS84-Longitude; (double)
        Altitude  = 62, ///< [m] Height above sea level; (double)

        YawAngle = 67, ///< [rad]; (double)

        UTCHours        = 70, ///< (uint8_t)
        UTCMinutes      = 71, ///< (uint8_t)
        UTCSeconds      = 72, ///< (uint8_t)
        UTCMilliSeconds = 73, ///< (uint32_t)
        UTCDays         = 79, ///< (uint8_t)
        UTCMonths       = 80, ///< (uint8_t)
        UTCYears        = 81, ///< (uint16_t)

        // Values from 400 to 4xx are specific to ECU Extended Tracking.
        // Corresponding declarations can be found in ObjectIn2281.hpp.

        // (Object) Label
        LabelUserData = 600, //!< (string)

        // Oela
        Oela_EgoLaneProjectionX          = 700,
        Oela_EgoLaneProjectionY          = 701,
        Oela_LateralEgoLaneDistance      = 702,
        Oela_LongitudinalEgoLaneDistance = 703,
        Oela_EgoLaneFlag                 = 704,

        RearMonitoringFlag = 705
    }; // KeyValues

public:
    explicit MeasurementKey(const uint16_t key) : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(key) {}

    MeasurementKey(const KeyValues key) : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(key) {}
    MeasurementKey(const MeasurementKey& key) : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(uint16_t(key)) {}
    MeasurementKey() : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(uint16_t(Key_Undefined)) {}

public:
    bool isSet() const { return (this->m_data != 0); }
    void unSet() { this->m_data = uint16_t(0); }

public:
    static std::streamsize getSerializedSize() { return sizeof(uint16_t); }

public:
    std::istream& readBE(std::istream& is)
    {
        ibeo::common::sdk::readBE(is, this->m_data);
        return is;
    }

    std::ostream& writeBE(std::ostream& os) const
    {
        ibeo::common::sdk::writeBE(os, this->m_data);
        return os;
    }

    void readBE(const char*& target) { ibeo::common::sdk::readBE(target, this->m_data); }

    void writeBE(char*& target) const { ibeo::common::sdk::writeBE(target, this->m_data); }

public: // friend functions for serialization
    template<typename TT>
    friend void readBE(std::istream& is, TT& value);
    template<typename TT>
    friend void writeBE(std::ostream& os, const TT& value);
}; // MeasurementKey

//==============================================================================

//==============================================================================
// Serialization
//==============================================================================

//==============================================================================
template<>
inline void readBE<MeasurementKey>(std::istream& is, MeasurementKey& k)
{
    ibeo::common::sdk::readBE(is, k.m_data);
}

//==============================================================================
template<>
inline void writeBE<MeasurementKey>(std::ostream& os, const MeasurementKey& k)
{
    ibeo::common::sdk::writeBE(os, k.m_data);
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
//==============================================================================
//==============================================================================

namespace boost {

//==============================================================================

template<>
struct hash<ibeo::common::sdk::MeasurementKey>
{
    std::size_t operator()(ibeo::common::sdk::MeasurementKey const& key) const
    {
        hash<uint16_t> h;
        return h(key);
    }
}; // :hash<DataTypeId>

//==============================================================================

} // namespace boost

//==============================================================================
