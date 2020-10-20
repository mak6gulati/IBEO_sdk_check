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
//!\date Jan 17, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2225.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ObjectList2225, DataTypeId::DataType_ObjectList2225>
  : public TypedExporter<ObjectList2225, DataTypeId::DataType_ObjectList2225>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& container) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& importContainer) const override;
}; // ObjectList2225Exporter2225

//==============================================================================

using ObjectList2225Exporter2225 = Exporter<ObjectList2225, DataTypeId::DataType_ObjectList2225>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
