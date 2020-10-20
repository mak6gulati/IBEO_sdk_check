///==============================================================================
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
//!\date Jan 13, 2018
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/measurementlist/MeasurementList2821Exporter2821.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::MeasurementList2821;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_MeasurementList2821>::getSerializedSize(const DataContainerBase& c) const
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

    return std::streamsize(4 + sizeof(NTPTime)) + std::streamsize(container->m_listName.size() + 1)
           + std::streamsize(container->m_groupName.size() + 1) + container->m_mList.getSerializedSize();
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_MeasurementList2821>::serialize(std::ostream& os,
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

    ibeo::common::sdk::writeBE(os, container->m_microseconds); // 4
    ibeo::common::sdk::writeBE(os, container->m_timestamp); // 8

    // two strings with 0 byte termination.
    os << container->m_listName;
    ibeo::common::sdk::write(os, std::string::value_type(0));
    os << container->m_groupName;
    ibeo::common::sdk::write(os, std::string::value_type(0));
    container->m_mList.serialize(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
