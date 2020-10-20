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

#include "MeasurementListTestSupport.hpp"

#include <algorithm>
#include <vector>

#define BOOST_TEST_MODULE MeasurementListTest
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(MeasurementListTestSuite)

//==============================================================================

class Fixture : public unittests::MeasurementListTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createMeasurement, Fixture)
{
    ibeo::common::sdk::Measurement m;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createMeasurementList, Fixture)
{
    ibeo::common::sdk::MeasurementList ml;
    BOOST_CHECK(true);
}

//==============================================================================

// single measurement
BOOST_FIXTURE_TEST_CASE(isIoMeasurementIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Measurement mOrig(createMeasurement());

        std::stringstream ss;
        BOOST_CHECK(mOrig.serialize(ss));

        Measurement mCopy;
        BOOST_CHECK(mCopy.deserialize(ss));

        BOOST_CHECK(mOrig == mCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoMeasurementListIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MeasurementList mlOrig(createMeasurementList());

        std::stringstream ss;
        BOOST_CHECK(mlOrig.serialize(ss));

        MeasurementList mlCopy;
        BOOST_CHECK(mlCopy.deserialize(ss));

        BOOST_CHECK(mlOrig == mlCopy);
    } // for r
}

//==============================================================================

//operator=
BOOST_FIXTURE_TEST_CASE(isMeasurementCopy, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Measurement mOrig(createMeasurement());
        Measurement mCopy = mOrig;
        BOOST_CHECK(mOrig == mCopy);
    }
}

//==============================================================================

//operator=
BOOST_FIXTURE_TEST_CASE(isMeasurementListCopy, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MeasurementList mlOrig(createMeasurementList());
        MeasurementList mlCopy = mlOrig;
        BOOST_CHECK(mlOrig == mlCopy);
    }
}

//==============================================================================

//operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isMeasurementEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Measurement mOrig(createMeasurement());
        Measurement mCopy = mOrig;
        BOOST_CHECK(mOrig == mCopy);

        uint16_t mtype = static_cast<uint16_t>(mOrig.typeIdToType(mOrig.getType()));
        fillRandomly(mCopy, mtype, mtype);
        BOOST_CHECK(mOrig != mCopy);
    }
}

//==============================================================================

//operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isMeasurementListEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MeasurementList mlOrig, mlCopy;
        BOOST_CHECK(mlOrig == mlCopy);

        const Measurement newM(createMeasurement());
        mlOrig.addMeasurement(newM);
        BOOST_CHECK(mlOrig != mlCopy);
        mlCopy.addMeasurement(mlOrig.getMeasurements().front());
        BOOST_CHECK(mlOrig == mlCopy);

        do
        {
            fillRandomly(mlOrig);
        } while (mlOrig.getSize() < 2);
        BOOST_CHECK(mlOrig != mlCopy);

        mlCopy.getMeasurements().clear();
        const MeasurementList::MeasurementVector& measVec = mlOrig.getMeasurements();
        for (size_t i = 0; i < measVec.size() - 1; ++i)
        {
            mlCopy.addMeasurement(measVec.at(i));
            BOOST_CHECK(mlOrig != mlCopy);
        }
        mlCopy.addMeasurement(measVec.back());
        BOOST_CHECK(mlOrig == mlCopy);

        const uint16_t pos = getRandValue<uint16_t>(0, static_cast<uint16_t>(mlCopy.getMeasurements().size() - 1));
        mlCopy.getMeasurements().erase(mlCopy.getMeasurements().begin() + pos);
        BOOST_CHECK(mlOrig != mlCopy);
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isMeasurementListAssigned, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MeasurementList mlOrig, mlCopy;
        BOOST_CHECK(mlOrig == mlCopy);
        fillRandomly(mlOrig);
        BOOST_CHECK(mlOrig != mlCopy);
        mlCopy = mlOrig;
        BOOST_CHECK(mlOrig == mlCopy);
    } //for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReorderedMeasurementListIdentity, Fixture)
{
    MeasurementList mlOrig, mlCopy;
    BOOST_CHECK(mlOrig == mlCopy);

    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        fillRandomly(mlOrig);
        BOOST_CHECK(mlOrig != mlCopy);
        mlCopy = mlOrig;
        BOOST_CHECK(mlOrig == mlCopy);
        if (mlCopy.getMeasurements().size() > 1)
        {
            std::random_shuffle(mlCopy.getMeasurements().begin(), mlCopy.getMeasurements().end());
            BOOST_CHECK(mlOrig != mlCopy);
            mlCopy = mlOrig;
            BOOST_CHECK(mlOrig == mlCopy);
        }
    } //for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
