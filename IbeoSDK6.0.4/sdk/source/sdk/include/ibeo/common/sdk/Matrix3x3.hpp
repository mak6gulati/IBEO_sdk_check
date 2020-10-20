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

#include <ibeo/common/sdk/io_prototypes.hpp>
#include <ibeo/common/sdk/Vector3.hpp>
#include <ibeo/common/sdk/Math.hpp>

#include <iostream>
#include <limits>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \class Matrix3x3
//! \brief Matrix class for which can store a 3x3 matrix.
//! Dedicated to be used for 3d calculations
// ------------------------------------------------------------------------------
template<typename T>
class Matrix3x3
{
public:
    using value_type = T;

public:
    //========================================
    //! \brief Default constructor.
    //! Initializes the matrix to be an identity matrix
    //----------------------------------------
    Matrix3x3() : m_11{1}, m_12{0}, m_13{0}, m_21{0}, m_22{1}, m_23{0}, m_31{0}, m_32{0}, m_33{1} {}

    //========================================
    //! \brief Entry wise constructor
    //----------------------------------------
    Matrix3x3(const value_type m11,
              const value_type m12,
              const value_type m13,
              const value_type m21,
              const value_type m22,
              const value_type m23,
              const value_type m31,
              const value_type m32,
              const value_type m33)
      : m_11{m11}, m_12{m12}, m_13{m13}, m_21{m21}, m_22{m22}, m_23{m23}, m_31{m31}, m_32{m32}, m_33{m33}
    {}

    virtual ~Matrix3x3() = default;

public: // operators
    //========================================
    //! \brief Adds another matrix to this one
    //! \param[in] other The matrix which shall be added to this one
    //! \return a reference to this after the calculation
    //----------------------------------------
    Matrix3x3<value_type>& operator+=(const Matrix3x3<value_type>& other)
    {
        m_11 += other.m_11;
        m_12 += other.m_12;
        m_13 += other.m_13;
        m_21 += other.m_21;
        m_22 += other.m_22;
        m_23 += other.m_23;
        m_31 += other.m_31;
        m_32 += other.m_32;
        m_33 += other.m_33;
        return *this;
    }

    //========================================
    //! \brief Adds another matrix to this one
    //! \param[in] other The matrix which shall be added to this one
    //! \return A new matrix holding the result of the calculation
    Matrix3x3<value_type> operator+(const Matrix3x3<value_type>& other) const
    {
        return Matrix3x3<value_type>{*this} += other;
    }

    //========================================
    //! \brief Subtracts another matrix from this one
    //! \param[in] other The matrix which shall be subtracted from this one
    //! \return a reference to this after the calculation
    //----------------------------------------
    Matrix3x3<value_type>& operator-=(const Matrix3x3<value_type>& other)
    {
        m_11 -= other.m_11;
        m_12 -= other.m_12;
        m_13 -= other.m_13;
        m_21 -= other.m_21;
        m_22 -= other.m_22;
        m_23 -= other.m_23;
        m_31 -= other.m_31;
        m_32 -= other.m_32;
        m_33 -= other.m_33;
        return *this;
    }

    //========================================
    //! \brief Subtracts another matrix from this one
    //! \param[in] other The matrix which shall be subtracted from this one
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    Matrix3x3<value_type> operator-(const Matrix3x3<value_type>& other) const
    {
        return Matrix3x3<value_type>{*this} -= other;
    }

    //========================================
    //! \brief Multiplies the matrix by a factor
    //! \param[in] factor the factor which shall be used for the calculation
    //! \return A reference to this after the calculation
    //----------------------------------------
    Matrix3x3<value_type>& operator*=(const value_type factor)
    {
        m_11 *= factor;
        m_12 *= factor;
        m_13 *= factor;
        m_21 *= factor;
        m_22 *= factor;
        m_23 *= factor;
        m_31 *= factor;
        m_32 *= factor;
        m_33 *= factor;
        return *this;
    }

    //========================================
    //! \brief Multiplies the matrix by a factor
    //! \param[in] factor the factor which shall be used for the calculation
    //! \return A new Matrix holding the result of the calculation
    //----------------------------------------
    Matrix3x3<value_type> operator*(const value_type factor) const { return Matrix3x3<value_type>{*this} *= factor; }

