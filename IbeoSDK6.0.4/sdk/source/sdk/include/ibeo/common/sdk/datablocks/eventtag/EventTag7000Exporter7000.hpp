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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/eventtag/EventTag7000.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<EventTag7000, DataTypeId::DataType_EventTag7000>
  : public TypedExporter<EventTag7000, DataTypeId::DataType_EventTag7000>
{
public:
    static constexpr std::streamsize serializedBaseSize{40 + EventTag7000::nbOfReserved};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // EventTag7000Exporter7000

//==============================================================================

using EventTag7000Exporter7000 = Exporter<EventTag7000, DataTypeId::DataType_EventTag7000>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
