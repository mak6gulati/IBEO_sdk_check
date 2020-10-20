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
//! \date Jan 13, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/measurementlist/MeasurementList2821.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

MeasurementList2821::MeasurementList2821() : SpecializedDataContainer() {}

//==============================================================================

MeasurementList2821::~MeasurementList2821() {}

//==============================================================================

//==============================================================================

bool operator==(const MeasurementList2821& lhs, const MeasurementList2821& rhs)
{
    if (lhs.getMicroseconds() != rhs.getMicroseconds())
        return false;

    if (lhs.getTimestamp() != rhs.getTimestamp())
        return false;

    if (lhs.getListName() != rhs.getListName())
        return false;

    if (lhs.getGroupName() != rhs.getGroupName())
        return false;

    if (lhs.getMeasList() != rhs.getMeasList())
        return false;

    return true;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
