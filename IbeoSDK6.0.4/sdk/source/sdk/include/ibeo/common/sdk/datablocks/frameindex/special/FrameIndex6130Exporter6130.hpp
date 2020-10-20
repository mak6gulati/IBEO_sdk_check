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

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::FrameIndex6130, DataTypeId::DataType_FrameIndex6130>
  : public TypedExporter<ibeo::common::sdk::FrameIndex6130, DataTypeId::DataType_FrameIndex6130>
{
public:
    static constexpr std::streamsize serializedBaseSize{128};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // FrameIndex6130Exporter6130

//==============================================================================

using FrameIndex6130Exporter6130 = Exporter<ibeo::common::sdk::FrameIndex6130, DataTypeId::DataType_FrameIndex6130>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
