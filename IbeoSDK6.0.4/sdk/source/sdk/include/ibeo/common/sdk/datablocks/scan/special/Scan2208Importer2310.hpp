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
//! \date Jan 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2310Importer2310.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2208.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<Scan2208, DataTypeId::DataType_Scan2310>
  : public RegisteredImporter<Scan2208, DataTypeId::DataType_Scan2310>
{
public:
    static bool to2208Scan(Scan2208& scan2208Container, const Scan2310& sfrdContainer);

protected:
    static uint16_t to2208Flags(const uint16_t rawFlags);
    static void setFlag(uint16_t& flagsToBeModified, const uint16_t flagToSet);

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
    Scan2310Importer2310 m_sfrdImporter;
}; // Scan2208Importer2310

//==============================================================================

using Scan2208Importer2310 = Importer<ibeo::common::sdk::Scan2208, DataTypeId::DataType_Scan2310>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
