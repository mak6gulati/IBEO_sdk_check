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
//!\date Mar 9, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130Exporter6130.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::FrameIndex6130;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_FrameIndex6130>::getSerializedSize(const DataContainerBase& c) const
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

    const std::streamsize nbOfFrameIndices = static_cast<std::streamsize>(container->m_frameIndices.size());
    const std::streamsize sizeOfIdxEntry
        = static_cast<std::streamsize>(FrameIndexEntryIn6130::getSerializedSize_static());

    return static_cast<std::streamsize>(serializedBaseSize) + (nbOfFrameIndices * sizeOfIdxEntry);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_FrameIndex6130>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    ibeo::common::sdk::writeBE(os, C::majorVersion);
    ibeo::common::sdk::writeBE(os, C::minorVersion);
    os.write(C::nameString, strlen(C::nameString));
    ibeo::common::sdk::writeBE(os, uint64_t(container->m_frameIndices.size()));
    if (!container->m_frameIndices.empty())
    {
        ibeo::common::sdk::writeBE(os, container->m_frameIndices.back().getTimeOffsetMs());
    }
    else
    {
        ibeo::common::sdk::writeBE(os, NTPTime());
    }
    container->m_framingPolicy.serialize(os);

    // there is room for at most 30 triggers
    int32_t numPadding    = int32_t(128 - 35 - container->m_framingPolicy.getSerializedSize());
    const uint8_t padding = 0;
    while (numPadding-- > 0)
    {
        ibeo::common::sdk::writeBE(os, padding);
    }

    for (const FrameIndexEntryIn6130& frameIndex : container->m_frameIndices)
    {
        frameIndex.serialize(os);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
