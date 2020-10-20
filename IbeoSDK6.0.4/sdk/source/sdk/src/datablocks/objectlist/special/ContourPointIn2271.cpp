//==============================================================================
//!\file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Apr 23, 2014
//------------------------------------------------------------------------------

//==============================================================================
//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlist/special/ContourPointIn2271.hpp>
#include <ibeo/common/sdk/io.hpp>

#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ContourPointIn2271::ContourPointIn2271(const Vector2<int16_t> pt) : m_x(pt.getX()), m_y(pt.getY()) {}

//==============================================================================

bool ContourPointIn2271::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_x);
    ibeo::common::sdk::readBE(is, m_y);
    ibeo::common::sdk::readBE(is, m_xSigma);
    ibeo::common::sdk::readBE(is, m_ySigma);
    ibeo::common::sdk::readBE(is, m_corrCoeff);
    ibeo::common::sdk::readBE(is, m_existenceProbability);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ContourPointIn2271::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_x);
    ibeo::common::sdk::writeBE(os, m_y);
    ibeo::common::sdk::writeBE(os, m_xSigma);
    ibeo::common::sdk::writeBE(os, m_ySigma);
    ibeo::common::sdk::writeBE(os, m_corrCoeff);
    ibeo::common::sdk::writeBE(os, m_existenceProbability);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================
//==============================================================================
//==============================================================================

bool operator==(const ContourPointIn2271& lhs, const ContourPointIn2271& rhs)
{
    if (lhs.getX() != rhs.getX())
    {
        return false;
    }
    if (lhs.getY() != rhs.getY())
    {
        return false;
    }
    if (lhs.getXSigma() != rhs.getXSigma())
    {
        return false;
    }
    if (lhs.getYSigma() != rhs.getYSigma())
    {
        return false;
    }
    if (lhs.getCorrCoeff() != rhs.getCorrCoeff())
    {
        return false;
    }
    if (lhs.getExistenceProbability() != rhs.getExistenceProbability())
    {
        return false;
    }

    return true;
}

//==============================================================================

bool operator!=(const ContourPointIn2271& lhs, const ContourPointIn2271& rhs)
{
    if (lhs.getX() != rhs.getX())
    {
        return true;
    }
    if (lhs.getY() != rhs.getY())
    {
        return true;
    }
    if (lhs.getXSigma() != rhs.getXSigma())
    {
        return true;
    }
    if (lhs.getYSigma() != rhs.getYSigma())
    {
        return true;
    }
    if (lhs.getCorrCoeff() != rhs.getCorrCoeff())
    {
        return true;
    }
    if (lhs.getExistenceProbability() != rhs.getExistenceProbability())
    {
        return true;
    }

    return false;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
