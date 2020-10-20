//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Jun 11, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/scan/ScanExporter2209.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/ScannerInfoIn2209.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/ScanPointIn2209.hpp>

#include <ibeo/common/sdk/Math.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::Scan;
} // namespace
//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_Scan2209>::getSerializedSize(const DataContainerBase& c) const
{
    const Scan* container{nullptr};
    try
    {
        container = &dynamic_cast<const Scan&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return std::streamsize(sizeof(NTPTime)) + std::streamsize(3 * sizeof(uint32_t))
           + std::streamsize(1 * sizeof(uint16_t)) + std::streamsize(sizeof(uint8_t))
           + 3 // = unit8 (reserved0) + uint16 (reserved1)
           + std::streamsize(uint8_t(container->m_scannerInfos.size())) * ScannerInfoIn2209::getSerializedSize_static()
           + std::streamsize(uint32_t(container->m_scanPoints.size()))
                 * ScanPointIn2209::getSerializedSize_static(); //todo ????
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_Scan2209>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    ibeo::common::sdk::writeBE(os, container->m_scanStartTime);
    ibeo::common::sdk::writeBE(os, container->m_endTimeOffset);

    ibeo::common::sdk::writeBE(os, container->m_flags);
    ibeo::common::sdk::writeBE(os, container->m_scanNumber);

    const uint32_t nbScanPts = uint32_t(container->m_scanPoints.size());
    ibeo::common::sdk::writeBE(os, nbScanPts);

    const uint8_t nbScanInfos = uint8_t(container->m_scannerInfos.size());
    ibeo::common::sdk::writeBE(os, nbScanInfos);

    ibeo::common::sdk::writeBE(os, container->m_reserved0);
    ibeo::common::sdk::writeBE(os, container->m_reserved1);

    for (uint8_t i = 0; i < nbScanInfos; ++i)
    {
        container->m_scannerInfos[i].serialize(os);
    }

    for (uint32_t i = 0; i < nbScanPts; ++i)
    {
        container->m_scanPoints[i].serialize(os);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
//==============================================================================
