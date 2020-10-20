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
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#include "IdcIStreamTestSupport.hpp"
#include <ibeo/common/sdk/devices/IdcIStream.hpp>
#include <boost/filesystem.hpp>

#define BOOST_TEST_MODULE IdcIStreamTests

#include <boost/test/unit_test.hpp>

#include <cstdio>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(IdcIStreamTestSuite)

//==============================================================================

class FileFixture : public unittests::IdcIStreamTestSupport
{
public:
    class FileObject
    {
    public:
        FileObject()
        {
            boost::filesystem::path tempfile = boost::filesystem::unique_path();
            m_filename                       = tempfile.make_preferred().string();
            m_fs.open(m_filename.c_str(), std::fstream::out | std::fstream::binary);
            reopen();
        }

        ~FileObject()
        {
            m_fs.close();
            std::remove(m_filename.c_str());
        }

    public:
        std::fstream& operator()() { return m_fs; }

    public:
        const std::string& getFilename() const { return m_filename; }

    public:
        void reopen()
        {
            m_fs.close();
            m_fs.open(m_filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
        }

    private:
        std::string m_filename;
        std::fstream m_fs;
    }; // FileObject
}; // Fixture

//==============================================================================

class StreamFixture : public unittests::IdcIStreamTestSupport
{
protected:
    void reset()
    {
        m_ss.str("");
        m_ss.clear();
    }

protected:
    std::stringstream m_ss;
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(readStreamCorrectly, StreamFixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        reset();
        BOOST_CHECK(fillStream(m_ss));
        IdcIStream is(m_ss);
        BOOST_CHECK(!is.isFile());
        BOOST_CHECK(is.isGood());
        BOOST_CHECK(!is.isEof());

        IbeoDataHeader dh;
        for (const auto& e : m_blocksInStream)
        {
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);

            BOOST_CHECK(body.get());
            BOOST_CHECK(dh == e.first);
            BOOST_CHECK(std::memcmp(body.get(), e.second.get(), dh.getMessageSize()) == 0);

            BOOST_CHECK(is.isGood());
            BOOST_CHECK(!is.isEof());
        }

        { // check reading beyond file end
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);
            BOOST_CHECK(!body.get());
            BOOST_CHECK(is.isEof());
            BOOST_CHECK(!is.isGood());
        }
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(readFileCorrectly, FileFixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        FileObject fo;

        BOOST_CHECK(fillStream(fo()));

        IdcIStream is(fo.getFilename());
        BOOST_CHECK(is.isFile());
        BOOST_CHECK(is.isGood());
        BOOST_CHECK(!is.isEof());

        IbeoDataHeader dh;
        for (const auto& e : m_blocksInStream)
        {
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);

            BOOST_CHECK(body.get());
            BOOST_CHECK(dh == e.first);
            BOOST_CHECK(std::memcmp(body.get(), e.second.get(), dh.getMessageSize()) == 0);

            BOOST_CHECK(is.isGood());
            BOOST_CHECK(!is.isEof());
        }

        { // check reading beyond file end
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);
            BOOST_CHECK(!body.get());
            BOOST_CHECK(is.isEof());
            BOOST_CHECK(!is.isGood());
        }
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
