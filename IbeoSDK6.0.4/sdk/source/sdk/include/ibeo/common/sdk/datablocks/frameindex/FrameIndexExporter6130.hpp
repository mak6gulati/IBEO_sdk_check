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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/frameindex/FrameIndex.hpp>
#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::FrameIndex, DataTypeId::DataType_FrameIndex6130>
  : public TypedExporter<ibeo::common::sdk::FrameIndex, DataTypeId::DataType_FrameIndex6130>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // FrameIndexExporter6130

//==============================================================================

using FrameIndexExporter6130 = Exporter<ibeo::common::sdk::FrameIndex, DataTypeId::DataType_FrameIndex6130>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
