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
#include <ibeo/common/sdk/datablocks/scan/Scan.hpp>
#include <ibeo/common/sdk/TransformationMatrix3d.hpp>
#include <ibeo/common/sdk/Vector3.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<Scan, DataTypeId::DataType_Scan2209> : public RegisteredImporter<Scan, DataTypeId::DataType_Scan2209>
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
    static constexpr const char* loggerId{"ibeo::common::sdk::ScanImporter2209"};
    static ibeo::common::logging::LoggerSPtr logger;

    std::streamsize getSerializedSize(const std::size_t nbOfScannerInfos, const std::size_t nbOfScanPoints) const;
}; //ScanImporter2209

//==============================================================================

using ScanImporter2209 = Importer<ibeo::common::sdk::Scan, DataTypeId::DataType_Scan2209>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
