//==============================================================================
//!\file
//!
//!\brief Imports object type 0x2281 from general object container
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Apr 9, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectList.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImporter2281_2291.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<ObjectList, DataTypeId::DataType_ObjectList2281>
  : public RegisteredImporter<ObjectList, DataTypeId::DataType_ObjectList2281>, protected ObjectListImporter2281_2291
{
public:
    virtual ~Importer() = default;

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override
    {
        return ObjectListImporter2281_2291::getSerializedSize(c);
    }

    virtual bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override
    {
        return ObjectListImporter2281_2291::deserialize(is, c, header);
    }
}; // ObjectListImporter2281

//==============================================================================

using ObjectListImporter2281 = Importer<ObjectList, DataTypeId::DataType_ObjectList2281>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
