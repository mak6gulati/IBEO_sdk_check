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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/logmessages/LogMessage64x0Base.hpp>

#include "common/TestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class LogMessage64x0TestSupport : public TestSupport
{
public:
    //========================================
    class OwningVector
    {
    public:
        ~OwningVector();

    public:
        const std::vector<LogMessage64x0Base*> getVector() const { return m_vec; }
        LogMessage64x0Base* operator[](const std::size_t idx) const;

    public:
        void push_back(LogMessage64x0Base* const lm);

    private:
        std::vector<LogMessage64x0Base*> m_vec;
    }; // OwningVector

public:
    LogMessage64x0TestSupport()          = default;
    virtual ~LogMessage64x0TestSupport() = default;

public:
    template<typename MT>
    static MT createMsg();

    template<typename MT>
    static MT createEmptyMsg();

protected:
    static void fillRandomly(LogMessage64x0Base& lme);

    std::unique_ptr<OwningVector> getAllLogMessages() const;

protected:
    static const int32_t nbOfRepeats = 100;
}; // LogMessage64x0TestSupport

//==============================================================================

template<typename MT>
MT LogMessage64x0TestSupport::createMsg()
{
    MT m;
    fillRandomly(m);
    return m;
}

//==============================================================================

template<typename MT>
MT LogMessage64x0TestSupport::createEmptyMsg()
{
    return MT();
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
