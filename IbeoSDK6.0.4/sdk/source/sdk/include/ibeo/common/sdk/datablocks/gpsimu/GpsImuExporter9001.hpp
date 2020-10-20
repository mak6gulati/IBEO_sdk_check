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
//!\date Jan 31, 2019
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/GpsImu.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<GpsImu, DataTypeId::DataType_GpsImu9001> : public TypedExporter<GpsImu, DataTypeId::DataType_GpsImu9001>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // GpsImuExporter9001

//==============================================================================

using GpsImuExporter9001 = Exporter<GpsImu, DataTypeId::DataType_GpsImu9001>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
