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

#include <ibeo/common/sdk/RotationMatrix2d.hpp>
#include <ibeo/common/sdk/Vector2.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \class TransformationMatrix2d
//! \brief Transformationmatrix class which holds a 2x2 rotation matrix and
//! a 2x1 dimensional position vector. The size of the matrix is 3x3.
//! The structure is:
//!
//! | rotM posV |
//! | 0  0    1 |
//!
//! Dedicated to be used for 2d coordinate transformations
// ------------------------------------------------------------------------------
template<typename T>
class TransformationMatrix2d
{
public:
    using value_type = T;

public: // constructors
    //========================================
    //! \brief Default constructors which initializes the matrix to an identity
    //! matrix
    //----------------------------------------
    TransformationMatrix2d() : m_rotM{RotationMatrix2d<value_type>{}}, m_posV{Vector2<value_type>{}} {}

    //========================================
    //! \brief Constructor with rotation matrix initialization
    //! \param[in] rm The rotation matrix which shall be used for initialization
    //----------------------------------------
    TransformationMatrix2d(const RotationMatrix2d<value_type>& rm) : m_rotM{rm}, m_posV{Vector2<value_type>{}} {}

    //========================================
    //! \brief constructor with position vector initialization
    //! \param[in] pos The position vector which shall be used for initialization
    //----------------------------------------
    TransformationMatrix2d(const Vector2<value_type>& pos) : m_rotM{RotationMatrix2d<value_type>{}}, m_posV{pos} {}

    //========================================
    //! \brief constructor with rotation matrix and position vector initialization
    //! \param[in] rm The rotation matrix which shall be used for initialization
    //! \param[in] pos The position vector which shall be used for initialization
    //----------------------------------------
    TransformationMatrix2d(const RotationMatrix2d<value_type>& rm, const Vector2<value_type>& pos)
      : m_rotM{rm}, m_posV{pos}
    {}

    //========================================
    //! \brief constructor with angle and position vector initialization
    //! \param[in] angle The angle in [rad] from which the rotation matrix shall
    //! be initialized
    //! \param[in] pos The position vector which shall be used for initialization
    //----------------------------------------
    TransformationMatrix2d(const value_type angle, const Vector2<value_type>& pos)
      : m_rotM{RotationMatrix2d<value_type>{angle}}, m_posV{pos}
    {}

    //========================================
    //! \brief constructor with angle initialization
    //! \param[in] angle The angle in [rad] from which the rotation matrix shall
    //! be initialized
    //----------------------------------------
    TransformationMatrix2d(const value_type angle)
      : m_rotM{RotationMatrix2d<value_type>{angle}}, m_posV{Vector2<value_type>{}}
    {}

public: // operators
    //========================================
    //! \brief Multiplies another Transformationmatrix from rigth hand side to
    //! this one. Performs a transformation of the other matrix into the reference
    //! system of this matrix
    //! \param[in] other The matrix which shall be multiplied to this one
    //! \return A reference to this after the calculation
    //----------------------------------------
    TransformationMatrix2d& operator*=(const TransformationMatrix2d<value_type>& other)
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
    TransformationMatrix2d operator*(const TransformationMatrix2d<value_type>& other) const
    {
        return TransformationMatrix2d<value_type>(*this) *= other;
    }

    //========================================
    //! \brief Performs a transformation of a vector into the reference system of
    //! this matrix. Performs a matrix multiplication T*V
    //! \param[in] vector The vector which shall be transformed
    //! \return The transformed vector
    //----------------------------------------
    Vector2<value_type> operator*(const Vector2<value_type>& vector) const { return (m_rotM * vector) + m_posV; }

    //========================================
    //! \brief Checks two matrices for equality
    //! \param[in] other The matrix which shall be compared to this one
    //! \return True, if all elements of both matrices are equal, false otherwise
    //----------------------------------------
    bool operator==(const TransformationMatrix2d<value_type>& other) const
    {
        return m_rotM == other.m_rotM && m_posV == other.m_posV;
    }

