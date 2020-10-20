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

#include "IdcOStreamTestSupport.hpp"
#include <ibeo/common/sdk/devices/IdcIStream.hpp>
#include <boost/filesystem.hpp>

#define BOOST_TEST_MODULE IdcOStreamTests
#include <boost/test/unit_test.hpp>

#include <cstdio>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(IdcOStreamTestSuite)

//==============================================================================

class FileFixture : public unittests::IdcOStreamTestSupport
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

class StreamFixture : public unittests::IdcOStreamTestSupport
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

BOOST_FIXTURE_TEST_CASE(writeStreamCorrectly, StreamFixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        reset();
        {
            IdcOStream os(m_ss);
            BOOST_CHECK(!os.isFile());
            BOOST_CHECK(fillStream(os));
        } // os has to be destroyed to write the index and trailer

        IdcIStream is(m_ss);
        IbeoDataHeader dh;

        for (const auto& e : m_blocksInStream)
        {
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);

            BOOST_REQUIRE(body.get());
            BOOST_CHECK(dh == e.first);
            BOOST_CHECK(std::memcmp(body.get(), e.second.get(), dh.getMessageSize()) == 0);
        }

        { // check for index and trailer
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);
            BOOST_REQUIRE(body.get());
            BOOST_CHECK(dh.getDataType() == DataTypeId::DataType_FrameIndex6130);
            body = is.getNextDataBlockRaw(dh);
            BOOST_REQUIRE(body.get());
            BOOST_CHECK(dh.getDataType() == DataTypeId::DataType_IdcTrailer6120);

            BOOST_CHECK(is.isGood());
            BOOST_CHECK(!is.isEof());
        }

        { // check reading beyond file end
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);
            BOOST_REQUIRE(!body.get());
            BOOST_CHECK(is.isEof());
            BOOST_CHECK(!is.isGood());
        }
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(writeFileCorrectly, FileFixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        FileObject fo;

        {
            IdcOStream os(fo.getFilename());
            BOOST_CHECK(os.isFile());
            BOOST_CHECK(fillStream(os));
        } // os has to be destroyed to write the index and trailer

        fo.reopen();
        IdcIStream is(fo());
        IbeoDataHeader dh;

        for (const auto& e : m_blocksInStream)
        {
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);

            BOOST_REQUIRE(body.get());
            BOOST_CHECK(dh == e.first);
            BOOST_CHECK(std::memcmp(body.get(), e.second.get(), dh.getMessageSize()) == 0);
        }

        { // check for index and trailer
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);
            BOOST_REQUIRE(body.get());
            BOOST_CHECK(dh.getDataType() == DataTypeId::DataType_FrameIndex6130);
            body = is.getNextDataBlockRaw(dh);
            BOOST_REQUIRE(body.get());
            BOOST_CHECK(dh.getDataType() == DataTypeId::DataType_IdcTrailer6120);

            BOOST_CHECK(is.isGood());
            BOOST_CHECK(!is.isEof());
        }

        { // check reading beyond file end
            std::shared_ptr<char> body = is.getNextDataBlockRaw(dh);
            BOOST_REQUIRE(!body.get());
            BOOST_CHECK(is.isEof());
            BOOST_CHECK(!is.isGood());
        }
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
