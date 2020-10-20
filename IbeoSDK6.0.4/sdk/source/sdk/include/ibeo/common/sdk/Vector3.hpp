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
//! \date Jan 16, 2018
//------------------------------------------------------------------------------

#pragma once

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Math.hpp>
#include <ibeo/common/sdk/io_prototypes.hpp>

#include <iostream>
#include <limits>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \class Vector3
//! \brief Vector class for which can store 3 elements (x, y and z).
//! Dedicated to be used for 3d calculations
// ------------------------------------------------------------------------------
template<typename T>
class Vector3
{
public: // type definitions
    //========================================
    using value_type = T;

public: // constructors
    //========================================
    //! \brief Default constructor, initializes x, y and z to 0
    //----------------------------------------
    Vector3() : m_x{0}, m_y{0}, m_z{0} {}

    //========================================
    //! \brief Constructor with member initialization
    //! \param[in] x initialization value for member x
    //! \param[in] y initialization value for member y
    //! \param[in] z initialization value for member z
    //----------------------------------------
    Vector3(const value_type x, const value_type y, const value_type z) : m_x{x}, m_y{y}, m_z{z} {}

    //========================================
    //! \brief Default Destructor
    //----------------------------------------
    virtual ~Vector3() {}

public: // operators
    //========================================
    //! \brief Operator for adding another two vectors
    //! \param[in] other The vector which shall be added to this one
    //! \return A new vector holding the sum of both vectors
    //! \sa operator+=
    //----------------------------------------
    Vector3<value_type> operator+(const Vector3<value_type>& other) const
    {
        return Vector3<value_type>{m_x + other.m_x, m_y + other.m_y, m_z + other.m_z};
    }

    //========================================
    //! \brief Operator for adding another Vector3 to this one
    //! \param[in] other The vector which shall be added to this one
    //! \return The sum of both vectors
    //----------------------------------------
    Vector3<value_type>& operator+=(const Vector3<value_type>& other)
    {
        m_x += other.m_x;
        m_y += other.m_y;
        m_z += other.m_z;
        return *this;
    }

    //========================================
    //! \brief Operator for subtracting two vectors
    //! \param[in] other The vector which shall be subtracted from this one
    //! \return A new vector holding the difference of both vectors
    //! \sa operator-=
    //----------------------------------------
    Vector3<value_type> operator-(const Vector3<value_type>& other) const
    {
        return Vector3<value_type>{m_x - other.m_x, m_y - other.m_y, m_z - other.m_z};
    }

    //========================================
    //! \brief Operator for multipling the Vector with a factor (scales the vector)
    //! \param[in] other The factor which shall be multiplied to the vector
    //! \return The scaled vector
    //! \sa scale
    //----------------------------------------
    Vector3<value_type>& operator-=(const Vector3<value_type>& other)
    {
        m_x -= other.m_x;
        m_y -= other.m_y;
        m_z -= other.m_z;
        return *this;
    }

    //========================================
    //! \brief Operator for multipling the Vector with a factor (scales the vector)
    //! \param[in] factor The factor which shall be multiplied to the vector
    //! \return A new vector which is scaled about the factor
    //----------------------------------------
    Vector3<value_type> operator*(const value_type factor) const
    {
        return Vector3<value_type>{m_x * factor, m_y * factor, m_z * factor};
    }

    //========================================
    //! \brief Operator for multipling the Vector with a factor (scales the vector)
    //! \param[in] factor The factor which shall be multiplied to the vector
    //! \return The scaled vector
    //----------------------------------------
    Vector3<value_type>& operator*=(const value_type factor)
    {
        m_x *= factor;
        m_y *= factor;
        m_z *= factor;
        return *this;
    }

    //========================================
    //! \brief Operator for dividing the vector by a divisor (scales the vector)
    //! \param[in] divisor The divisor which shall be used for scaling the vector
    //! \return A new vector holding a scaled vector
    //! \sa operator/=
    //! \sa getScaled
    //----------------------------------------
    Vector3<value_type> operator/(const value_type divisor) const
    {
        return Vector3<value_type>{m_x / divisor, m_y / divisor, m_z / divisor};
    }

    //========================================
    //! \brief Operator for dividing the Vector by a divisor (scales the vector)
    //! \param[in] divisor The divisor which shall be used for scaling the vector
    //! \return The scaled vector
    //! \sa scale
    //----------------------------------------
    Vector3<value_type>& operator/=(const value_type divisor)
    {
        m_x /= divisor;
        m_y /= divisor;
        m_z /= divisor;
        return *this;
    }

    //========================================
    //! \brief Operator for getting the dot product of two vectors
    //! \param[in] other The vector which shall be multiplied to the first one
    //! \return A scalar value holding the result of the dot product
    //----------------------------------------
    value_type operator*(const Vector3<value_type>& other) const
    {
        return (m_x * other.m_x) + (m_y * other.m_y) + (m_z * other.m_z);
    }

