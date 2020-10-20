//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date March 15, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9011.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<TimeRelationsList9011, DataTypeId::DataType_TimeRelationsList9011>
  : public RegisteredImporter<TimeRelationsList9011, DataTypeId::DataType_TimeRelationsList9011>
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
    //!\return \c true if serialization succeed, else: \c false
    //!\note This method is to be called from outside for deserialization.
    //----------------------------------------
    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;
}; // TimeRelationsList9011Importer9011

//==============================================================================

using TimeRelationsList9011Importer9011
    = Importer<ibeo::common::sdk::TimeRelationsList9011, DataTypeId::DataType_TimeRelationsList9011>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
