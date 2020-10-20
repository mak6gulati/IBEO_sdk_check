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
//!\date Mar 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/stateofoperation/StateOfOperation9110.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<StateOfOperation9110, DataTypeId::DataType_StateOfOperation9110>
  : public TypedExporter<StateOfOperation9110, DataTypeId::DataType_StateOfOperation9110>
{
public:
    static constexpr std::streamsize serializedBaseSize{3 + sizeof(uint32_t) * StateOfOperation9110::nbOfReserved};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // StateOfOperation9110Exporter9110

//==============================================================================

using StateOfOperation9110Exporter9110 = Exporter<StateOfOperation9110, DataTypeId::DataType_StateOfOperation9110>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
