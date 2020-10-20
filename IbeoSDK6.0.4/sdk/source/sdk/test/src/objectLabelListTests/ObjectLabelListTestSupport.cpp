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
//! \date Jan 25, 2019
//------------------------------------------------------------------------------

#include "ObjectLabelListTestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

ObjectLabelListTestSupport::ObjectLabelListTestSupport() : TestSupport() {}

//==============================================================================

ObjectLabelListTestSupport::~ObjectLabelListTestSupport() {}

//==============================================================================

ibeo::common::sdk::ObjectLabelList ObjectLabelListTestSupport::createObjectLabelList()
{
    ibeo::common::sdk::ObjectLabelList oll;
    fillRandomly(oll);
    return oll;
}

//==============================================================================

ibeo::common::sdk::ObjectLabel ObjectLabelListTestSupport::createObjectLabel()
{
    ibeo::common::sdk::ObjectLabel ol;
    fillRandomly(ol);
    return ol;
}

//==============================================================================

void ObjectLabelListTestSupport::fillRandomly(ibeo::common::sdk::ObjectLabelList& oll)
{
    oll.setTimeOffsetUs(getRandValue<uint32_t>());
    oll.setTimestamp(getRandValue<NTPTime>());
    oll.setScanNumber(getRandValue<uint32_t>());
    oll.setScanMidTimestamp(getRandValue<NTPTime>());

    for (uint16_t r = 0; r < ObjectLabelList::nbOfReserved; ++r)
    {
        oll.setReserved(r, getRandValue<uint16_t>());
    }

    ObjectLabelList::LabelVector::iterator olIter = oll.getLabels().begin();
    for (; olIter != oll.getLabels().end(); ++olIter)
    {
        fillRandomly(*olIter);
    }
}

//==============================================================================

void ObjectLabelListTestSupport::fillRandomly(ibeo::common::sdk::ObjectLabel& ol)
{
    ol.getObjBox() = getRandValue<Rectangle<int16_t>>();
    ol.setWeight(getRandValue<uint8_t>());
    ol.setClassification(getRandValue<uint8_t>());
    ol.setId(getRandValue<uint32_t>());
    ol.setTrackingId(getRandValue<Uoid>());
    ol.setDisplayMagnificationFactor(getRandValue<float>());
    ol.setObjectFlags(getRandValue<uint16_t>());
    ol.setIsInOnKeyframe(getRandValue<uint16_t>());

    for (uint16_t r = 0; r < ObjectLabel::nbOfReserved; ++r)
    {
        ol.setReserved(r, getRandValue<uint16_t>());
    }

    fillRandomly(ol.getUserData());
}

//==============================================================================

void ObjectLabelListTestSupport::fillRandomly(ibeo::common::sdk::MeasurementList& ml)
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
