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

#include <ibeo/common/sdk/datablocks/eventtag/EventTag7000Exporter7000.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::EventTag7000;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
void writeBE<C::TagClass>(std::ostream& os, const C::TagClass& tc)
{
    writeBE(os, uint16_t(tc));
}

//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_EventTag7000>::getSerializedSize(const DataContainerBase& c) const
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

    return serializedBaseSize + std::streamsize(container->m_tagString.size())
           + PositionWgs84::getSerializedSize_static();
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_EventTag7000>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    writeBE(os, container->m_tagStart);
    writeBE(os, container->m_tagEnd);
    writeBE(os, container->m_flags);
    writeBE(os, container->m_tagClass);
    writeBE(os, container->m_tagId);

    {
        const uint8_t strLength = uint8_t(container->m_tagString.size());
        writeBE(os, strLength);
        os.write(&container->m_tagString[0], strLength); // assuming contiguous storage for std::string.
    }

    if (!container->m_wgs84.serialize(os))
    {
        return false;
    }

    writeBE(os, container->m_roiWidth);
    writeBE(os, container->m_roiLength);

    os.write(container->m_reserved.data(), C::nbOfReserved);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
