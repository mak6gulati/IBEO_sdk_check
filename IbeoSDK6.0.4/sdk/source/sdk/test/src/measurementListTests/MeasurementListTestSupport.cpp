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

//==============================================================================

#include "MeasurementListTestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

MeasurementListTestSupport::MeasurementListTestSupport() : TestSupport() {}

//==============================================================================

MeasurementListTestSupport::~MeasurementListTestSupport() {}

//==============================================================================

ibeo::common::sdk::MeasurementList MeasurementListTestSupport::createMeasurementList()
{
    ibeo::common::sdk::MeasurementList ml;
    fillRandomly(ml);
    return ml;
}

//==============================================================================

ibeo::common::sdk::Measurement MeasurementListTestSupport::createMeasurement()
{
    ibeo::common::sdk::Measurement m;
    fillRandomly(m);
    return m;
}

//==============================================================================

void MeasurementListTestSupport::fillRandomly(ibeo::common::sdk::MeasurementList& ml)
{
    const uint8_t nbOfMeasurements = getRandValue<uint8_t>();
    for (uint16_t mIdx = 0; mIdx < nbOfMeasurements; ++mIdx)
    {
        Measurement m;
        fillRandomly(m, 0x0000, 0xFFFF);
        ml.addMeasurement(m);
    }
}
//==============================================================================

void MeasurementListTestSupport::fillRandomly(ibeo::common::sdk::Measurement& m,
                                              const uint16_t keyRangeStart,
                                              const uint16_t keyRangeEnd)
{
    m.setKey(MeasurementKey(getRandValue<uint16_t>(keyRangeStart, keyRangeEnd)));

    switch (getRandValue<Measurement::MeasurementType>())
    {
    case Measurement::MeasurementType::Void:
        fillDataRandomly<Measurement::MeasurementType::Void>(m);
        return;
    case Measurement::MeasurementType::Float:
        fillDataRandomly<Measurement::MeasurementType::Float>(m);
        return;
    case Measurement::MeasurementType::Double:
        fillDataRandomly<Measurement::MeasurementType::Double>(m);
        return;
    case Measurement::MeasurementType::INT8:
        fillDataRandomly<Measurement::MeasurementType::INT8>(m);
        return;
    case Measurement::MeasurementType::UINT8:
        fillDataRandomly<Measurement::MeasurementType::UINT8>(m);
        return;
    case Measurement::MeasurementType::INT16:
        fillDataRandomly<Measurement::MeasurementType::INT16>(m);
        return;
    case Measurement::MeasurementType::UINT16:
        fillDataRandomly<Measurement::MeasurementType::UINT16>(m);
        return;
    case Measurement::MeasurementType::INT32:
        fillDataRandomly<Measurement::MeasurementType::INT32>(m);
        return;
    case Measurement::MeasurementType::UINT32:
        fillDataRandomly<Measurement::MeasurementType::UINT32>(m);
        return;
    case Measurement::MeasurementType::INT64:
        fillDataRandomly<Measurement::MeasurementType::INT64>(m);
        return;
    case Measurement::MeasurementType::UINT64:
        fillDataRandomly<Measurement::MeasurementType::UINT64>(m);
        return;
    case Measurement::MeasurementType::Bool:
        fillDataRandomly<Measurement::MeasurementType::Bool>(m);
        return;
    case Measurement::MeasurementType::StdString:
        fillDataRandomly<Measurement::MeasurementType::StdString>(m);
        return;
    }
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::Void>(Measurement& m)
{
    m.resetValue();
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::Float>(Measurement& m)
{
    const float v = getRandValue<float>();
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::Double>(Measurement& m)
{
    const double v = getRandValue<double>();
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::INT8>(Measurement& m)
{
    const int8_t v = int8_t(getRandValue<uint8_t>());
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::UINT8>(Measurement& m)
{
    const uint8_t v = getRandValue<uint8_t>();
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::INT16>(Measurement& m)
{
    const int16_t v = int16_t(getRandValue<uint16_t>());
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::UINT16>(Measurement& m)
{
    const uint16_t v = getRandValue<uint16_t>();
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::INT32>(Measurement& m)
{
    const int32_t v = int32_t(getRandValue<uint32_t>());
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::UINT32>(Measurement& m)
{
    const uint32_t v = getRandValue<uint32_t>();
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::INT64>(Measurement& m)
{
    const int64_t v = int64_t(getRandValue<uint64_t>());
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::UINT64>(Measurement& m)
{
    const uint64_t v = getRandValue<uint64_t>();
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::Bool>(Measurement& m)
{
    const bool v = getRandValue<bool>();
    m.setData(v);
}

//==============================================================================

template<>
void MeasurementListTestSupport::fillDataRandomly<Measurement::MeasurementType::StdString>(Measurement& m)
{
    std::string s;
    fill64kString(s);
    m.setData(s);
}

//==============================================================================

void MeasurementListTestSupport::fill64kString(std::string& s)
{
    const uint16_t n = getRandValue<uint16_t>();
    s.resize(n);

    std::string::iterator it = s.begin();
    for (; it != s.end(); ++it)
    {
        *it = int8_t(65 + getRandValue<uint8_t>(25));
    }
}

//==============================================================================

template<>
Measurement::MeasurementType TestSupport::getRandValue()
{
    return Measurement::MeasurementType(
        getRandValue<uint8_t>(static_cast<uint8_t>(Measurement::MeasurementType::StdString)
                              - static_cast<uint8_t>(Measurement::MeasurementType::Void))
        + static_cast<uint8_t>(Measurement::MeasurementType::Void));
}

//==============================================================================

} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