    //========================================
    //! \brief Checks two matrices for inequality
    //! \param[in] other The matrix which shall be compared to this one
    //! \return False, if all elements of both matrices are equal, true otherwise
    //----------------------------------------
    bool operator!=(const TransformationMatrix2d<value_type>& other) const { return !(*this == other); }

public: // member functions
    //========================================
    //!\brief Inverts this transformation matrix. Note that inverting
    //!       transformation matrices is much cheaper than inverting
    //!       normal matrices
    //!\return A reference to this after inverting.
    //----------------------------------------
    TransformationMatrix2d<value_type>& invert()
    {
        *this = TransformationMatrix2d<value_type>{*this}.getInverse();
        return *this;
    }

    //========================================
    //! \brief Inverts this transformation matrix. Note that invering
    //! transformation matrices is much cheaper than inverting normal matrices
    //! \return A new TransformationMatrix which holds the inverse of this matrix
    //----------------------------------------
    TransformationMatrix2d<value_type> getInverse() const
    {
        RotationMatrix2d<value_type> invRot{m_rotM.getInverse()};
        Vector2<value_type> invPos{-invRot * m_posV};
        return TransformationMatrix2d<value_type>{invRot, invPos};
    }

    //========================================
    //! \brief Rotates the matrix about the x-axis
    //! \param[in] angle The angle in [rad]
    //! \return A reference to this after the rotation
    //----------------------------------------
    TransformationMatrix2d<value_type>& rotateX(const value_type angle)
    {
        *this *= TransformationMatrix2d<value_type>{RotationMatrix2d<value_type>{}.rotateX(angle)};
        return *this;
    }

    //========================================
    //! \brief Rotates the matrix about the x-axis
    //! \param[in] angle The angle in [rad]
    //! \return A new matrix which is rotated
    //----------------------------------------
    TransformationMatrix2d<value_type> getRotatedX(const value_type angle) const
    {
        return TransformationMatrix2d<value_type>{*this}.rotateX(angle);
    }

    //========================================
    //! \brief Rotates the matrix about the y-axis
    //! \param[in] angle The angle in [rad]
    //! \return A reference to this after the rotation
    //----------------------------------------
    TransformationMatrix2d<value_type>& rotateY(const value_type angle)
    {
        *this *= TransformationMatrix2d<value_type>{RotationMatrix2d<value_type>{}.rotateY(angle)};
        return *this;
    }

    //========================================
    //! \brief Rotates the matrix about the Y-axis
    //! \param[in] angle The angle in [rad]
    //! \return A new matrix which is rotated
    //----------------------------------------
    TransformationMatrix2d<value_type> getRotatedY(const value_type angle) const
    {
        return TransformationMatrix2d<value_type>{*this}.rotateY(angle);
    }

    //========================================
    //! \brief Translates the matrix about a given offset
    //! \param[in] offset A offset vector
    //! \return A reference to this after translation
    //----------------------------------------
    TransformationMatrix2d<value_type>& translate(const Vector2<value_type>& offset)
    {
        *this *= TransformationMatrix2d<value_type>{offset};
        return *this;
    }

    //========================================
    //! \brief Translates the matrix about a given offset
    //! \param[in] offset A offset vector
    //! \return A new matrix which is translated
    //----------------------------------------
    TransformationMatrix2d<value_type> getTranslated(const Vector2<value_type>& offset) const
    {
        return TransformationMatrix2d<value_type>{*this}.translate(offset);
    }

public: // getters
    //========================================
    //! \brief Getter for the rotation matrix part of the transformation matrix
    //! \return The rotation matrix
    //----------------------------------------
    const RotationMatrix2d<value_type>& getRotationMatrix() const { return m_rotM; }

    //========================================
    //! \brief Getter for the position vector part of the transformation matrix
    //! \return The position vector
    //----------------------------------------
    const Vector2<value_type>& getPositionVector() const { return m_posV; }

protected:
    RotationMatrix2d<value_type> m_rotM;
    Vector2<value_type> m_posV;

}; // TransformationMatrix2d

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
