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
//! \date Jan 23, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/logpolygonlist2d/LogPolygonList2d.hpp>
#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<LogPolygonList2d, DataTypeId::DataType_LogPolygonList2dFloat6817>
  : public TypedExporter<LogPolygonList2d, DataTypeId::DataType_LogPolygonList2dFloat6817>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // LogPolygonList2dExporter6817

//==============================================================================

using LogPolygonList2dExporter6817 = Exporter<LogPolygonList2d, DataTypeId::DataType_LogPolygonList2dFloat6817>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
