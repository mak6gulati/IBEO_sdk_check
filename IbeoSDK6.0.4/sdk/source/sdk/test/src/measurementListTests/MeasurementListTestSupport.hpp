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
//! \date Apr 28, 2016
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/MeasurementList.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class MeasurementListTestSupport : public TestSupport
{
public:
    MeasurementListTestSupport();
    virtual ~MeasurementListTestSupport();

    static ibeo::common::sdk::MeasurementList createMeasurementList();

    static ibeo::common::sdk::Measurement createMeasurement();

protected:
    static void fillRandomly(ibeo::common::sdk::MeasurementList& ml);

    static void fillRandomly(ibeo::common::sdk::Measurement& m,
                             const uint16_t keyRangeStart = 0x0000,
                             const uint16_t keyRangeend   = 0xFFFF);

    template<Measurement::MeasurementType MT>
    static void fillDataRandomly(ibeo::common::sdk::Measurement& m);

    static void fill64kString(std::string& s);

protected:
    static const int32_t nbOfRepeats = 100;
}; // MeasurementListTestSupport

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::Void>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::Float>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::Double>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::INT8>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::UINT8>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::INT16>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::UINT16>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::INT32>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::UINT32>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::INT64>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::UINT64>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::Bool>(Measurement& m);
template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::StdString>(Measurement& m);

//==============================================================================

template<>
Measurement::MeasurementType TestSupport::getRandValue();

//==============================================================================

} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
