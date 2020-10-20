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
//!\date Feb 4, 2019
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/ContentSeparator.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ContentSeparator, DataTypeId::DataType_ContentSeparator7100>
  : public TypedExporter<ContentSeparator, DataTypeId::DataType_ContentSeparator7100>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // ContentSeparatorExporter7100

//==============================================================================

using ContentSeparatorExporter7100 = Exporter<ContentSeparator, DataTypeId::DataType_ContentSeparator7100>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
