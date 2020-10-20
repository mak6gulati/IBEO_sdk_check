//==============================================================================
//!\file
//!\brief Test for FileLoggerBackend class.
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jun 26, 2018
//------------------------------------------------------------------------------

#define BOOST_TEST_MODULE FileLoggerBackendTest

//==============================================================================

#include <boost/test/unit_test.hpp>

#include <ibeo/common/logging/logging.hpp>
#include <TestSupport.hpp>

//==============================================================================

using namespace ibeo::common::logging;

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
namespace unittest {
//==============================================================================

//==============================================================================
BOOST_AUTO_TEST_SUITE(FileLoggerBackendTestSuite)
//==============================================================================

BOOST_AUTO_TEST_CASE(checkDefaultConfiguration)
{
    TestSupport::printTestName();

    FileLoggerBackend backend;
    BOOST_CHECK_EQUAL(backend.getFilePath(), "default.log");
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkValidConfiguration)
{
    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = "<Backend id=\"ibeo::common::logging::FileLoggerBackend\">"
                            "    <Path>testDirectory/testFilename.tst</Path>"
                            "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    FileLoggerBackend backend;
    BOOST_CHECK(backend.configure(configNode, false));

    BOOST_CHECK_EQUAL(backend.getFilePath(), "testDirectory/testFilename.tst");
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkValidConfigurationWithEnvVars)
{
#ifdef _WIN32
    static const char* const homeVarName{"USERPROFILE"};
#else
    static const char* const homeVarName{"HOME"};
#endif

    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = std::string()
                            + "<Backend id=\"ibeo::common::logging::FileLoggerBackend\">"
                              "    <Path>${"
                            + homeVarName
                            + "}/testDirectory/testFilename.tst</Path>"
                              "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    FileLoggerBackend backend;
    BOOST_CHECK(backend.configure(configNode, false));

    std::string homeVar = getenv(homeVarName);
    BOOST_CHECK_EQUAL(backend.getFilePath(), homeVar + "/testDirectory/testFilename.tst");
}

//==============================================================================
BOOST_AUTO_TEST_SUITE_END()
//==============================================================================

//==============================================================================
} // namespace unittest
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================
