//==============================================================================
//!\file
//!
//!\brief Imports object type 0x2280 or 0x2290 from general object container
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

#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImExporterCommon2280_2290.hpp>
#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class ObjectListImporter2280_2290 : public ObjectListImExporterCommon2280_2290
{
public:
    //========================================
    //!\brief convert data from source to target type (deserialization)
    //!\param[in, out] is      Input data stream
    //!\param[in]      c       Input container.
    //!\param[in]      header  Ibeo DataHeader
    //!\return \c true if serialization succeed, else: false
    //!\note This method is to be called from outside for deserialization.
    //----------------------------------------
    static bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header);

private:
    // Deserialize the general object in context of a data container type 0x2280/0x2290.
    static bool deserialize(std::istream& is, Object& object);
}; // ObjectListImporter2280_2290

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
