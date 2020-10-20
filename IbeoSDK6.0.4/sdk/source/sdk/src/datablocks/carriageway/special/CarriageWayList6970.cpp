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
//!\date Apr 4, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6970.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

CarriageWayList6970::CarriageWayList6970() : SpecializedDataContainer{} {}

//==============================================================================

bool operator==(const CarriageWayList6970& lhs, const CarriageWayList6970& rhs)
{
    // std::shared_ptr simply compares pointer values. We need to compare the objects here.
    if (lhs.getCarriageWays().size() != rhs.getCarriageWays().size())
    {
        return false;
    }

    for (std::size_t index = 0; index < lhs.getCarriageWays().size(); ++index)
    {
        // Do not compare shared pointers, but objects they point to.
        const lanes::CarriageWayIn6970::Ptr& cwLeft{lhs.getCarriageWays()[index]};
        const lanes::CarriageWayIn6970::Ptr& cwRight{rhs.getCarriageWays()[index]};

        if (lanes::CarriageWayIn6970::areSharedPtrObjectsEqual(cwLeft, cwRight) == false)
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
