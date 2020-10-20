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
//! \date Dec 19, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

CarriageWayList::CarriageWayList() : DataContainerBase{} {}

//==============================================================================

bool operator==(const CarriageWayList& lhs, const CarriageWayList& rhs)
{
    // std::shared_ptr simply compares pointer values. We need to compare the objects here.
    if (lhs.getCarriageWays().size() != rhs.getCarriageWays().size())
    {
        return false;
    }

    for (std::size_t index = 0; index < lhs.getCarriageWays().size(); ++index)
    {
        // Do not compare shared pointers, but objects they point to.
        const lanes::CarriageWay::Ptr& cwLeft{lhs.getCarriageWays()[index]};
        const lanes::CarriageWay::Ptr& cwRight{rhs.getCarriageWays()[index]};

        if (lanes::CarriageWay::areSharedPtrObjectsEqual(cwLeft, cwRight) == false)
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
