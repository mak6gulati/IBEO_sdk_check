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

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/ibeoevent/IbeoEvent7001.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<IbeoEvent7001, DataTypeId::DataType_IbeoEvent7001>
  : public TypedExporter<IbeoEvent7001, DataTypeId::DataType_IbeoEvent7001>
{
public:
    static constexpr std::streamsize serializedBaseSize{10};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // IbeoEvent7001Exporter7001

//==============================================================================

using IbeoEvent7001Exporter7001 = Exporter<IbeoEvent7001, DataTypeId::DataType_IbeoEvent7001>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
