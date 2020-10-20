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

#include <ibeo/common/sdk/Matrix2x2.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \class RotationMatrix2d
//! \brief Matrix class for which can store a 2x2 rotation matrix.
//! Dedicated to be used for 2d calculations
// ------------------------------------------------------------------------------
template<typename T>
class RotationMatrix2d : public Matrix2x2<T>
{
public:
    using value_type = T;

public: // constructors
    //========================================
    //! \brief Default constructors which initializes the matrix to an identity
    //! matrix
    //----------------------------------------
    RotationMatrix2d() : Matrix2x2<value_type>() {}

    //========================================
    //! \brief Constructor for constructing a rotation matrix rotated about a
    //! given angle
    //! \param[in] alpha The angle in [rad] about the matrix will be rotated
    //----------------------------------------
    RotationMatrix2d(const value_type alpha)
      : Matrix2x2<value_type>(std::cos(alpha), -std::sin(alpha), std::sin(alpha), std::cos(alpha))
    {}

    //========================================
    //! \brief Copy constructor from base class
    //! \param[in] src The source from which this instance shall be filled
    //----------------------------------------
    RotationMatrix2d(const Matrix2x2<value_type>& src) : Matrix2x2<value_type>(src) {}

    virtual ~RotationMatrix2d() = default;

public: // overloaded functions
        //========================================
    //! \brief Inverts the matrix
    //! \return A reference to this after inverting
    //----------------------------------------
    virtual RotationMatrix2d<value_type>& invert() override
    {
        *this = getInverse();
        return *this;
    }

    //========================================
    //! \brief Calculates the inverse of the matrix
    //! \return A new matrix holding the result of the calculation
    //----------------------------------------
    RotationMatrix2d<value_type> getInverse() const { return this->getTransposed(); }

    //========================================
    //! \brief Calculates the rotation angle of the matrix
    //! \return The rotation angle in [rad]
    //----------------------------------------
    value_type getAngle() const { return std::atan2(this->m_21, this->m_11); }

}; // RotationMatrix2d

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