    //========================================
    //! \brief Matrix-Vector multiplication M*V
    //! \param[in] vector The vector which shall be multiplied to this matrix
    //! \return A vector holding the result of the calculation
    //----------------------------------------
    Vector3<value_type> operator*(const Vector3<value_type>& vector) const
    {
        return Vector3<value_type>{m_11 * vector.getX() + m_12 * vector.getY() + m_13 * vector.getZ(),
                                   m_21 * vector.getX() + m_22 * vector.getY() + m_23 * vector.getZ(),
                                   m_31 * vector.getX() + m_32 * vector.getY() + m_33 * vector.getZ()};
    }

    //========================================
    //! \brief Vector-Matrix multiplication V*M
    //! \param[in] vector The vector which shall be multiplied to the matrix
    //! \param[in] matrix The matrix which shall be used for the operation
    //! \return A vector holding the result of the calculation
    //----------------------------------------
    friend Vector3<value_type> operator*(const Vector3<value_type>& vector, const Matrix3x3<value_type>& matrix)
    {
        return Vector3<value_type>{
            vector.getX() * matrix.m_11 + vector.getY() * matrix.m_21 + vector.getZ() * matrix.m_31,
            vector.getX() * matrix.m_12 + vector.getY() * matrix.m_22 + vector.getZ() * matrix.m_32,
            vector.getX() * matrix.m_13 + vector.getY() * matrix.m_23 + vector.getZ() * matrix.m_33};
    }

    //========================================
    //! \brief Matrix-Matrix multiplication M*M
    //! \param[in] other The matrix which shall by multiplied to this one
    //! \return A reference to this after the calculation
    //----------------------------------------
    Matrix3x3<value_type>& operator*=(const Matrix3x3<value_type>& other)
    {
        *this = Matrix3x3<value_type>{m_11 * other.m_11 + m_12 * other.m_21 + m_13 * other.m_31,
                                      m_11 * other.m_12 + m_12 * other.m_22 + m_13 * other.m_32,
                                      m_11 * other.m_13 + m_12 * other.m_23 + m_13 * other.m_33,
                                      m_21 * other.m_11 + m_22 * other.m_21 + m_23 * other.m_31,
                                      m_21 * other.m_12 + m_22 * other.m_22 + m_23 * other.m_32,
                                      m_21 * other.m_13 + m_22 * other.m_23 + m_23 * other.m_33,
                                      m_31 * other.m_11 + m_32 * other.m_21 + m_33 * other.m_31,
                                      m_31 * other.m_12 + m_32 * other.m_22 + m_33 * other.m_32,
                                      m_31 * other.m_13 + m_32 * other.m_23 + m_33 * other.m_33};

        return *this;
    }

    //========================================
    //! \brief Matrix-Matrix multiplication M*M
    //! \param[in] other The matrix which shall by multiplied to this one
    //! \return The result of the calculation
    //----------------------------------------
    Matrix3x3<value_type> operator*(const Matrix3x3<value_type>& other) const
    {
        return Matrix3x3<value_type>{*this} *= other;
    }

    //========================================
    //! \brief Matrix division by a divisor. Divides all matrix entries by a
    //! given divisor
    //! \param[in] division The divisor for the division calculation
    //! \return A reference to this after the calculation
    //----------------------------------------
    Matrix3x3<value_type>& operator/=(const value_type divisor)
    {
        m_11 /= divisor;
        m_12 /= divisor;
        m_13 /= divisor;
        m_21 /= divisor;
        m_22 /= divisor;
        m_23 /= divisor;
        m_31 /= divisor;
        m_32 /= divisor;
        m_33 /= divisor;

        return *this;
    }

    //========================================
    //! \brief Matrix division by a divisor. Divides all matrix entries by a
    //! given divisor
    //! \param[in] division The divisor for the division calculation
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    Matrix3x3<value_type> operator/(const value_type divisor) const { return Matrix3x3<value_type>{*this} /= divisor; }

    //========================================
    //! \brief Negates the matrix
    //! \return A new matrix which is negated
    //----------------------------------------
    Matrix3x3<value_type> operator-() const { return Matrix3x3<value_type>{0, 0, 0, 0, 0, 0, 0, 0, 0} -= *this; }

    //========================================
    //! \brief Checks to matrices for equality
    //! \param[in] other The matrix, this matrix shall be compared to
    //! \return True, if all elements in the matrix are identical to
    //! the entries of the other matrix, false otherwise
    //----------------------------------------
    bool operator==(const Matrix3x3<value_type>& other) const
    {
        return m_11 == other.m_11 && m_12 == other.m_12 && m_13 == other.m_13 && m_21 == other.m_21
               && m_22 == other.m_22 && m_23 == other.m_23 && m_31 == other.m_31 && m_32 == other.m_32
               && m_33 == other.m_33;
    }

