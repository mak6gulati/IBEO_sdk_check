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
//!\date Feb 12, 2018
//------------------------------------------------------------------------------

#include <logMessage64x0Tests/LogMessage64x0TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/logmessages/LogMessageDebug6430.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageNote6420.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageWarning6410.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageError6400.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

LogMessage64x0TestSupport::OwningVector::~OwningVector()
{
    for (auto b : m_vec)
    {
        delete b;
    }
}

//==============================================================================

void LogMessage64x0TestSupport::OwningVector::push_back(LogMessage64x0Base* const lm) { m_vec.push_back(lm); }

//==============================================================================

LogMessage64x0Base* LogMessage64x0TestSupport ::OwningVector::operator[](const std::size_t idx) const
{
    return m_vec[idx];
}

//==============================================================================
//==============================================================================
//==============================================================================

void LogMessage64x0TestSupport::fillRandomly(LogMessage64x0Base& lme)
{
    const uint16_t len = uint16_t(getRandValue<uint16_t>(uint16_t(std::numeric_limits<uint16_t>::max() - 1)) + 1);
    lme.setMessage(getOrdinaryAsciiString(len));
}

//==============================================================================

std::unique_ptr<LogMessage64x0TestSupport::OwningVector> LogMessage64x0TestSupport ::getAllLogMessages() const
{
    std::unique_ptr<OwningVector> vec{new OwningVector};

    vec->push_back(new LogMessageError6400);
    vec->push_back(new LogMessageWarning6410);
    vec->push_back(new LogMessageNote6420);
    vec->push_back(new LogMessageDebug6430);

    return vec;
}
//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
