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
//!\date March 23, 2018
//------------------------------------------------------------------------------
//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

#include <ibeo/common/sdk/datablocks/scan/Scan.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2202.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/ScanPointIn2202.hpp>
#include <ibeo/common/sdk/datablocks/scan/ScanPoint.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<Scan, DataTypeId::DataType_Scan2202> : public RegisteredImporter<Scan, DataTypeId::DataType_Scan2202>
{
    friend bool operator==(const Scan& lhs, const Scan2202& rhs);

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
    bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;

private:
    static void toGeneralPointFlags(ScanPoint& scanPoint, const uint8_t flags);

    static float getVerticalAngle(const bool isRearMirrorSide, const uint8_t layer, const float vBeamDivergence);

    static void convertScanPoint2202(const ScanPointIn2202& scanPoint2202,
                                     ScanPoint& scanPoint,
                                     const bool isRearMirrorSide,
                                     const float ticksPerDegree);

}; // ScanImporter2202

//==============================================================================

using ScanImporter2202 = Importer<Scan, DataTypeId::DataType_Scan2202>;

bool operator==(const Scan& lhs, const Scan2202& rhs);

inline bool operator!=(const Scan& lhs, const Scan2202& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
