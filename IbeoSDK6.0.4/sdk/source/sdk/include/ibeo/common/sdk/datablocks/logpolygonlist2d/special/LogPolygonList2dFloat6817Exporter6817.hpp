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
//!\date Mar 26, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/logpolygonlist2d/special/LogPolygonList2dFloat6817.hpp>
#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<LogPolygonList2dFloat6817, DataTypeId::DataType_LogPolygonList2dFloat6817>
  : public TypedExporter<LogPolygonList2dFloat6817, DataTypeId::DataType_LogPolygonList2dFloat6817>
{
public:
    static constexpr std::streamsize serializedBaseSize{2};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // LogPolygonList2dFloat6817Exporter6817

//==============================================================================

using LogPolygonList2dFloat6817Exporter6817
    = Exporter<LogPolygonList2dFloat6817, DataTypeId::DataType_LogPolygonList2dFloat6817>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
