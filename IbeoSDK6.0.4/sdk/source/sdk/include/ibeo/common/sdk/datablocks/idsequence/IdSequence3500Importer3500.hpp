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
//!\date Sept 03, 2018
//------------------------------------------------------------------------------

#pragma once

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/idsequence/IdSequence3500.hpp>
#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<IdSequence3500, DataTypeId::DataType_IdSequence3500>
  : public RegisteredImporter<IdSequence3500, DataTypeId::DataType_IdSequence3500>
{
public:
    Importer() : RegisteredImporter() {}
    Importer(const Importer&) = delete;
    Importer& operator=(const Importer&) = delete;

public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;

}; // IdSequence3500Importer3500

//==============================================================================

using IdSequence3500Importer3500 = Importer<IdSequence3500, DataTypeId::DataType_IdSequence3500>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