    //========================================
    //! \brief Operator for comparing two vectors for equality
    //! \param[in] other The vector which shall be compared to the first one
    //! \return True, if x, y and z of both vectors are equal, false otherwise
    //----------------------------------------
    bool operator==(const Vector3<value_type>& other) const
    {
        return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
    }

    //========================================
    //! \brief Operator for comparing two vectors for inequality
    //! \param[in] other The vector which shall be compared to the first one
    //! \return False, if x, and z of both vectors are equal, true otherwise
    //----------------------------------------
    bool operator!=(const Vector3<value_type>& other) const { return !(*this == other); }

public: // member functions
    //========================================
    //! \brief Getter function for the x value
    //! \return The x component of the vector
    //----------------------------------------
    value_type getX() const { return m_x; }

    //========================================
    //! \brief Getter function for the y value
    //! \return The y component of the vector
    //----------------------------------------
    value_type getY() const { return m_y; }

    //========================================
    //! \brief Getter function for the z value
    //! \return The z component of the vector
    //----------------------------------------
    value_type getZ() const { return m_z; }

    //========================================
    //! \brief Setter function for the x value
    //! \param[in] val The value which will replace the current x value
    //----------------------------------------
    void setX(const value_type val) { m_x = val; }

    //========================================
    //! \brief Setter function for the y value
    //! \param[in] val The value which will replace the current y value
    //----------------------------------------
    void setY(const value_type val) { m_y = val; }

    //========================================
    //! \brief Setter function for the z value
    //! \param[in] val The value which will replace the current y value
    //----------------------------------------
    void setZ(const value_type val) { m_z = val; }

    //========================================
    //! \brief Calculates the length of the vector
    //! \return The length of the vector
    //----------------------------------------
    value_type getLength() const { return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); }

    //========================================
    //! \brief Calculates the squared length of the vector
    //! \return The squared length of the vector
    //----------------------------------------
    value_type getSquaredLength() const { return m_x * m_x + m_y * m_y + m_z * m_z; }

    //========================================
    //! \brief Calculates the rotation around the x-axis
    //! This is the angle of 2 dimensional vector projected
    //! onto the y-z plane
    //! \return The angle around the x-axis in [rad]
    //----------------------------------------
    value_type getAngleAroundX() const { return std::atan2(m_z, m_y); }

    //========================================
    //! \brief Calculates the rotation around the y-axis
    //! This is the angle of 2 dimensional vector projected
    //! onto the x-z plane
    //! \return The angle around the y-axis in [rad]
    //----------------------------------------
    value_type getAngleAroundY() const { return std::atan2(m_x, m_z); }

    //========================================
    //! \brief Calculates the rotation around the z-axis
    //! This is the angle of 2 dimensional vector projected
    //! onto the x-y plane
    //! \return The angle around the z-axis in [rad]
    //----------------------------------------
    value_type getAngleAroundZ() const { return std::atan2(m_y, m_x); }

    //========================================
    //! \brief Normalizes the vector to have a length of 1
    //----------------------------------------
    void normalize() { *this = getNormalized(); }

    //========================================
    //! \brief Calculates a normalized vector from this on
    //! \return A new normalized vector
    //! \sa normalize
    //----------------------------------------
    Vector3<value_type> getNormalized() const
    {
        if (isZero())
        {
            return *this;
        }

        return *this / getLength();
    }

    //========================================
    //! \brief Scales this vector by a factor
    //! \param[in] The factor which will be used for scaling
    //! \sa operator*=
    //----------------------------------------
    void scale(const value_type factor) { this->operator*=(factor); }

    //========================================
    //! \brief Calculates a scaled version of this vector
    //! \param[in] The factor which will be used for scaling
    //! \return A new vector holding a scaled version of this one
    //! \sa scale
    //----------------------------------------
    Vector3<value_type> getScaled(const value_type factor) { return *this * factor; }

    //========================================
    //! \brief Operator for calculating the cross product of two vectors
    //! \param[in] other The vector which shall used for the cross product
    //! calculation
    //! \return The cross product of the two vectors
    //----------------------------------------
    Vector3<value_type> cross(const Vector3<value_type>& other) const
    {
        return Vector3<value_type>{(m_y * other.m_z) - (m_z * other.m_y),
                                   (m_z * other.m_x) - (m_x * other.m_z),
                                   (m_x * other.m_y) - (m_y * other.m_x)};
    }

    //========================================
    //! \brief Checks this vector to have 0 length
    //! \return True if the vector length is below epsilon
    //! (depends on the template type)
    //! \return True, if length < epsilon, false otherwise
    //----------------------------------------
    bool isZero() const
    {
        T distance{getLength()};
        if (-std::numeric_limits<T>::epsilon() < distance && distance < std::numeric_limits<T>::epsilon())
        {
            return true;
        }

        return false;
    }

    //========================================
    //! \brief Rotates the vector around the x-axis
    //! \param[in] angle The angle in [rad] about the vector shall be rotated
    //! \return A reference to this after rotation
    //----------------------------------------
    Vector3<value_type>& rotateAroundX(const value_type angle)
    {
        *this = getRotatedAroundX(angle);
        return *this;
    }

    //========================================
    //! \brief Rotates the vector around the x-axis
    //! \param[in] angle The angle in [rad] about the vector shall be rotated
    //! \return A new vector holding the rotated vector
    //----------------------------------------
    Vector3<value_type> getRotatedAroundX(const value_type angle) const
    {
        const value_type dCos = std::cos(angle);
        const value_type dSin = std::sin(angle);

        const value_type y = -m_z * dSin + m_y * dCos;
        const value_type z = m_z * dCos + m_y * dSin;

        return Vector3<value_type>{m_x, z, y};
    }

    //========================================
    //! \brief Rotates the vector around the y-axis
    //! \param[in] angle The angle in [rad] about the vector shall be rotated
    //! \return A reference to this after rotation
    //----------------------------------------
    Vector3<value_type>& rotateAroundY(const value_type angle)
    {
        *this = getRotatedAroundY(angle);
        return *this;
    }

    //========================================
    //! \brief Rotates the vector around the y-axis
    //! \param[in] angle The angle in [rad] about the vector shall be rotated
    //! \return A new vector holding the rotated vector
    //----------------------------------------
    Vector3<value_type> getRotatedAroundY(const value_type angle) const
    {
        const value_type dCos = std::cos(angle);
        const value_type dSin = std::sin(angle);

        const value_type x = m_z * dSin + m_x * dCos;
        const value_type z = m_z * dCos - m_x * dSin;

        return Vector3<value_type>{x, m_y, z};
    }

    //========================================
    //! \brief Rotates the vector around the z-axis
    //! \param[in] angle The angle in [rad] about the vector shall be rotated
    //! \return A reference to this after rotation
    //----------------------------------------
    Vector3<value_type>& rotateAroundZ(const value_type angle)
    {
        *this = getRotatedAroundZ(angle);
        return *this;
    }

    //========================================
    //! \brief Rotates the vector around the z-axis
    //! \param[in] angle The angle in [rad] about the vector shall be rotated
    //! \return A new vector holding the rotated vector
    //----------------------------------------
    Vector3<value_type> getRotatedAroundZ(const value_type angle) const
    {
        const value_type dCos = std::cos(angle);
        const value_type dSin = std::sin(angle);

        const value_type x = m_x * dCos - m_y * dSin;
        const value_type y = m_x * dSin + m_y * dCos;

        return Vector3<value_type>{x, y, m_z};
    }

    //========================================

