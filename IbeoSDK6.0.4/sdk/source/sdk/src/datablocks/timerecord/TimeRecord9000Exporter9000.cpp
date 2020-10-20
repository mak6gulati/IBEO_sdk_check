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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/timerecord/TimeRecord9000Exporter9000.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::TimeRecord9000;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_TimeRecord9000>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c); // ignore the return value
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    std::streamsize result = serializedBaseSize;
    result += container->m_externalClockType.getSerializedSize();
    result += container->m_internalClockType.getSerializedSize();
    result += std::streamsize(8 * container->m_externalClockTimes.size());
    result += std::streamsize(8 * container->m_internalClockTimes.size());
    result += std::streamsize(sizeof(uint8_t) * container->m_fixModes.size());
    return result;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_TimeRecord9000>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    container->m_externalClockType.serialize(os);
    container->m_internalClockType.serialize(os);
    const uint32_t nbOfEntries = static_cast<uint32_t>(container->m_externalClockTimes.size());
    writeBE(os, nbOfEntries);

    for (auto& ect : container->m_externalClockTimes)
    {
        writeBE(os, ect);
    }

    for (auto& ict : container->m_internalClockTimes)
    {
        writeBE(os, ict);
    }

    for (auto& fm : container->m_fixModes)
    {
        writeBE(os, static_cast<uint8_t>(fm));
    }

    for (auto& r : container->m_reserved)
    {
        writeBE(os, r);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
