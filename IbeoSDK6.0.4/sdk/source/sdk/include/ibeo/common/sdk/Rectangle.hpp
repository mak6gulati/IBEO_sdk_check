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
//! \date Jan 11, 2018
//------------------------------------------------------------------------------

#pragma once

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Math.hpp>
#include <ibeo/common/sdk/Vector2.hpp>
#include <ibeo/common/sdk/io.hpp>

#include <iostream>
#include <limits>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \class Rectangle
//! \brief Vector class for which can store a rectangle with center point and
//! size (x and y extension) and a rotation.
// ------------------------------------------------------------------------------
template<typename T>
class Rectangle
{
public: // type definitions
    //========================================
    using value_type = T;

public: // constructors
    //========================================
    //! \brief Default constructor, all values are initialized with 0
    //----------------------------------------
    Rectangle() : m_center{Vector2<value_type>{}}, m_size{Vector2<value_type>{}}, m_rotation{0} {}

    //========================================
    //! \brief Constructor
    //! \param[in] center The center for the rectangle
    //! \param[in] size The extension in x and y direction
    //! \param[in] rotation The rotation of the rectangle
    //----------------------------------------
    Rectangle(const Vector2<value_type>& center, const Vector2<value_type>& size, const value_type rotation = 0)
      : m_center{center}, m_size{size}, m_rotation{rotation}
    {}

public: // operators
    //========================================
    //! \brief Operator for comparing two rectangles for equality
    //! \param[in] other The rectangle which shall be compared to the first one
    //! \return True, if center, size and rotation of both rectangles are equal,
    //! false otherwise
    //----------------------------------------
    bool operator==(const Rectangle<value_type>& other) const
    {
        return m_center == other.m_center && m_size == other.m_size && m_rotation == other.m_rotation;
    }

    //========================================
    //! \brief Operator for comparing two rectangles for inequality
    //! \param[in] other The rectangle which shall be compared to the first one
    //! \return False, if center, size and rotation of both rectangles are equal,
    //! true otherwise
    //----------------------------------------
    bool operator!=(const Rectangle<value_type>& other) const { return !(*this == other); }

public: // getters and setters
    //========================================
    //! \brief Getter for the center point of the rectangle
    //! \return The center point
    //----------------------------------------
    const Vector2<T>& getCenter() const { return m_center; }

    //========================================
    //! \brief Sets the center point of the rectangle
    //! \param[in] center The new center point for the rectangle
    //----------------------------------------
    void setCenter(const Vector2<T>& center) { m_center = center; }

    //========================================
    //! \brief Getter for the size of the rectangle
    //! \return The size
    //----------------------------------------
    const Vector2<T>& getSize() const { return m_size; }

    //========================================
    //! \brief Sets the size of the rectangle
    //! \param[in] size The new size of the rectangle
    //----------------------------------------
    void setSize(const Vector2<T>& size) { m_size = size; }

    //========================================
    //! \brief Getter for the rotation of the rectangle
    //! \return The rotation angle in [rad]
    //----------------------------------------
    const T getRotation() const { return m_rotation; }

    //========================================
    //! \brief Sets the rotation of the rectangle
    //! \param[in] angle The rotation angle in [rad]
    //----------------------------------------
    void setRotation(const T angle) { m_rotation = angle; }

public: // member functions
    //========================================
    //! \brief Scales the rectangle with given factor
    //! \param[in] factor The factor used for scaling
    //! \return A reference to this after scaling
    //----------------------------------------
    Rectangle<value_type>& scale(const value_type factor)
    {
        m_size.scale(factor);
        return *this;
    }

    //========================================
    //! \brief Scales the rectangle with given factor
    //! \param[in] factor The factor used for scaling
    //! \return A new rectangle which is scaled
    //----------------------------------------
    const Rectangle<value_type>& getScaled(const value_type factor) const
    {
        Rectangle<value_type> ret{*this};
        return ret.scale(factor);
    }

    //========================================
    //! \brief Translates the current rectangle by a given offset
    //! \param[in] offset The offset about the rectangle shall be translated
    //! \return A reference to this after translation
    //----------------------------------------
    Rectangle<value_type>& translate(const Vector2<value_type>& offset)
    {
        m_center += offset;
        return *this;
    }

    //========================================
    //! \brief Translates the current rectangle by a given offset
    //! \param[in] offset The offset about the rectangle shall be translated
    //! \return A new rectangle which is translated
    //----------------------------------------
    const Rectangle<value_type>& translate(const Vector2<value_type>& offset) const
    {
        Rectangle<value_type> ret{*this};
        return ret.translate(offset);
    }

    //========================================
    //! \brief Rotates the rectangle about a given angel
    //! \param[in] angle The angle in [rad] about the rectangle will be rotated
    //! \return A reference to this after rotation
    //----------------------------------------
    Rectangle<value_type>& rotate(const value_type angle)
    {
        m_rotation += angle;
        return *this;
    }

    //========================================
    //! \brief Rotates the rectangle about a given angel
    //! \param[in] angle The angle in [rad] about the rectangle will be rotated
    //! \return A new rectangle which is rotated
    //----------------------------------------
    const Rectangle<value_type>& rotate(const value_type angle) const
    {
        Rectangle<value_type> ret{*this};
        return ret.rotate(angle);
    }

public: // friend functions for serialization
    template<typename TT>
    friend void readBE(std::istream& is, Rectangle<TT>& value);
    template<typename TT>
    friend void writeBE(std::ostream& os, const Rectangle<TT>& value);

public:
    static constexpr bool isSerializable()
    {
        return (std::is_same<value_type, float>{} || std::is_same<value_type, int16_t>{});
    }

protected: // members
    Vector2<T> m_center;
    Vector2<T> m_size;
    T m_rotation;

}; // Rectangle

//==============================================================================
// Serialization
//==============================================================================

//==============================================================================
template<typename T>
inline constexpr std::streamsize serializedSize(const Rectangle<T>&)
{
    static_assert(Rectangle<T>::isSerializable(),
                  "serializedSize is not implemented for given template type of Rectangle");

    return 2 * serializedSize(Vector2<T>{}) + serializedSize(T{});
}

//==============================================================================
template<typename T>
inline void writeBE(std::ostream& os, const Rectangle<T>& p)
{
    static_assert(Rectangle<T>::isSerializable(), "writeBE is not implemented for given template type of Rectangle");

    ibeo::common::sdk::writeBE(os, p.m_center);
    ibeo::common::sdk::writeBE(os, p.m_size);
    ibeo::common::sdk::writeBE(os, p.m_rotation);
}

//==============================================================================
template<typename T>
inline void readBE(std::istream& is, Rectangle<T>& p)
{
    static_assert(Rectangle<T>::isSerializable(), "readBE is not implemented for given template type of Rectangle");

    ibeo::common::sdk::readBE(is, p.m_center);
    ibeo::common::sdk::readBE(is, p.m_size);
    ibeo::common::sdk::readBE(is, p.m_rotation);
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo
