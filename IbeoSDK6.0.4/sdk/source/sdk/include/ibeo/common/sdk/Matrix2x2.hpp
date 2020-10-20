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
#include <ibeo/common/sdk/Vector2.hpp>
#include <ibeo/common/sdk/Math.hpp>

#include <iostream>
#include <limits>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \class Matrix2x2
//! \brief Matrix class for which can store a 2x2 matrix.
//! Dedicated to be used for 2d calculations
// ------------------------------------------------------------------------------
template<typename T>
class Matrix2x2
{
public:
    using value_type = T;

public:
    //========================================
    //! \brief Default constructor.
    //! Initializes the matrix to be an identity matrix
    //----------------------------------------
    Matrix2x2() : m_11{1}, m_12{0}, m_21{0}, m_22{1} {}

    //========================================
    //! \brief Entry wise constructor
    //----------------------------------------
    Matrix2x2(const value_type m11, const value_type m12, const value_type m21, const value_type m22)
      : m_11{m11}, m_12{m12}, m_21{m21}, m_22{m22}
    {}

    virtual ~Matrix2x2() = default;

public: // operators
    //========================================
    //! \brief Adds another matrix to this one
    //! \param[in] other The matrix which shall be added to this one
    //! \return a reference to this after the calculation
    //----------------------------------------
    Matrix2x2<value_type>& operator+=(const Matrix2x2<value_type>& other)
    {
        m_11 += other.m_11;
        m_12 += other.m_12;
        m_21 += other.m_21;
        m_22 += other.m_22;
        return *this;
    }

    //========================================
    //! \brief Adds another matrix to this one
    //! \param[in] other The matrix which shall be added to this one
    //! \return A new matrix holding the result of the calculation
    Matrix2x2<value_type> operator+(const Matrix2x2<value_type>& other) const
    {
        return Matrix2x2<value_type>{*this} += other;
    }

    //========================================
    //! \brief Subtracts another matrix from this one
    //! \param[in] other The matrix which shall be subtracted from this one
    //! \return a reference to this after the calculation
    //----------------------------------------
    Matrix2x2<value_type>& operator-=(const Matrix2x2<value_type>& other)
    {
        m_11 -= other.m_11;
        m_12 -= other.m_12;
        m_21 -= other.m_21;
        m_22 -= other.m_22;
        return *this;
    }

    //========================================
    //! \brief Subtracts another matrix from this one
    //! \param[in] other The matrix which shall be subtracted from this one
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    Matrix2x2<value_type> operator-(const Matrix2x2<value_type>& other) const
    {
        return Matrix2x2<value_type>{*this} -= other;
    }

    //========================================
    //! \brief Multiplies the matrix by a factor
    //! \param[in] factor the factor which shall be used for the calculation
    //! \return A reference to this after the calculation
    //----------------------------------------
    Matrix2x2<value_type>& operator*=(const value_type factor)
    {
        m_11 *= factor;
        m_12 *= factor;
        m_21 *= factor;
        m_22 *= factor;
        return *this;
    }

    //========================================
    //! \brief Multiplies the matrix by a factor
    //! \param[in] factor the factor which shall be used for the calculation
    //! \return A new Matrix holding the result of the calculation
    //----------------------------------------
    Matrix2x2<value_type> operator*(const value_type factor) const { return Matrix2x2<value_type>{*this} *= factor; }

    //========================================
    //! \brief Matrix-Vector multiplication M*V
    //! \param[in] vector The vector which shall be multiplied to this matrix
    //! \return A vector holding the result of the calculation
    //----------------------------------------
    Vector2<value_type> operator*(const Vector2<value_type>& vector) const
    {
        return Vector2<value_type>{m_11 * vector.getX() + m_12 * vector.getY(),
                                   m_21 * vector.getX() + m_22 * vector.getY()};
    }

    //========================================
    //! \brief Vector-Matrix multiplication V*M
    //! \param[in] vector The vector which shall be multiplied to the matrix
    //! \param[in] matrix The matrix which shall be used for the operation
    //! \return A vector holding the result of the calculation
    //----------------------------------------
    friend Vector2<value_type> operator*(const Vector2<value_type>& vector, const Matrix2x2<value_type>& matrix)
    {
        return Vector2<value_type>{vector.getX() * matrix.m_11 + vector.getY() * matrix.m_21,
                                   vector.getX() * matrix.m_12 + vector.getY() * matrix.m_22};
    }

