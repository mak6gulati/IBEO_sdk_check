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
//!\date Mar 26, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/ibeoevent/IbeoEvent7001.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

IbeoEvent7001::IbeoEvent7001() : SpecializedDataContainer{}, m_type{0}, m_body{}, m_author{} {}

//==============================================================================

IbeoEvent7001::IbeoEvent7001(const uint16_t type, const std::string& body, const std::string& author)
  : SpecializedDataContainer{}, m_type{type}, m_body{body}, m_author{author}
{}

//==============================================================================

IbeoEvent7001::IbeoEvent7001(const uint16_t type, const char* const body, const char* const author)
  : SpecializedDataContainer{}, m_type{type}, m_body{body}, m_author{author}
{}

//==============================================================================

//==============================================================================

bool operator==(const IbeoEvent7001& lhs, const IbeoEvent7001& rhs)
{
    return (lhs.getType() == rhs.getType()) && (lhs.getBody() == rhs.getBody()) && (lhs.getAuthor() == rhs.getAuthor());
}

//==============================================================================

bool operator!=(const IbeoEvent7001& lhs, const IbeoEvent7001& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
