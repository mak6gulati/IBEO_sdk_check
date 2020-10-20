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

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130.hpp>
#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! Importer class for the frame index of an idc file.
template<>
class Importer<FrameIndex6130, DataTypeId::DataType_FrameIndex6130>
  : public RegisteredImporter<FrameIndex6130, DataTypeId::DataType_FrameIndex6130>
{
public:
    static constexpr std::streamsize serializedBaseSize{128};

public:
    Importer() : RegisteredImporter() {}
    Importer(const Importer&) = delete;
    Importer& operator=(const Importer&) = delete;

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    //========================================
    //!\brief convert data from source to target type (deserialization)
    //!\param[in, out] is      Input data stream
    //!\param[out]     c       Output container.
    //!\param[in]      header  Ibeo DataHeader
    //!\return \c true if serialization succeed, else: false
    //!\note This method is to be called from outside for deserialization.
    //----------------------------------------
    virtual bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;
}; //FrameIndex6130Importer6130

//==============================================================================

using FrameIndex6130Importer6130 = Importer<ibeo::common::sdk::FrameIndex6130, DataTypeId::DataType_FrameIndex6130>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
