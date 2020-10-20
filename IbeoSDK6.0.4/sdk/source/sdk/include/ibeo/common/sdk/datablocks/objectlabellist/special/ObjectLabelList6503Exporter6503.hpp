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
//!\date Jan 15, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelList6503.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::ObjectLabelList6503, DataTypeId::DataType_ObjectLabel6503>
  : public TypedExporter<ibeo::common::sdk::ObjectLabelList6503, DataTypeId::DataType_ObjectLabel6503>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase&) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& importContainer) const override;
}; // ObjectLabelList6503Exporter6503

//==============================================================================

using ObjectLabelList6503Exporter6503
    = Exporter<ibeo::common::sdk::ObjectLabelList6503, DataTypeId::DataType_ObjectLabel6503>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
