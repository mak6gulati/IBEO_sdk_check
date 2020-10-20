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
//!\date May 4, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<ObjectList, DataTypeId::DataType_ObjectList2221>
  : public RegisteredImporter<ObjectList, DataTypeId::DataType_ObjectList2221>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    virtual bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;

private:
    // Deserialize the general object in context of a data container type 0x2221.
    std::streamsize getSerializedSize(const Object& object) const;
    bool deserialize(std::istream& is, Object& object, const NTPTime& containerTimestamp) const;
}; // ObjectListImporter2221

//==============================================================================

using ObjectListImporter2221 = Importer<ObjectList, DataTypeId::DataType_ObjectList2221>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
