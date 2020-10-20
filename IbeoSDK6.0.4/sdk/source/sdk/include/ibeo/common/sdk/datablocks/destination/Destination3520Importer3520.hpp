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
//!\date Sept 05, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include "Destination3520.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<Destination3520, DataTypeId::DataType_Destination3520>
  : public RegisteredImporter<Destination3520, DataTypeId::DataType_Destination3520>
{
public:
    Importer() : RegisteredImporter() {}

    Importer(const Importer&) = delete;

    Importer& operator=(const Importer&) = delete;

public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;
};

//==============================================================================

using Destination3520Importer3520 = Importer<ibeo::common::sdk::Destination3520, DataTypeId::DataType_Destination3520>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
