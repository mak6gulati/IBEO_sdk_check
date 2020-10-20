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

#include <ibeo/common/sdk/datablocks/ibeoevent/IbeoEvent7001Exporter7001.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::IbeoEvent7001;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_IbeoEvent7001>::getSerializedSize(const DataContainerBase& c) const
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

    return serializedBaseSize + static_cast<std::streamsize>(container->m_body.length())
           + static_cast<std::streamsize>(container->m_author.length());
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_IbeoEvent7001>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    // Type
    writeBE(os, container->m_type);

    // Body
    uint32_t len = static_cast<uint32_t>(container->m_body.length());
    writeBE(os, len);
    os.write(container->m_body.data(), len);

    // Author
    len = static_cast<uint32_t>(container->m_author.length());
    writeBE(os, len);
    os.write(container->m_author.data(), len);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
