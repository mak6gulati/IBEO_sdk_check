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
//!\date Jan 31th, 2019
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/ContentSeparator.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<ContentSeparator, DataTypeId::DataType_ContentSeparator7100>
  : public RegisteredImporter<ContentSeparator, DataTypeId::DataType_ContentSeparator7100>
{
public:
    Importer() : RegisteredImporter() {}

public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;
}; //ContentSeparatorImporter7100

//==============================================================================

using ContentSeparatorImporter7100 = Importer<ContentSeparator, DataTypeId::DataType_ContentSeparator7100>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
