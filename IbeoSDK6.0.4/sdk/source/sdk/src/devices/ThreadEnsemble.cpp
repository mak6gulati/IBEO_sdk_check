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
//! \date Oct 22, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/devices/ThreadEnsemble.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ibeo::common::logging::LoggerSPtr ThreadEnsemble::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
