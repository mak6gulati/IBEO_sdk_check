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
//!\date Sept 05, 2018
//------------------------------------------------------------------------------
#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include "MissionResponse3540.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<MissionResponse3540, DataTypeId::DataType_MissionResponse3540>
  : public RegisteredImporter<MissionResponse3540, DataTypeId::DataType_MissionResponse3540>
{
public:
    Importer() : RegisteredImporter() {}
    Importer(const Importer&) = delete;
    Importer& operator=(const Importer&) = delete;

public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;

}; //MissionResponse3540Importer3540

//==============================================================================

using MissionResponse3540Importer3540
    = Importer<ibeo::common::sdk::MissionResponse3540, DataTypeId::DataType_MissionResponse3540>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
