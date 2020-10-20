//==============================================================================
//!\file
//!
//!\brief Exports object type 0x2281 to general object container
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Apr 25, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectList.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListExporter2281_2291.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ObjectList, DataTypeId::DataType_ObjectList2281>
  : public TypedExporter<ObjectList, DataTypeId::DataType_ObjectList2281>, protected ObjectListExporter2281_2291
{
public:
    virtual ~Exporter() = default;

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override
    {
        return ObjectListExporter2281_2291::getSerializedSize(c);
    }

    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override
    {
        return ObjectListExporter2281_2291::serialize(os, c);
    }
}; // ObjectListExporter2281

//==============================================================================

using ObjectListExporter2281 = Exporter<ObjectList, DataTypeId::DataType_ObjectList2281>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
