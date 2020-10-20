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
//!\date 14.November 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84Sequence.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<PositionWgs84Sequence, DataTypeId::DataType_PositionWgs84_2604>
  : public TypedExporter<PositionWgs84Sequence, DataTypeId::DataType_PositionWgs84_2604>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;

}; //PositionWgs84SequenceExporter2604

//==============================================================================

using PositionWgs84SequenceExporter2604 = Exporter<PositionWgs84Sequence, DataTypeId::DataType_PositionWgs84_2604>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
