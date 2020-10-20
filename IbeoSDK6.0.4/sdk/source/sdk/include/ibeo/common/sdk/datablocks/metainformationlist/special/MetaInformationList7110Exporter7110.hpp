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
//! \date Feb 02, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationList7110.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<MetaInformationList7110, DataTypeId::DataType_MetaInformationList7110>
  : public TypedExporter<MetaInformationList7110, DataTypeId::DataType_MetaInformationList7110>
{
public:
    virtual ~Exporter() = default;

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // MetaInformationList7110Exporter7110

//==============================================================================

using MetaInformationList7110Exporter7110
    = Exporter<ibeo::common::sdk::MetaInformationList7110, DataTypeId::DataType_MetaInformationList7110>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
