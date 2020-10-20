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
//!\date Mar 20, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/objectassociationlist/special/ObjectAssociationList4001.hpp>

#include <ibeo/common/logging/logging.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<ObjectAssociationList4001, DataTypeId::DataType_ObjectAssociationList4001>
  : public RegisteredImporter<ObjectAssociationList4001, DataTypeId::DataType_ObjectAssociationList4001>
{
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

private:
    static constexpr const char* loggerId = "ibeo::common::sdk::ObjectAssociationList4001Importer4001";
    static ibeo::common::logging::LoggerSPtr logger;
}; //ObjectAssociationList4001Importer4001

//==============================================================================

using ObjectAssociationList4001Importer4001
    = Importer<ObjectAssociationList4001, DataTypeId::DataType_ObjectAssociationList4001>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
