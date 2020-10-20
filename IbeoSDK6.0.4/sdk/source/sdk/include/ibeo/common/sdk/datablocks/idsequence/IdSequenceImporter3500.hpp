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
//!\date 07.November 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/idsequence/IdSequence.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<IdSequence, DataTypeId::DataType_IdSequence3500>
  : public RegisteredImporter<IdSequence, DataTypeId::DataType_IdSequence3500>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;

}; // IdSequenceImporter3500

//==============================================================================

using IdSequenceImporter3500 = Importer<IdSequence, DataTypeId::DataType_IdSequence3500>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
