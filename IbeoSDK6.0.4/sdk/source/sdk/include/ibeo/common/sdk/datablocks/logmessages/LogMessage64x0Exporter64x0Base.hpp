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
//!\date Mar 16, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/misc/SdkExceptions.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<class C>
class LogMessage64x0Exporter64x0Base
{
public:
    std::streamsize getSerializedSize(const C* container) const;
    bool serialize(std::ostream& os, const C* container) const;
}; // LogMessage64x0Exporter64x0Base

//==============================================================================

template<class C>
std::streamsize LogMessage64x0Exporter64x0Base<C>::getSerializedSize(const C* container) const
{
    return std::streamsize(1 + container->m_message.size());
}

//==============================================================================

template<class C>
bool LogMessage64x0Exporter64x0Base<C>::serialize(std::ostream& os, const C* container) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(C::msgTraceLevel));
    os.write(container->m_message.c_str(), std::streamsize(container->m_message.size()));

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(container));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
