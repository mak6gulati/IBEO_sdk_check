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

#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayListExporter6972.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayListSerializedSize6972.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6972Exporter6972.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::CarriageWayList;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_CarriageWayList6972>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return CarriageWayListSerializedSize6972::getSerializedSize(*container);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_CarriageWayList6972>::serialize(std::ostream& os,
                                                                      const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, static_cast<uint64_t>(container->getCarriageWays().size()));

    for (const lanes::CarriageWay::Ptr& cw : container->getCarriageWays())
    {
        // Currently, the general data container is equal to 6972.
        if (!CarriageWayList6972Exporter6972::serialize(os, *cw))
        {
            return false;
        }
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