    //========================================
    //! \brief Matrix-Matrix multiplication M*M
    //! \param[in] other The matrix which shall by multiplied to this one
    //! \return A reference to this after the calculation
    //----------------------------------------
    Matrix2x2<value_type>& operator*=(const Matrix2x2<value_type>& other)
    {
        *this = Matrix2x2<value_type>{m_11 * other.m_11 + m_12 * other.m_21,
                                      m_11 * other.m_12 + m_12 * other.m_22,
                                      m_21 * other.m_11 + m_22 * other.m_21,
                                      m_21 * other.m_12 + m_22 * other.m_22};

        return *this;
    }

    //========================================
    //! \brief Matrix-Matrix multiplication M*M
    //! \param[in] other The matrix which shall by multiplied to this one
    //! \return The result of the calculation
    //----------------------------------------
    Matrix2x2<value_type> operator*(const Matrix2x2<value_type>& other) const
    {
        return Matrix2x2<value_type>{*this} *= other;
    }

    //========================================
    //! \brief Matrix division by a divisor. Divides all matrix entries by a
    //! given divisor
    //! \param[in] division The divisor for the division calculation
    //! \return A reference to this after the calculation
    //----------------------------------------
    Matrix2x2<value_type>& operator/=(const value_type divisor)
    {
        m_11 /= divisor;
        m_12 /= divisor;
        m_21 /= divisor;
        m_22 /= divisor;

        return *this;
    }

    //========================================
    //! \brief Matrix division by a divisor. Divides all matrix entries by a
    //! given divisor
    //! \param[in] division The divisor for the division calculation
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    Matrix2x2<value_type> operator/(const value_type divisor) const { return Matrix2x2<value_type>{*this} /= divisor; }

    //========================================
    //! \brief Negates the matrix
    //! \return A new matrix which is negated
    //----------------------------------------
    Matrix2x2<value_type> operator-() const
    {
        return Matrix2x2<value_type>{-m_11, -m_12, -m_21, -m_22};
        ;
    }

    //========================================
    //! \brief Checks to matrices for equality
    //! \param[in] other The matrix, this matrix shall be compared to
    //! \return True, if all elements in the matrix are identical to
    //! the entries of the other matrix, false otherwise
    //----------------------------------------
    bool operator==(const Matrix2x2<value_type>& other) const
    {
        return m_11 == other.m_11 && m_12 == other.m_12 && m_21 == other.m_21 && m_22 == other.m_22;
    }

    //========================================
    //! \brief Checks to matrices for inequality
    //! \param[in] other The matrix, this matrix shall be compared to
    //! \return False, if all elements in the matrix are identical to
    //! the entries of the other matrix, true otherwise
    //----------------------------------------
    bool operator!=(const Matrix2x2<value_type>& other) const { return !(*this == other); }

public: // member functions
    //========================================
    //! \brief Transposes the matrix
    //! \return A reference to this after transposing
    //----------------------------------------
    Matrix2x2<value_type>& transpose()
    {
        *this = getTransposed();
        return *this;
    }

    //========================================
    //! \brief Calculates the transposed of the matrix
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    Matrix2x2<value_type> getTransposed() const { return Matrix2x2<value_type>{m_11, m_21, m_12, m_22}; }

    //========================================
    //! \brief Calculates the determinant of the matrix
    //! \return The determinant
    //----------------------------------------
    value_type getDeterminant() const { return m_11 * m_22 - m_12 * m_21; }

    //========================================
    //! \brief Inverts the matrix
    //! \return A reference to this after inverting
    //----------------------------------------
    virtual Matrix2x2<value_type>& invert()
    {
        *this = getInverse();
        return *this;
    }

    //========================================
    //! \brief Calculates the inverse of the matrix
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    Matrix2x2<value_type> getInverse() const
    {
        auto factor = static_cast<value_type>(1.0) / getDeterminant();
        return Matrix2x2<value_type>{m_22 * factor, -m_12 * factor, -m_21 * factor, m_11 * factor};
    }

public: // getters
    //========================================
    //! \brief Getter for element wise access to the elements
    //! \param[in] row The row index of the element to access. Starts at 1
    //! \param[in] col The row index of the element to access. Starts at 1
    //! \return The matrix element value at the given indices
    //----------------------------------------
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
            default:
                return static_cast<value_type>(NAN);
            }
            break;
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
    value_type m_21;
    value_type m_22;
}; // Matrix2x2

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
