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
//!\date Mar 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/idctrailer/IdcTrailer6120.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::IdcTrailer6120, DataTypeId::DataType_IdcTrailer6120>
  : public TypedExporter<ibeo::common::sdk::IdcTrailer6120, DataTypeId::DataType_IdcTrailer6120>
{
public:
    static constexpr std::streamsize serializedSize{0};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // IdcTrailer6120Exporter6120

//==============================================================================

using IdcTrailer6120Exporter6120 = Exporter<ibeo::common::sdk::IdcTrailer6120, DataTypeId::DataType_IdcTrailer6120>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
