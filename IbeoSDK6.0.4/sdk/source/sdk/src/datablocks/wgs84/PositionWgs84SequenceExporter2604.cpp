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
//!\date 15.November 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84SequenceExporter2604.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::PositionWgs84Sequence;
} //namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_PositionWgs84_2604>::getSerializedSize(const DataContainerBase& c) const
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

    return container->getPositionSequence().front().getSerializedSize();
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_PositionWgs84_2604>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    container->getPositionSequence().front().serialize(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