    //========================================
    //! \brief Checks to matrices for inequality
    //! \param[in] other The matrix, this matrix shall be compared to
    //! \return False, if all elements in the matrix are identical to
    //! the entries of the other matrix, true otherwise
    //----------------------------------------
    bool operator!=(const Matrix3x3<value_type>& other) const { return !(*this == other); }

public: // member functions
    //========================================
    //! \brief Transposes the matrix
    //! \return A reference to this after transposing
    //----------------------------------------
    Matrix3x3<value_type>& transpose()
    {
        *this = getTransposed();
        return *this;
    }

    //========================================
    //! \brief Calculates the transposed of the matrix
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    Matrix3x3<value_type> getTransposed() const
    {
        return Matrix3x3<value_type>{m_11, m_21, m_31, m_12, m_22, m_32, m_13, m_23, m_33};
    }

    //========================================
    //! \brief Calculates the determinant of the matrix
    //! \return The determinant
    //----------------------------------------
    value_type getDeterminant() const
    {
        return m_11 * (m_22 * m_33 - m_32 * m_23) + m_21 * (m_32 * m_13 - m_12 * m_33)
               + m_31 * (m_12 * m_23 - m_22 * m_13);
    }

    //========================================
    //! \brief Calculates the adjoint of this matrix
    //! \return A reference to this after the calculation
    //----------------------------------------
    Matrix3x3<value_type>& adjoint()
    {
        *this = getAdjoint();
        return *this;
    }

    //========================================
    //! \brief Calculates the adjoint of this matrix
    //! \return A new matrix holding the adjoint of this matrix
    //----------------------------------------
    Matrix3x3<value_type> getAdjoint() const
    {
        return Matrix3x3<value_type>{m_22 * m_33 - m_23 * m_32,
                                     m_13 * m_32 - m_12 * m_33,
                                     m_12 * m_23 - m_13 * m_22,
                                     m_23 * m_31 - m_21 * m_33,
                                     m_11 * m_33 - m_13 * m_31,
                                     m_13 * m_21 - m_11 * m_23,
                                     m_21 * m_32 - m_22 * m_31,
                                     m_12 * m_31 - m_11 * m_32,
                                     m_11 * m_22 - m_12 * m_21};
    }

    //========================================
    //! \brief Inverts the matrix
    //! \return A reference to this after inverting
    //----------------------------------------
    virtual Matrix3x3<value_type>& invert()
    {
        *this = getInverse();
        return *this;
    }

    //========================================
    //! \brief Calculates the inverse of the matrix
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    Matrix3x3<value_type> getInverse() const { return getAdjoint() / getDeterminant(); }

    //========================================
    //! \brief Resets this matrix to hold an identity matrix
    //! \return A reference to this after resetting to identity
    //----------------------------------------
    Matrix3x3<value_type>& setToIdentity()
    {
        m_11 = value_type{1};
        m_12 = value_type{0};
        m_13 = value_type{0};

        m_21 = value_type{0};
        m_22 = value_type{1};
        m_23 = value_type{0};

        m_31 = value_type{0};
        m_32 = value_type{0};
        m_33 = value_type{1};

        return *this;
    }

public: // getter functions
    //========================================
    //! \brief Getter for element wise access to the elements
    //! \param[in] row The row index of the element to access. Starts at 1
    //! \param[in] col The row index of the element to access. Starts at 1
    //! \return The matrix element value at the given indices
    value_type get(const uint8_t row, const uint8_t col) const
    {
        switch (row)
        {
        case 1:
        {
            switch (col)
            {
            case 1:
                return m_11;
            case 2:
                return m_12;
            case 3:
                return m_13;
            default:
                return static_cast<value_type>(NAN);
            }
        }
        break;
        case 2:
        {
            switch (col)
            {
            case 1:
                return m_21;
            case 2:
                return m_22;
            case 3:
                return m_23;
            default:
                return static_cast<value_type>(NAN);
            }
        }
        break;

        case 3:
        {
            switch (col)
            {
            case 1:
                return m_31;
            case 2:
                return m_32;
            case 3:
                return m_33;
            default:
                return static_cast<value_type>(NAN);
            }
        }
        break;

        default:
            return static_cast<value_type>(NAN);
        }
    }

protected:
    value_type m_11;
    value_type m_12;
    value_type m_13;
    value_type m_21;
    value_type m_22;
    value_type m_23;
    value_type m_31;
    value_type m_32;
    value_type m_33;
}; // Matrix3x3

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
