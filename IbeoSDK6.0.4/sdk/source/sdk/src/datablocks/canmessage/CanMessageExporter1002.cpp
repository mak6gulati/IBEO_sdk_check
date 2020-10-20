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
//!\date 12.October 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/canmessage/CanMessageExporter1002.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================

namespace {
using C = ibeo::common::sdk::CanMessage;
} // namespace

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
inline void writeBE<C::MsgType>(std::ostream& os, const C::MsgType& value)
{
    const uint8_t tmp = static_cast<uint8_t>(value);
    writeBE(os, tmp);
}

//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_CanMessage1002>::getSerializedSize(const DataContainerBase& c) const
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

    return 1 + container->m_length + 1 + (container->hasExtendedCanId() ? 4 : 2)
           + (container->hasValidTimestamp() ? 12 : 0) + 1;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_CanMessage1002>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    const int64_t startPos = streamposToInt64(os.tellp());

    const unsigned int extTsBitMask = C::extTsBitMask;
    const unsigned int stdTsBitMask = C::stdTsBitMask;

    const uint8_t lenVer = uint8_t(container->m_length << 4) | container->m_version;
    writeBE(os, lenVer);
    for (uint_fast8_t i = 0; i < container->m_length; ++i)
    {
        writeBE(os, container->m_data[i]);
    }
    writeBE(os, container->m_msgType);

    const bool hasValidTs = container->hasValidTimestamp();

    if (container->hasExtendedCanId())
    {
        const uint32_t canId = container->m_canId | (hasValidTs ? extTsBitMask : 0);
        writeBE(os, canId);
    }
    else
    {
        const uint16_t canId = uint16_t(container->m_canId | (hasValidTs ? stdTsBitMask : 0));
        writeBE(os, canId);
    }

    if (hasValidTs)
    {
        writeBE(os, container->m_usSinceStartup);
        writeBE(os, container->m_timestamp);
    }

    writeBE(os, container->m_deviceId);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
