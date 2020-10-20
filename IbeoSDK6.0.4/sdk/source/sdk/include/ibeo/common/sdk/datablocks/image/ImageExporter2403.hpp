//==============================================================================
//!\file
//!
//! Exporter for Image GDC to Image2403
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!
//! Created by
//!\date June 18, 2018
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/image/Image.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<Image, DataTypeId::DataType_Image2403> : public TypedExporter<Image, DataTypeId::DataType_Image2403>
{
public:
    //========================================
    //!\brief get size in bytes of serialized data
    //!\param[in]      c       Data container.
    //!\return \c true if serialization succeed, else: false
    //!\note This method is to be called from outside for serialization.
    //----------------------------------------
    virtual std::streamsize getSerializedSize(const DataContainerBase&) const override;

    //!\brief convert to byte stream (serialization)
    //!\param[in, out] os      Output data stream
    //!\param[in]      c       Data container.
    //!\return \c true if serialization succeeded, else: false
    //!\note This method is to be called from outside for serialization.
    virtual bool serialize(std::ostream& os, const DataContainerBase& importContainer) const override;
}; // ImageExporter2403

//==============================================================================

using ImageExporter2403 = Exporter<Image, DataTypeId::DataType_Image2403>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
