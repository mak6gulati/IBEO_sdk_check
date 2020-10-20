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
//! \date Jan 22, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationList.hpp>
#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<MetaInformationList, DataTypeId::DataType_MetaInformationList7110>
  : public RegisteredImporter<MetaInformationList, DataTypeId::DataType_MetaInformationList7110>
{
public:
    Importer() : RegisteredImporter() {}
    Importer(const Importer&) = delete;
    Importer& operator=(const Importer&) = delete;

public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

    //========================================
    //!\brief convert data from source to target type (deserialization)
    //!\param[in, out] is      Input data stream
    //!\param[out]     c       Output container.
    //!\param[in]      header  Ibeo DataHeader
    //!\return \c true if serialization succeed, else: false
    //!\note This method is to be called from outside for deserialization.
    //----------------------------------------
    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;
}; //MetaInformationListImporter7110

//==============================================================================

using MetaInformationListImporter7110
    = Importer<ibeo::common::sdk::MetaInformationList, DataTypeId::DataType_MetaInformationList7110>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
