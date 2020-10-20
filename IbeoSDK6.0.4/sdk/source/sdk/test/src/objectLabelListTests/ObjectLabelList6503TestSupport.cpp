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
//!\date Apr 28, 2016
//------------------------------------------------------------------------------

#include "ObjectLabelList6503TestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

ObjectLabelList6503TestSupport::ObjectLabelList6503TestSupport() : TestSupport() {}

//==============================================================================

ObjectLabelList6503TestSupport::~ObjectLabelList6503TestSupport() {}

//==============================================================================

ibeo::common::sdk::ObjectLabelList6503 ObjectLabelList6503TestSupport::createObjectLabelList6503()
{
    ibeo::common::sdk::ObjectLabelList6503 oll;
    fillRandomly(oll);
    return oll;
}

//==============================================================================

ibeo::common::sdk::ObjectLabelIn6503 ObjectLabelList6503TestSupport::createObjectLabel6503()
{
    ibeo::common::sdk::ObjectLabelIn6503 ol;
    fillRandomly(ol);
    return ol;
}

//==============================================================================

void ObjectLabelList6503TestSupport::fillRandomly(ibeo::common::sdk::ObjectLabelList6503& oll)
{
    oll.setTimeOffsetUs(getRandValue<uint32_t>());
    oll.setTimestamp(getRandValue<NTPTime>());
    oll.setScanNumber(getRandValue<uint32_t>());
    oll.setScanMidTimestamp(getRandValue<NTPTime>());

    for (uint16_t r = 0; r < ObjectLabelList6503::nbOfReserved; ++r)
    {
        oll.setReserved(r, getRandValue<uint16_t>());
    }

    ObjectLabelList6503::LabelVector::iterator olIter = oll.getLabels().begin();
    for (; olIter != oll.getLabels().end(); ++olIter)
    {
        fillRandomly(*olIter);
    }
}

//==============================================================================

void ObjectLabelList6503TestSupport::fillRandomly(ibeo::common::sdk::ObjectLabelIn6503& ol)
{
    ol.getObjBox() = getRandValue<Rectangle<int16_t>>();
    ol.setWeight(getRandValue<uint8_t>());
    ol.setClassification(getRandValue<uint8_t>());
    ol.setId(getRandValue<uint32_t>());
    ol.setTrackingId(getRandValue<Uoid>());
    ol.setDisplayMagnificationFactor(getRandValue<float>());
    ol.setObjectFlags(getRandValue<uint16_t>());
    ol.setIsInOnKeyframe(getRandValue<uint16_t>());

    for (uint16_t r = 0; r < ObjectLabelIn6503::nbOfReserved; ++r)
    {
        ol.setReserved(r, getRandValue<uint16_t>());
    }

    fillRandomly(ol.getUserData());
}

//==============================================================================

void ObjectLabelList6503TestSupport::fillRandomly(ibeo::common::sdk::MeasurementList& ml)
{
    const bool hasMeasurementList = getRandValue<bool>();
    if (hasMeasurementList)
    {
        Measurement m;
        m.setKey(MeasurementKey::LabelUserData); // currently only key

        const uint16_t strLen = getRandValue<uint16_t>();
        std::string s;
        s.resize(strLen);
        std::string::iterator sIter = s.begin();
        for (; sIter != s.end(); ++sIter)
        {
            *sIter = getRandValue<char>();
        }
        m.setData(s);
        ml.addMeasurement(m);
    }
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
