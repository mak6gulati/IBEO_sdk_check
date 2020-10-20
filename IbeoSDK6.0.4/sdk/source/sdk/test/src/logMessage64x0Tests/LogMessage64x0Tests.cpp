//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Feb 12, 2018
//------------------------------------------------------------------------------

#include <logMessage64x0Tests/LogMessage64x0TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/logmessages/LogMessageError6400Exporter6400.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageError6400Importer6400.hpp>

#include <ibeo/common/sdk/datablocks/logmessages/LogMessageWarning6410Exporter6410.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageWarning6410Importer6410.hpp>

#include <ibeo/common/sdk/datablocks/logmessages/LogMessageNote6420Exporter6420.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageNote6420Importer6420.hpp>

#include <ibeo/common/sdk/datablocks/logmessages/LogMessageDebug6430Exporter6430.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageDebug6430Importer6430.hpp>

#define BOOST_TEST_MODULE LogMessage64x0Test
#include <boost/test/unit_test.hpp>

#include <set>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(LogMessage64x0TestSuite)

//==============================================================================

class Fixture : public unittests::LogMessage64x0TestSupport
{
}; // Fixture

template<class C, class E, class I>
class Triple
{
public:
    using Container = C;
    using Exporter  = E;
    using Importer  = I;
};

using LogMessageTypes = boost::mpl::list<
    Triple<LogMessageError6400, LogMessageError6400Exporter6400, LogMessageError6400Importer6400>,
    Triple<LogMessageWarning6410, LogMessageWarning6410Exporter6410, LogMessageWarning6410Importer6410>,
    Triple<LogMessageNote6420, LogMessageNote6420Exporter6420, LogMessageNote6420Importer6420>,
    Triple<LogMessageDebug6430, LogMessageDebug6430Exporter6430, LogMessageDebug6430Importer6430>>;

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isIoOfEmptyLogMessage64x0Identity, MTT, LogMessageTypes, Fixture)
{
    using C = typename MTT::Container;
    using E = typename MTT::Exporter;
    using I = typename MTT::Importer;

    {
        const E exporter;
        C emOrig(createEmptyMsg<C>());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(emOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, emOrig));

        C emCopy;
        const I importer;
        BOOST_CHECK(importer.deserialize(ss, emCopy, dh));

        BOOST_CHECK(emOrig == emCopy);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isIoLogMessage64x0Identity, MTT, LogMessageTypes, Fixture)
{
    using C = typename MTT::Container;
    using E = typename MTT::Exporter;
    using I = typename MTT::Importer;

    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const E exporter;
        C emOrig(createMsg<C>());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(emOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, emOrig));

        C emCopy;
        const I importer;
        BOOST_CHECK(importer.deserialize(ss, emCopy, dh));

        BOOST_CHECK(emOrig == emCopy);

        if (emOrig != emCopy)
        {
            std::cerr << std::hex;
            for (auto c : emOrig.getMessage())
            {
                std::cerr << int(c) << " ";
            }
            std::cerr << std::endl;
            for (auto c : emCopy.getMessage())
            {
                std::cerr << int(c) << " ";
            }
            std::cerr << std::endl;
            std::cerr << std::endl;
        }

    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(allLogMessageTypesHashesAreUnique, Fixture)
{
    const std::unique_ptr<OwningVector> allClasses{getAllLogMessages()};

    std::set<std::size_t> allHashes;
    int idx = 0;
    for (auto lm : allClasses->getVector())
    {
        auto* sdc = dynamic_cast<SpecializedDataContainer*>(lm);
        auto res  = allHashes.insert(sdc->getClassIdHash());
        BOOST_CHECK_MESSAGE(res.second, "Hash " << sdc->getClassIdHash() << " appears twice. " << idx << "'s check.");
        ++idx;
    }

    BOOST_CHECK(allHashes.size() == 4);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(allLogMessageTypesTraceLevelsAreUnique, Fixture)
{
    const std::unique_ptr<OwningVector> allClasses{getAllLogMessages()};

    std::set<LogMessage64x0Base::TraceLevel> allHashes;
    int idx = 0;
    for (auto lm : allClasses->getVector())
    {
        auto res = allHashes.insert(lm->getTraceLevel());
        BOOST_CHECK_MESSAGE(res.second,
                            "Hash " << int(lm->getTraceLevel()) << " appears twice. " << idx << "'s check.");
        ++idx;
    }

    BOOST_CHECK(allHashes.size() == 4);
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
