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

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/idsequence/IdSequence3500.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<IdSequence3500, DataTypeId::DataType_IdSequence3500>
  : public TypedExporter<IdSequence3500, DataTypeId::DataType_IdSequence3500>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; //IdSequence3500Exporter3500

//==============================================================================

using IdSequence3500Exporter3500 = Exporter<IdSequence3500, DataTypeId::DataType_IdSequence3500>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
