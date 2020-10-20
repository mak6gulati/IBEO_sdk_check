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
//!\date Jan 16, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::ContentSeparator7100, DataTypeId::DataType_ContentSeparator7100>
  : public TypedExporter<ibeo::common::sdk::ContentSeparator7100, DataTypeId::DataType_ContentSeparator7100>
{
public:
    static constexpr std::streamsize serializedSize{std::streamsize(sizeof(uint16_t) + sizeof(uint32_t))};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase&) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& importContainer) const override;
}; // ContentSeparator7100Exporter7100

//==============================================================================

using ContentSeparator7100Exporter7100
    = Exporter<ibeo::common::sdk::ContentSeparator7100, DataTypeId::DataType_ContentSeparator7100>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
