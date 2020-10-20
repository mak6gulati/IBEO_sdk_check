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
//!\date Jan 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2205.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<Scan2205, DataTypeId::DataType_Scan2205> : public TypedExporter<Scan2205, DataTypeId::DataType_Scan2205>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // Scan2205Exporter2205

//==============================================================================

using Scan2205Exporter2205 = Exporter<Scan2205, DataTypeId::DataType_Scan2205>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