protected: // member variables
    value_type m_x;
    value_type m_y;
    value_type m_z;

public: // friend functions for serialization
    template<typename TT>
    friend void readBE(std::istream& is, Vector3<TT>& value);
    template<typename TT>
    friend void writeBE(std::ostream& os, const Vector3<TT>& value);

public:
    static constexpr bool isSerializable()
    {
        return (std::is_same<value_type, int16_t>{} || std::is_same<value_type, float>{}
                || std::is_same<value_type, double>{});
    }
}; // Vector3

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
std::ostream& operator<<(std::ostream& os, const Vector3<T>& p)
{
    os << "(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
    return os;
}

//==============================================================================
// Serialization
//==============================================================================

//==============================================================================
// specializations
//==============================================================================
template<typename T>
inline void writeBE(std::ostream& os, const Vector3<T>& p)
{
    static_assert(Vector3<T>::isSerializable(), "writeBE is not implemented for given template type of Vector3");

    ibeo::common::sdk::writeBE(os, p.m_x);
    ibeo::common::sdk::writeBE(os, p.m_y);
    ibeo::common::sdk::writeBE(os, p.m_z);
}

//==============================================================================
template<typename T>
inline void readBE(std::istream& is, Vector3<T>& p)
{
    static_assert(Vector3<T>::isSerializable(), "readBE is not implemented for given template type of Vector3");

    ibeo::common::sdk::readBE(is, p.m_x);
    ibeo::common::sdk::readBE(is, p.m_y);
    ibeo::common::sdk::readBE(is, p.m_z);
}

//==============================================================================
template<typename T>
inline constexpr std::streamsize serializedSize(const Vector3<T>&)
{
    static_assert(Vector3<T>::isSerializable(), "serializedSize is not implemented for given template type of Vector3");
    return 3 * sizeof(T);
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
