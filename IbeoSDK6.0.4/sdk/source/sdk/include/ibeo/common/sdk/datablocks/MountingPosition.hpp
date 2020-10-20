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
//!\date Jan 16, 2018
///-----------------------------------------------------------------------------

#pragma once

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Math.hpp>
#include <ibeo/common/sdk/Vector3.hpp>
#include <ibeo/common/sdk/io_prototypes.hpp>

#include <iostream>
#include <limits>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//!\class MountingPosition
//!\brief MountingPosition class which stores a mounting position of a Device.
//------------------------------------------------------------------------------
template<typename T>
class MountingPosition
{
public: // type definitions
    //========================================
    using value_type = T;

public:
    static constexpr bool isSerializable()
    {
        return (std::is_same<value_type, float>{} || std::is_same<value_type, int16_t>{});
    }

public: // constructors
    //========================================
    //! \brief Default constructor, initializes all angles and positions to 0
    //----------------------------------------
    MountingPosition() : m_rotation{}, m_position{} {}

    //========================================
    //! \brief Constructor with member initialization
    //! \param[in] yaw yaw angle
    //! \param[in] pitch pitch angle
    //! \param[in] roll roll angle
    //! \param[in] x x position
    //! \param[in] y y position
    //! \param[in] z z position
    //----------------------------------------
    MountingPosition(const value_type yaw,
                     const value_type pitch,
                     const value_type roll,
                     const value_type x,
                     const value_type y,
                     const value_type z)
      : m_rotation{roll, pitch, yaw}, m_position{x, y, z}
    {}

    //========================================
    //! \brief Constructor with member initialization
    //! \param[in] rotation The rotation vector with order roll, pitch, yaw
    //! (x-, y-, z-axis)
    //! \param[in] position The position vector
    //----------------------------------------
    MountingPosition(const Vector3<value_type>& rotation, const Vector3<value_type>& position)
      : m_rotation{rotation}, m_position{position}
    {}

    //========================================
    //! \brief Default Destructor
    //----------------------------------------
    virtual ~MountingPosition() {}

public: // operators
    //========================================
    //! \brief Operator for comparing two vectors for equality
    //! \param[in] other The mounting position which shall be compared to the
    //! first one
    //! \return True, if all angles and positions are equal, false otherwise
    //----------------------------------------
    bool operator==(const MountingPosition<value_type>& other) const
    {
        return m_rotation == other.m_rotation && m_position == other.m_position;
    }

    //========================================
    //! \brief Operator for comparing two vectors for inequality
    //! \param[in] other The vector which shall be compared to the first one
    //! \return False, if x, and z of both vectors are equal, true otherwise
    //----------------------------------------
    bool operator!=(const MountingPosition<value_type>& other) const { return !(*this == other); }

public: // member functions
    //========================================
    //! \brief Getter function for the yaw angle
    //! \return The yaw angle of the mounting position
    //----------------------------------------
    value_type getYaw() const { return m_rotation.getZ(); }

    //========================================
    //! \brief Getter function for the pitch angle
    //! \return The pitch angle of the mounting position
    value_type getPitch() const { return m_rotation.getY(); }

    //========================================
    //! \brief Getter function for the roll angle
    //! \return The roll angle of the mounting position
    value_type getRoll() const { return m_rotation.getX(); }

    //========================================
    //! \brief Getter function for the x value
    //! \return The x component of the vector
    //----------------------------------------
    value_type getX() const { return m_position.getX(); }

    //========================================
    //! \brief Getter function for the y value
    //! \return The y component of the vector
    //----------------------------------------
    value_type getY() const { return m_position.getY(); }

    //========================================
    //! \brief Getter function for the z value
    //! \return The z component of the vector
    //----------------------------------------
    value_type getZ() const { return m_position.getZ(); }

    //========================================
    //! \brief Getter for the position vector
    //! \return A constant reference to the position vector
    //----------------------------------------
    const Vector3<value_type>& getPosition() const { return m_position; }

    //========================================
    //! \brief Getter for the rotation vector (roll, pitch, yaw)
    //! \return A constant reference to the rotation vector
    //----------------------------------------
    const Vector3<value_type>& getRotation() const { return m_rotation; }

    //========================================
    //! \brief Setter function for the yaw angle
    //! \param[in] val The value which will replace the current yaw angle
    //----------------------------------------
    void setYaw(const value_type val) { m_rotation.setZ(val); }

