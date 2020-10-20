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
//!\date Feb 4th, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/contentseparator/ContentSeparator.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class ContentSeparatorTestSupport : public TestSupport
{
public:
    ContentSeparatorTestSupport();
    virtual ~ContentSeparatorTestSupport() = default;

public:
    template<typename T>
    T createContentSeparator();

public:
    template<typename T>
    static void fillRandomly(T& vs);

protected:
    static const int32_t nbOfRepeats = 100;
}; // ContentSeparatorTestSupport

//==============================================================================

template<typename T>
T ContentSeparatorTestSupport::createContentSeparator()
{
    T contentseparator;
    fillRandomly(contentseparator);
    return contentseparator;
}

//==============================================================================

// specialization for ContentSeparator
template<>
ibeo::common::sdk::ContentSeparator ContentSeparatorTestSupport::createContentSeparator<ContentSeparator>();

//==============================================================================

template<>
void ContentSeparatorTestSupport::fillRandomly(ContentSeparator& contentSeparator);

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
