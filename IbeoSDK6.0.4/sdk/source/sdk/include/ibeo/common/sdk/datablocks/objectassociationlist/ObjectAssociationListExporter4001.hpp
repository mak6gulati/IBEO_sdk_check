//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Jan 25, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/objectassociationlist/ObjectAssociationList.hpp>
#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::ObjectAssociationList, DataTypeId::DataType_ObjectAssociationList4001>
  : public TypedExporter<ibeo::common::sdk::ObjectAssociationList, DataTypeId::DataType_ObjectAssociationList4001>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase&) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& importContainer) const override;
}; // ObjectAssociationListExporter4001

//==============================================================================

using ObjectAssociationListExporter4001
    = Exporter<ObjectAssociationList, DataTypeId::DataType_ObjectAssociationList4001>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