    //========================================
    //! \brief Setter function for the pitch angle
    //! \param[in] val The value which will replace the current pitch angle
    //----------------------------------------
    void setPitch(const value_type val) { m_rotation.setY(val); }

    //========================================
    //! \brief Setter function for the roll angle
    //! \param[in] val The value which will replace the current roll angle
    //----------------------------------------
    void setRoll(const value_type val) { m_rotation.setX(val); }

    //========================================
    //! \brief Setter function for the x value
    //! \param[in] val The value which will replace the current x value
    //----------------------------------------
    void setX(const value_type val) { m_position.setX(val); }

    //========================================
    //! \brief Setter function for the y value
    //! \param[in] val The value which will replace the current y value
    //----------------------------------------
    void setY(const value_type val) { m_position.setY(val); }

    //========================================
    //! \brief Setter function for the z value
    //! \param[in] val The value which will replace the current y value
    //----------------------------------------
    void setZ(const value_type val) { m_position.setZ(val); }

    //========================================
    //! \brief Setter for the position vector
    //! \param[in] position The new position vector
    //----------------------------------------
    void setPosition(const Vector3<value_type>& position) { m_position = position; }

    //========================================
    //! \brief Setter for the position vector (roll, pitch, yaw)
    //! \param[in] rotation The new position vector
    //----------------------------------------
    void setRotation(const Vector3<value_type>& rotation) { m_rotation = rotation; }

public: // member functions
    //========================================
    //! \brief Normalizes the angles to be in the range of [-PI,PI]
    //! \return A reference to this after normalization
    //----------------------------------------
    MountingPosition<value_type>& normalizeAngles()
    {
        m_rotation.setX(ibeo::common::sdk::normalizeRadians(m_rotation.getX()));
        m_rotation.setY(ibeo::common::sdk::normalizeRadians(m_rotation.getY()));
        m_rotation.setZ(ibeo::common::sdk::normalizeRadians(m_rotation.getZ()));
        return *this;
    }

    //========================================

protected: // member variables
    Vector3<value_type> m_rotation;
    Vector3<value_type> m_position;

public: // friend functions for serialization
    template<typename TT>
    friend void readBE(std::istream& is, MountingPosition<TT>& value);
    template<typename TT>
    friend void writeBE(std::ostream& os, const MountingPosition<TT>& value);
}; // MountingPosition

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================
//! \brief Stream operator for writing the vector content to a stream
//! \param[in] os The stream, the vector shall be written to
//! \param[in] p The vector which shall be streamed
//! \return The stream to which the vector was written to
//------------------------------------------------------------------------------
template<typename T>
inline std::ostream& operator<<(std::ostream& os, const MountingPosition<T>& p)
{
    os << "(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
    return os;
}

//==============================================================================

//==============================================================================
// Serialization
//==============================================================================

template<typename T>
inline void writeBE(std::ostream& os, const MountingPosition<T>& p)
{
    static_assert(MountingPosition<T>::isSerializable(),
                  "writeBE is not implemented for given template type of MountingPosition");

    ibeo::common::sdk::writeBE(os, p.getYaw());
    ibeo::common::sdk::writeBE(os, p.getPitch());
    ibeo::common::sdk::writeBE(os, p.getRoll());
    ibeo::common::sdk::writeBE(os, p.m_position);
}

//==============================================================================

template<typename T>
inline void readBE(std::istream& is, MountingPosition<T>& p)
{
    static_assert(MountingPosition<T>::isSerializable(),
                  "readBE is not implemented for given template type of MountingPosition");

    T yaw, pitch, roll;
    ibeo::common::sdk::readBE(is, yaw);
    ibeo::common::sdk::readBE(is, pitch);
    ibeo::common::sdk::readBE(is, roll);
    ibeo::common::sdk::readBE(is, p.m_position);

    p.setYaw(yaw);
    p.setPitch(pitch);
    p.setRoll(roll);
}

//==============================================================================

template<typename T>
inline constexpr std::streamsize serializedSize(const MountingPosition<T>&)
{
    static_assert(MountingPosition<T>::isSerializable(),
                  "serializedSize is not implemented for given template type of MountingPosition");

    return std::streamsize{3 * sizeof(T)} + serializedSize(Vector3<T>{});
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
