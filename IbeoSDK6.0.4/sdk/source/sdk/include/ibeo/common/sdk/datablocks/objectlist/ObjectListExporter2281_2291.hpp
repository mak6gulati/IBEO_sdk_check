//==============================================================================
//!\file
//!
//!\brief Exports object type 0x2281/0x2291 to general object container.
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
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImExporterCommon2281_2291.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class ObjectListExporter2281_2291 : protected ObjectListImExporterCommon2281_2291
{
public:
    virtual ~ObjectListExporter2281_2291() = default;

public:
    //========================================
    //!\brief convert to byte stream (serialization)
    //!\param[in, out] os      Output data stream
    //!\param[in]      c       Data container.
    //!\return \c true if serialization succeeded, else: false
    //!\note This method is to be called from outside for serialization.
    //----------------------------------------
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const;

private:
    // Serialize the general object in context of a data container type 0x2281/0x2291.
    bool serialize(std::ostream& os, const Object& object) const;
}; // ObjectListExporter2281_2291

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
