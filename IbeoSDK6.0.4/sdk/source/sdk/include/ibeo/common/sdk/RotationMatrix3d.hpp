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

#include <ibeo/common/sdk/Matrix3x3.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \class RotationMatrix3d
//! \brief Matrix class for which can store a 3x3 rotation matrix.
//! Dedicated to be used for 3d calculations
// ------------------------------------------------------------------------------
template<typename T>
class RotationMatrix3d : public Matrix3x3<T>
{
public:
    using value_type = T;

public: // constructors
    //========================================
    //! \brief Default constructors which initializes the matrix to an identity
    //! matrix
    //----------------------------------------
    RotationMatrix3d() : Matrix3x3<value_type>() {}

    //========================================
    //! \brief Constructor for constructing a rotation matrix for which the axis
    //! vector is aligned to an alignment vector
    //! \param[in] alpha The angle in [rad] about the matrix will be rotated
    //----------------------------------------
    RotationMatrix3d(const Vector3<value_type>& axis, const Vector3<value_type>& alignment) : Matrix3x3<value_type>()
    {
        if (alignment.isZero() || axis.isZero())
        {
            *this = RotationMatrix3d<value_type>{};
        }
        else
        {
            Vector3<value_type> a = axis.getNormalized();
            Vector3<value_type> b = alignment.getNormalized();
            value_type c          = a * b; // cosine of the angle
            Vector3<value_type> v = a.cross(b); // cross product

            Matrix3x3<value_type> skew{0, -v.getZ(), v.getY(), v.getZ(), 0, -v.getX(), -v.getY(), v.getX(), 0};

            *this = RotationMatrix3d<value_type>{} + // identity
                    skew + (skew * skew) * (1 / (1 + c));
        } // else
    }

    //========================================
    //! \brief Copy constructor from base class
    //! \param[in] src The source from which this instance shall be filled
    //----------------------------------------
    RotationMatrix3d(const Matrix3x3<value_type>& src) : Matrix3x3<value_type>(src) {}

public:
    //========================================
    //! \brief Rotates the matrix about the x-axis
    //! \param[in] angle The angle in [rad] about which the matrix shall be rotated
    //! \return A reference to this after rotation
    //----------------------------------------
    RotationMatrix3d<value_type>& rotateX(const value_type angle)
    {
        const value_type c = std::cos(angle);
        const value_type s = std::sin(angle);
        *this              = Matrix3x3<value_type>{1, 0, 0, 0, c, -s, 0, s, c};

        return *this;
    }

    //========================================
    //! \brief Rotates the matrix about the x-axis
    //! \param[in] angle The angle in [rad] about which the matrix shall be rotated
    //! \return A new matrix holding the rotated matrix
    //----------------------------------------
    RotationMatrix3d<value_type>& getRotatedX(const value_type angle) const
    {
        return RotationMatrix3d<value_type>{*this}.rotateX(angle);
    }

    //========================================
    //! \brief Rotates the matrix about the y-axis
    //! \param[in] angle The angle in [rad] about which the matrix shall be rotated
    //! \return A reference to this after rotation
    //----------------------------------------
    RotationMatrix3d<value_type>& rotateY(const value_type angle)
    {
        const value_type c = std::cos(angle);
        const value_type s = std::sin(angle);
        *this              = Matrix3x3<value_type>{c, 0, s, 0, 1, 0, -s, 0, c};

        return *this;
    }

    //========================================
    //! \brief Rotates the matrix about the y-axis
    //! \param[in] angle The angle in [rad] about which the matrix shall be rotated
    //! \return A new matrix holding the rotated matrix
    //----------------------------------------
    RotationMatrix3d<value_type>& getRotatedY(const value_type angle) const
    {
        return RotationMatrix3d<value_type>{*this}.rotateY(angle);
    }

    //========================================
    //! \brief Rotates the matrix about the z-axis
    //! \param[in] angle The angle in [rad] about which the matrix shall be rotated
    //! \return A reference to this after rotation
    //----------------------------------------
    RotationMatrix3d<value_type>& rotateZ(const value_type angle)
    {
        const value_type c = std::cos(angle);
        const value_type s = std::sin(angle);
        *this              = Matrix3x3<value_type>{c, -s, 0, s, c, 0, 0, 0, 1};

        return *this;
    }

    //========================================
    //! \brief Rotates the matrix about the z-axis
    //! \param[in] angle The angle in [rad] about which the matrix shall be rotated
    //! \return A new matrix holding the rotated matrix
    //----------------------------------------
    RotationMatrix3d<value_type>& getRotatedZ(const value_type angle) const
    {
        return RotationMatrix3d<value_type>{*this}.rotateZ(angle);
    }

public: // overloaded functions
    //========================================
    //! \brief Inverts the matrix
    //! \return A reference to this after inverting
    //----------------------------------------
    virtual RotationMatrix3d<value_type>& invert() override
    {
        *this = getInverse();
        return *this;
    }

    //========================================
    //! \brief Calculates the inverse of the matrix
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    RotationMatrix3d<value_type> getInverse() const { return this->getTransposed(); }
}; // RotationMatrix3d

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
