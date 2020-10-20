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
//! \date Sep 28, 2015
//------------------------------------------------------------------------------

//==============================================================================

#include "ObjectList2271TestSupport.hpp"

#define BOOST_TEST_MODULE Object2271Test
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(Object2271Suite)

//==============================================================================

class Fixture : public unittests::ObjectListScala2271TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentity, Fixture)
{
    for (int ua = 0; ua <= 1; ++ua)
    {
        for (int uc = 0; uc <= 1; ++uc)
        {
            if (ua == 0 && uc == 1)
                continue;

            for (int fa = 0; fa <= 1; ++fa)
            {
                for (int fc = 0; fc <= 1; ++fc)
                {
                    if (fa == 0 && fc == 1)
                        continue;

                    ObjectIn2271 objOrig = createObj((ua != 0) ? true : false,
                                                     (uc != 0) ? true : false,
                                                     (fa != 0) ? true : false,
                                                     (fc != 0) ? true : false);

                    std::stringstream ss;
                    BOOST_CHECK(objOrig.serialize(ss));

                    ObjectIn2271 objCopy;
                    BOOST_CHECK(objCopy.deserialize(ss));

                    BOOST_CHECK(objOrig.getFilteredObjectData() == objCopy.getFilteredObjectData());
                    BOOST_CHECK(objOrig.getUnfilteredObjectData() == objCopy.getUnfilteredObjectData());

                    BOOST_CHECK(objOrig == objCopy);
                }
            }
        }
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
