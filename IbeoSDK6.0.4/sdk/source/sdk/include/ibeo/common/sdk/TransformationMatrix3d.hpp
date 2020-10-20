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

#include <ibeo/common/sdk/RotationMatrix3d.hpp>
#include <ibeo/common/sdk/Vector3.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \class TransformationMatrix3d
//! \brief Transformationmatrix class which holds a 3x3 rotation matrix and
//! a 3x1 dimensional position vector. The size of the matrix is 4x4.
//! The structure is:
//!
//! | rotM   posV |
//! | 0 0 0     1 |
//!
//! Dedicated to be used for 3d coordinate transformations
// ------------------------------------------------------------------------------
template<typename T>
class TransformationMatrix3d
{
public:
    using value_type = T;

public: // constructors
    //========================================
    //! \brief Default constructors which initializes the matrix to an identity
    //! matrix
    //----------------------------------------
    TransformationMatrix3d() : m_rotM{RotationMatrix3d<value_type>{}}, m_posV{Vector3<value_type>{}} {}

    //========================================
    //! \brief Constructor with rotation matrix initialization
    //! \param[in] rm The rotation matrix which shall be used for initialization
    //----------------------------------------
    TransformationMatrix3d(const RotationMatrix3d<value_type>& rm) : m_rotM{rm}, m_posV{Vector3<value_type>{}} {}

    //========================================
    //! \brief constructor with position vector initialization
    //! \param[in] pos The position vector which shall be used for initialization
    //----------------------------------------
    TransformationMatrix3d(const Vector3<value_type>& pos) : m_rotM{RotationMatrix3d<value_type>{}}, m_posV{pos} {}

    //========================================
    //! \brief constructor with rotation matrix and position vector initialization
    //! \param[in] rm The rotation matrix which shall be used for initialization
    //! \param[in] pos The position vector which shall be used for initialization
    //----------------------------------------
    TransformationMatrix3d(const RotationMatrix3d<value_type>& rm, const Vector3<value_type>& pos)
      : m_rotM{rm}, m_posV{pos}
    {}

public: // operators
    //========================================
    //! \brief Multiplies another Transformationmatrix from rigth hand side to
    //! this one. Performs a transformation of the other matrix into the reference
    //! system of this matrix
    //! \param[in] other The matrix which shall be multiplied to this one
    //! \return A reference to this after the calculation
    //----------------------------------------
    TransformationMatrix3d& operator*=(const TransformationMatrix3d<value_type>& other)
    {
        m_posV += m_rotM * other.m_posV;
        m_rotM *= other.m_rotM;
        return *this;
    }

    //========================================
    //! \brief Multiplies another Transformationmatrix from rigth hand side to
    //! this one. Performs a transformation of the other matrix into the reference
    //! system of this matrix
    //! \param[in] other The matrix which shall be multiplied to this one
    //! \return A new TransformationMatrix holding the result of the multiplication
    //----------------------------------------
    TransformationMatrix3d operator*(const TransformationMatrix3d<value_type>& other) const
    {
        return TransformationMatrix3d<value_type>(*this) *= other;
    }

    //========================================
    //! \brief Performs a transformation of a vector into the reference system of
    //! this matrix. Performs a matrix multiplication T*V
    //! \param[in] vector The vector which shall be transformed
    //! \return The transformed vector
    //----------------------------------------
    Vector3<value_type> operator*(const Vector3<value_type>& vector) const { return m_rotM * vector + m_posV; }

    //========================================
    //! \brief Checks two matrices for equality
    //! \param[in] other The matrix which shall be compared to this one
    //! \return True, if all elements of both matrices are equal, false otherwise
    //----------------------------------------
    bool operator==(const TransformationMatrix3d<value_type>& other) const
    {
        return m_rotM == other.m_rotM && m_posV == other.m_posV;
    }

    //========================================
    //! \brief Checks two matrices for inequality
    //! \param[in] other The matrix which shall be compared to this one
    //! \return False, if all elements of both matrices are equal, true otherwise
    //----------------------------------------
    bool operator!=(const TransformationMatrix3d<value_type>& other) const { return !(*this == other); }

public: // member functions
    //========================================
    //! \brief Inverts this transformation matrix. Note that invering
    //! transformation matrices is much cheaper than inverting normal matrices
    //! \return A reference to this after inverting
    //----------------------------------------
    TransformationMatrix3d<value_type>& invert()
    {
        *this = TransformationMatrix3d<value_type>{*this}.getInverse();
        return *this;
    }

