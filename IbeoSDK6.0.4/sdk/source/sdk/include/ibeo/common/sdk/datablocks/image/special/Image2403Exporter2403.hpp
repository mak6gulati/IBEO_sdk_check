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
//!\date Mar 9, 2018
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/image/special/Image2403.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::Image2403, DataTypeId::DataType_Image2403>
  : public TypedExporter<ibeo::common::sdk::Image2403, DataTypeId::DataType_Image2403>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase&) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& importContainer) const override;
}; // Image2403Exporter2403

//==============================================================================

using Image2403Exporter2403 = Exporter<ibeo::common::sdk::Image2403, DataTypeId::DataType_Image2403>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
