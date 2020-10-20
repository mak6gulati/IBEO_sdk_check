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
//!\date Jan 12, 2018
//------------------------------------------------------------------------------

#include "common/MatrixTestSupport.hpp"

#define BOOST_TEST_MODULE MatrixTests
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(MatrixTestSuite)

//==============================================================================

class Fixture : public unittests::VectorTestSupport
{
}; // Fixture
using test_types = boost::mpl::list<float, double>;

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(checkConstructors, T, test_types)
{
    Matrix2x2<T> m22;
    Matrix3x3<T> m33;
    RotationMatrix2d<T> rm22;
    RotationMatrix3d<T> rm33;
    TransformationMatrix2d<T> tm22;
    TransformationMatrix3d<T> tm33;

    BOOST_CHECK(true);
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(isMatTimeInvMatIdentity2d, T, test_types)
{
    using namespace ibeo::common::sdk::unittests;

    for (uint32_t i = 0; i < MatrixTestSupport::nbOfRepeats; ++i)
    {
        // check inverse
        const auto m22 = MatrixTestSupport::createMatrix2x2<T>();
        if (m22.getDeterminant() != 0)
        {
            const auto m22inv   = m22.getInverse();
            const auto identity = m22inv * m22;

            const bool nearIdentity
                = fuzzyCompareT<3>(identity.get(1, 1), T(1.0)) && fuzzyCompareT<3>(identity.get(1, 2), T(0.0))
                  && fuzzyCompareT<3>(identity.get(2, 1), T(0.0)) && fuzzyCompareT<3>(identity.get(2, 2), T(1.0));

            BOOST_CHECK(nearIdentity);
        }
    } // for i
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(isMatTimeInvMatIdentity3d, T, test_types)
{
    using namespace ibeo::common::sdk::unittests;

    for (uint32_t i = 0; i < MatrixTestSupport::nbOfRepeats; ++i)
    {
        // check inverse
        const auto m33 = MatrixTestSupport::createMatrix3x3<T>();
        if (m33.getDeterminant() != 0)
        {
            const auto m33inv   = m33.getInverse();
            const auto identity = m33 * m33inv;

            const bool nearIdentity
                = fuzzyCompareT<3>(identity.get(1, 1), T(1.0)) && fuzzyCompareT<3>(identity.get(1, 2), T(0.0))
                  && fuzzyCompareT<3>(identity.get(1, 3), T(0.0)) && fuzzyCompareT<3>(identity.get(2, 1), T(0.0))
                  && fuzzyCompareT<3>(identity.get(2, 2), T(1.0)) && fuzzyCompareT<3>(identity.get(2, 3), T(0.0))
                  && fuzzyCompareT<3>(identity.get(3, 1), T(0.0)) && fuzzyCompareT<3>(identity.get(3, 2), T(0.0))
                  && fuzzyCompareT<3>(identity.get(3, 3), T(1.0));

            BOOST_CHECK(nearIdentity);
        }
    } // for i
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(isTransformationInvTransformationIdentify2d, T, test_types)
{
    using namespace ibeo::common::sdk::unittests;

    for (uint32_t i = 0; i < MatrixTestSupport::nbOfRepeats; ++i)
    {
        //========================================
        // check 2d transformation
        const auto p2a   = VectorTestSupport::createVector2<T>();
        const auto tma2b = MatrixTestSupport::createTransformationMatrix2d<T>();

        // transform vector from a to b
        const auto p2b = tma2b * p2a;

        // transform back to a
        const auto p2a2 = tma2b.getInverse() * p2b;
        const auto diff = p2a2 - p2a2;

        BOOST_CHECK(diff.getLength() < T(0.0001));
    }
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(isTransformationInvTransformationIdentify3d, T, test_types)
{
    using namespace ibeo::common::sdk::unittests;

    for (uint32_t i = 0; i < MatrixTestSupport::nbOfRepeats; ++i)
    {
        //========================================
        // check 3d transformation
        const auto p3a   = VectorTestSupport::createVector3<T>();
        const auto tma3b = MatrixTestSupport::createTransformationMatrix3d<T>();

        // transform vector from a to b
        const auto p3b = tma3b * p3a;

        // transform back to a
        const auto p3a2 = tma3b.getInverse() * p3b;
        BOOST_CHECK((p3a - p3a2).getLength() < T(0.0001));
    }
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(isGetInverseAndInvertTheSame2d, T, test_types)
{
    using namespace ibeo::common::sdk::unittests;

    for (uint32_t i = 0; i < MatrixTestSupport::nbOfRepeats; ++i)
    {
        auto tm2dOrig = MatrixTestSupport::createTransformationMatrix2d<T>();
        auto tm2dInv  = tm2dOrig.getInverse();
        tm2dOrig.invert();

        BOOST_CHECK(tm2dOrig == tm2dInv);
    }
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(isGetInverseAndInvertTheSame3d, T, test_types)
{
    using namespace ibeo::common::sdk::unittests;

    for (uint32_t i = 0; i < MatrixTestSupport::nbOfRepeats; ++i)
    {
        auto tm3dOrig = MatrixTestSupport::createTransformationMatrix3d<T>();
        auto tm3dInv  = tm3dOrig.getInverse();
        tm3dOrig.invert();

        BOOST_CHECK(tm3dOrig == tm3dInv);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
