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
//! \date May 3, 2016
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/MeasurementKey.hpp>

#include <ibeo/common/sdk/datablocks/Measurement.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

bool MeasurementKey::compare(const Measurement& m, const MeasurementKey key) { return key == m.getKey(); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
