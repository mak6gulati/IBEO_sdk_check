//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 15, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelList6503Exporter6503.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::ObjectLabelList6503;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_ObjectLabel6503>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize sz = std::streamsize(2 * sizeof(uint32_t)) + std::streamsize(2 * sizeof(uint64_t))
                         + std::streamsize(C::nbOfReserved * sizeof(uint16_t)) + std::streamsize(1 * sizeof(uint16_t));

    for (auto& label : container->getLabels())
    {
        sz += label.getSerializedSize();
    }
    return sz;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_ObjectLabel6503>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    ibeo::common::sdk::writeBE(os, container->m_timeOffsetUs);
    ibeo::common::sdk::writeBE(os, container->m_timestamp);
    ibeo::common::sdk::writeBE(os, container->m_scanNumber);
    ibeo::common::sdk::writeBE(os, container->m_scanMidTimestamp);

    for (auto reserved : container->m_reserved)
    {
        ibeo::common::sdk::writeBE(os, reserved);
    }

    ibeo::common::sdk::writeBE(os, uint16_t(container->m_labels.size()));

    for (const auto& label : container->getLabels())
    {
        if (!label.serialize(os))
        {
            break;
        }
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
