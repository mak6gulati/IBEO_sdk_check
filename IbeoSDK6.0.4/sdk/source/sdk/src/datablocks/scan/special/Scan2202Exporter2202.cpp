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

#include <ibeo/common/sdk/datablocks/scan/special/Scan2202Exporter2202.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::Scan2202;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_Scan2202>::getSerializedSize(const DataContainerBase& c) const
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

    return std::streamsize(3 * sizeof(uint16_t) + 2 * sizeof(NTPTime))
           + std::streamsize(2 * sizeof(uint16_t) + 2 * sizeof(int16_t))
           + std::streamsize(container->m_points.size()) * ScanPointIn2202::getSerializedSize_static()
           + std::streamsize(6 * sizeof(uint16_t) + sizeof(uint16_t));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_Scan2202>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    ibeo::common::sdk::writeLE(os, container->m_scanNumber);
    ibeo::common::sdk::writeLE(os, container->m_scannerStatus);
    ibeo::common::sdk::writeLE(os, container->m_syncPhaseOffset);
    ibeo::common::sdk::writeLE(os, container->m_startNTP);
    ibeo::common::sdk::writeLE(os, container->m_endNTP);
    ibeo::common::sdk::writeLE(os, container->m_angleTicksPerRotation);
    ibeo::common::sdk::writeLE(os, container->m_startAngleTicks);
    ibeo::common::sdk::writeLE(os, container->m_endAngleTicks);
    const uint16_t nbScanPts = uint16_t(container->m_points.size());
    ibeo::common::sdk::writeLE(os, nbScanPts);
    ibeo::common::sdk::writeLE(os, container->m_mountingPosYawAngleTicks);
    ibeo::common::sdk::writeLE(os, container->m_mountingPosPitchAngleTicks);
    ibeo::common::sdk::writeLE(os, container->m_mountingPosRollAngleTicks);
    ibeo::common::sdk::writeLE(os, container->m_mountingPosCmX);
    ibeo::common::sdk::writeLE(os, container->m_mountingPosCmY);
    ibeo::common::sdk::writeLE(os, container->m_mountingPosCmZ);
    ibeo::common::sdk::writeLE(os, container->m_flags);

    for (unsigned int i = 0; i < nbScanPts; ++i)
    {
        container->m_points[i].serialize(os);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
