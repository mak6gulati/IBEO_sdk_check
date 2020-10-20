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
//!\date Jan 22, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301.hpp>
#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<DeviceStatus6301, DataTypeId::DataType_DeviceStatus6301>
  : public RegisteredImporter<DeviceStatus6301, DataTypeId::DataType_DeviceStatus6301>
{
public:
    constexpr static std::streamsize serializedSize{168};

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

public:
    static bool deserialize(std::istream& is, SerialNumberIn6301& sn);
    static bool deserialize(std::istream& is, Version448In6301& version);
}; // DeviceStatus6301Importer6301

//==============================================================================

using DeviceStatus6301Importer6301 = Importer<DeviceStatus6301, DataTypeId::DataType_DeviceStatus6301>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
