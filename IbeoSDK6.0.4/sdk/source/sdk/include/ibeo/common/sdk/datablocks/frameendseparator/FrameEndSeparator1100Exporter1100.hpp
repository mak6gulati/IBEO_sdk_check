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
//!\date Jan 11, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/frameendseparator/FrameEndSeparator1100.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<FrameEndSeparator1100, DataTypeId::DataType_FrameEndSeparator1100>
  : public TypedExporter<FrameEndSeparator1100, DataTypeId::DataType_FrameEndSeparator1100>
{
public:
    static constexpr std::streamsize serializedSize{32};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // FrameEndSeparator1100Exporter1100

//==============================================================================

using FrameEndSeparator1100Exporter1100 = Exporter<FrameEndSeparator1100, DataTypeId::DataType_FrameEndSeparator1100>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