    //========================================
    //! \brief Inverts this transformation matrix. Note that invering
    //! transformation matrices is much cheaper than inverting normal matrices
    //! \return A new TransformationMatrix which holds the inverse of this matrix
    //----------------------------------------
    TransformationMatrix3d<value_type> getInverse() const
    {
        RotationMatrix3d<value_type> invRot{m_rotM.getInverse()};
        Vector3<value_type> invPos{-invRot * m_posV};
        return TransformationMatrix3d<value_type>{invRot, invPos};
    }

    //========================================
    //! \brief Rotates the matrix about the x-axis
    //! \param[in] angle The angle in [rad]
    //! \return A reference to this after the rotation
    //----------------------------------------
    TransformationMatrix3d<value_type>& rotateX(const value_type angle)
    {
        *this *= TransformationMatrix3d<value_type>{RotationMatrix3d<value_type>{}.rotateX(angle)};
        return *this;
    }

    //========================================
    //! \brief Rotates the matrix about the x-axis
    //! \param[in] angle The angle in [rad]
    //! \return A new matrix which is rotated
    //----------------------------------------
    TransformationMatrix3d<value_type> getRotatedX(const value_type angle) const
    {
        return TransformationMatrix3d<value_type>{*this}.rotateX(angle);
    }

    //========================================
    //! \brief Rotates the matrix about the y-axis
    //! \param[in] angle The angle in [rad]
    //! \return A reference to this after the rotation
    //----------------------------------------
    TransformationMatrix3d<value_type>& rotateY(const value_type angle)
    {
        *this *= TransformationMatrix3d<value_type>{RotationMatrix3d<value_type>{}.rotateY(angle)};
        return *this;
    }

    //========================================
    //! \brief Rotates the matrix about the Y-axis
    //! \param[in] angle The angle in [rad]
    //! \return A new matrix which is rotated
    //----------------------------------------
    TransformationMatrix3d<value_type> getRotatedY(const value_type angle) const
    {
        return TransformationMatrix3d<value_type>{*this}.rotateY(angle);
    }

    //========================================
    //! \brief Rotates the matrix about the z-axis
    //! \param[in] angle The angle in [rad]
    //! \return A reference to this after the rotation
    //----------------------------------------
    TransformationMatrix3d<value_type>& rotateZ(const value_type angle)
    {
        *this *= TransformationMatrix3d<value_type>{RotationMatrix3d<value_type>{}.rotateZ(angle)};
        return *this;
    }

    //========================================
    //! \brief Rotates the matrix about the z-axis
    //! \param[in] angle The angle in [rad]
    //! \return A new matrix which is rotated
    //----------------------------------------
    TransformationMatrix3d<value_type> getRotatedZ(const value_type angle) const
    {
        return TransformationMatrix3d<value_type>{*this}.rotateZ(angle);
    }

    //========================================
    //! \brief Translates the matrix about a given offset
    //! \param[in] offset A offset vector
    //! \return A reference to this after translation
    //----------------------------------------
    TransformationMatrix3d<value_type>& translate(const Vector3<value_type>& offset)
    {
        *this *= TransformationMatrix3d<value_type>{offset};
        return *this;
    }

    //========================================
    //! \brief Translates the matrix about a given offset
    //! \param[in] offset A offset vector
    //! \return A new matrix which is translated
    //----------------------------------------
    TransformationMatrix3d<value_type> getTranslated(const Vector3<value_type>& offset) const
    {
        return TransformationMatrix3d<value_type>{*this}.translate(offset);
    }

public: // getters
    //========================================
    //! \brief Getter for the rotation matrix part of the transformation matrix
    //! \return The rotation matrix
    //----------------------------------------
    const RotationMatrix3d<value_type>& getRotationMatrix() const { return m_rotM; }

    //========================================
    //! \brief Getter for the position vector part of the transformation matrix
    //! \return The position vector
    //----------------------------------------
    const Vector3<value_type>& getPositionVector() const { return m_posV; }

protected:
    RotationMatrix3d<value_type> m_rotM;
    Vector3<value_type> m_posV;

}; // TransformationMatrix3d

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
