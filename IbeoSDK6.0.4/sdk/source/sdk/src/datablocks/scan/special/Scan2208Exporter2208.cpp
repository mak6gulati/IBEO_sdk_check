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
//!\date Jan 14, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/scan/special/Scan2208Exporter2208.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::Scan2208;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_Scan2208>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize sz = 52;
    for (const auto& subscan : container->getSubScans())
    {
        sz += static_cast<std::streamsize>(subscan.getSerializedSize());
    }
    return sz;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_Scan2208>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    writeBE(os, container->m_scanNumber);
    writeBE(os, uint16_t(container->m_scannerType));
    writeBE(os, container->m_scannerStatus);
    writeBE(os, container->m_angleTicksPerRotation);
    writeBE(os, container->m_processingFlags);
    writeBE(os, container->m_mountingPosition);

    for (auto threshold : container->m_thresholds)
        writeBE(os, threshold);

    for (auto reserved : container->m_reserved)
        writeBE(os, reserved);

    writeBE(os, container->m_deviceId);
    const uint8_t nbOfSubScans = uint8_t(container->m_subScans.size());
    writeBE(os, nbOfSubScans);

    for (const auto& subscan : container->getSubScans())
        if (!subscan.serialize(os))
            return false;

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
