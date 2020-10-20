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
//! \date Jun 11, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/scan/Scan.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<Scan, DataTypeId::DataType_Scan2209> : public TypedExporter<Scan, DataTypeId::DataType_Scan2209>
{
public:
    virtual ~Exporter() = default;

public:
    //========================================
    //!\brief get size in bytes of serialized data
    //!\param[in]      c       Data container.
    //!\return \c true if serialization succeed, else: false
    //!\note This method is to be called from outside for serialization.
    //----------------------------------------
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

    //========================================
    //!\brief convert to byte stream (serialization)
    //!\param[in, out] os      Output data stream
    //!\param[in]      c       Data container.
    //!\return \c true if serialization succeeded, else: false
    //!\note This method is to be called from outside for serialization.
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // ScanExporter2209

//==============================================================================

using ScanExporter2209 = Exporter<Scan, DataTypeId::DataType_Scan2209>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
