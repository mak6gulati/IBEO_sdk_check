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
//!\date Mar 26, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/logpolygonlist2d/special/LogPolygonList2dFloat6817Exporter6817.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::LogPolygonList2dFloat6817;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_LogPolygonList2dFloat6817>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize sz{serializedBaseSize};
    for (const auto& lp : container->m_logList)
    {
        sz += lp.getSerializedSize();
    }
    return sz;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_LogPolygonList2dFloat6817>::serialize(std::ostream& os,
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

    const uint16_t nbOfPolygons = static_cast<uint16_t>(container->m_logList.size());
    ibeo::common::sdk::writeBE(os, nbOfPolygons);

    for (auto& lp : container->m_logList)
    {
        if (!lp.serialize(os))
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
