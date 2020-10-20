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
//! \date Feb 09, 2018
//------------------------------------------------------------------------------

#include "MeasurementListTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/MeasurementList.hpp>
#include <ibeo/common/sdk/datablocks/measurementlist/MeasurementList2821Importer2821.hpp>
#include <ibeo/common/sdk/datablocks/measurementlist/MeasurementList2821Exporter2821.hpp>

#include <vector>
#include <algorithm>

#define BOOST_TEST_MODULE MeasurementList2821Test
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(MeasurementList2821TestSuite)

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

BOOST_FIXTURE_TEST_CASE(createMeasurement2821Importer, Fixture)
{
    ibeo::common::sdk::MeasurementList2821Importer2821 mlImporter;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createMeasurement2821Exporter, Fixture)
{
    ibeo::common::sdk::MeasurementList2821Exporter2821 mlExporter;
    BOOST_CHECK(true);
}

//==============================================================================

//whole MeasurementList2821
BOOST_FIXTURE_TEST_CASE(isIoMeasurementListIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const MeasurementList2821Exporter2821 exporter;
        MeasurementList2821 mlOrig;
        mlOrig.setMeasurementList(createMeasurementList());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(mlOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, mlOrig));

        MeasurementList2821 mlCopy;
        const MeasurementList2821Importer2821 importer;
        BOOST_CHECK(importer.deserialize(ss, mlCopy, dh));
        BOOST_CHECK(mlOrig == mlCopy);
    } //for r
}

//==============================================================================

//operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isContentMeasurement2821Equal, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MeasurementList2821 mlOrig, mlCopy;
        BOOST_CHECK(mlOrig == mlCopy);
        do
        {
            fillRandomly(mlOrig.getMeasList());
        } while (mlOrig.getMeasList().getSize() < 1);
        BOOST_CHECK(mlOrig != mlCopy);

        mlCopy.getMeasList().getMeasurements().clear();
        const MeasurementList::MeasurementVector& measVec = mlOrig.getMeasList().getMeasurements();
        for (size_t i = 0; i < measVec.size() - 1; ++i)
        {
            mlCopy.getMeasList().addMeasurement(measVec.at(i));
            BOOST_CHECK(mlOrig != mlCopy);
        }
        mlCopy.getMeasList().addMeasurement(measVec.back());
        BOOST_CHECK(mlOrig == mlCopy);

        const uint16_t pos
            = getRandValue<uint16_t>(0, static_cast<uint16_t>(mlCopy.getMeasList().getMeasurements().size() - 1));
        mlCopy.getMeasList().getMeasurements().erase(mlCopy.getMeasList().getMeasurements().begin() + pos);

        BOOST_CHECK(mlOrig != mlCopy);
    } // for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isContentMeasurementList2821Assigned, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MeasurementList2821 mlOrig, mlCopy;
        BOOST_CHECK(mlOrig == mlCopy);
        fillRandomly(mlOrig.getMeasList());
        BOOST_CHECK(mlOrig != mlCopy);
        mlCopy = mlOrig;
        BOOST_CHECK(mlOrig == mlCopy);
    } //for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReorderedMeasurementList2821Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MeasurementList2821 mlOrig, mlCopy;
        BOOST_CHECK(mlOrig == mlCopy);

        fillRandomly(mlOrig.getMeasList());
        BOOST_CHECK(mlOrig != mlCopy);
        mlCopy = mlOrig;
        BOOST_CHECK(mlOrig == mlCopy);
        if (mlCopy.getMeasList().getMeasurements().size() > 1)
        {
            std::random_shuffle(mlCopy.getMeasList().getMeasurements().begin(),
                                mlCopy.getMeasList().getMeasurements().end());
            BOOST_CHECK(mlOrig != mlCopy);
            mlCopy = mlOrig;
            BOOST_CHECK(mlOrig == mlCopy);
        }
    } //for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
