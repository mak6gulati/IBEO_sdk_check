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
//! \date Mar 14, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/IbeoSdk.hpp>
#include <version_defines.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

const Version& IbeoSdk::getVersion()
{
    static Version sdkVersion(Version::MajorVersion(VERSION_MAJOR),
                              Version::MinorVersion(VERSION_MINOR),
                              Version::Revision(VERSION_PATCH),
                              Version::PatchLevel(),
                              Version::Build(),
                              VERSION_EXTRA);

    return sdkVersion;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
