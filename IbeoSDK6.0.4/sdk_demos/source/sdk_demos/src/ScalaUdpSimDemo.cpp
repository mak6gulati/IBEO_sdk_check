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
//!\date Apr 27, 2017
//!
//!\example ScalaUdpSimDemo.cpp Demo project for simulating an Scala device sending its data
//! via UDP
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/lux.hpp>
#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/minilux.hpp>
#include <ibeo/common/sdk/scala.hpp>

#include <ibeo/common/sdk/devices/IdcFile.hpp>

#include <ibeo/common/sdk/devices/sutp/IbeoSutpSendInterface.hpp>

#include <boost/asio.hpp>

#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "ScalaUdpSimDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

TimeConversion tc;

//==============================================================================

class ScalaSim
{
public:
    ScalaSim(const std::string filename, const unsigned short port = 2000);
    ~ScalaSim();

public:
    void run();

protected:
    void sendDataBlock(const IbeoDataHeader& dh, const std::shared_ptr<char> body);
    bool sendData(boost::asio::streambuf& outBuf);

protected:
    unsigned short m_port;
    boost::asio::io_service m_io_service;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_destinationEndpoint;
    std::string m_idcFileName;
    IdcFile m_idcFile;
    std::shared_ptr<IbeoSutpSendInterface> m_sutpSendInterface;
    uint32_t m_nbOfSendDatablocks;
}; // ScalaSim

//==============================================================================

ScalaSim::ScalaSim(const std::string filename, const unsigned short port)
  : m_port(port),
    m_io_service(),
    m_socket(m_io_service),
    m_destinationEndpoint(),
    m_idcFileName(filename),
    m_idcFile(),
    m_sutpSendInterface(),
    m_nbOfSendDatablocks(0)
{}

//==============================================================================

ScalaSim::~ScalaSim()
{
    boost::system::error_code error;
    m_socket.close(error);

    LOGINFO(appLogger, m_nbOfSendDatablocks << " send packages");
}

//==============================================================================

void ScalaSim::run()
{
    m_sutpSendInterface.reset(new IbeoSutpSendInterface(boost::bind(&ScalaSim::sendData, this, _1)));

    boost::system::error_code error;
    m_socket.open(boost::asio::ip::udp::v4(), error);

    m_socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    //	m_socket.set_option(boost::asio::socket_base::broadcast(true));

    boost::asio::ip::address destination_address = boost::asio::ip::address::from_string("127.0.0.1");
    m_destinationEndpoint                        = boost::asio::ip::udp::endpoint(destination_address, m_port);

    //	m_socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), m_port));
    //	m_socket.set_option(boost::asio::ip::multicast::join_group(listen_address));

    m_idcFile.open(m_idcFileName);
    if (!m_idcFile.isOpen())
    {
        LOGERROR(appLogger, "Cannot open IDC file '" << m_idcFileName << "'");
        return;
    }

    LOGINFO(appLogger, "Start sending");

    IbeoDataHeader dh;
    while (m_idcFile.isGood() && (m_nbOfSendDatablocks < 1000000))
    {
        //usleep(40);

        std::shared_ptr<char> body = m_idcFile.getNextDataBlockRaw(dh);

        if (body)
        {
            LOGDEBUG(appLogger, "Send data block: " << toHex(dh.getDataType()));
            sendDataBlock(dh, body);
        }
    } // while

    LOGINFO(appLogger, "Finished sending");
    LOGINFO(appLogger, m_nbOfSendDatablocks << " send datablocks");
    m_sutpSendInterface.reset();
}

//==============================================================================

void ScalaSim::sendDataBlock(const IbeoDataHeader& dh, const std::shared_ptr<char> body)
{
    LOGINFO(appLogger, "DataBlock: " << toHex(dh.getDataType()) << "  size: " << dh.getMessageSize());
    if (dh.getDataType() != DataTypeId::DataType_Image2403)
    {
        m_sutpSendInterface->send(dh, body.get());
        ++m_nbOfSendDatablocks;
    }
}

//==============================================================================

bool ScalaSim::sendData(boost::asio::streambuf& outBuf)
{
    LOGINFO(appLogger, "Actually sending");
    //	// serialize dh
    //	boost::array<char, 24> dhs;
    //	boost::iostreams::stream<boost::iostreams::array_sink> strm(dhs.begin(), dhs.end());
    //	std::ostream& s = (std::ostream&)strm;
    //	dh.serialize(s);
    //
    //	// combine header and body to a buffer sequence
    //	std::vector<boost::asio::const_buffer> data;
    //	data.push_back(boost::asio::buffer(dhs));
    //	data.push_back(boost::asio::buffer(body.get(), dh.getMessageSize()));

    // send data via UDP
    LOGINFO(appLogger, "Buffers size bytes: " << outBuf.size());

    const uint32_t len = uint32_t(m_socket.send_to(outBuf.data(), m_destinationEndpoint));
    LOGINFO(appLogger, "Send bytes: " << len);
    return true;
}

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

int checkArguments(const int argc, const char** argv, bool& hasLogFile)
{
    const int minNbOfNeededArguments = 2;
    const int maxNbOfNeededArguments = 3;

    bool wrongNbOfArguments = false;
    if (argc < minNbOfNeededArguments)
    {
        std::cerr << "Missing argument" << std::endl;
        wrongNbOfArguments = true;
    }
    else if (argc > maxNbOfNeededArguments)
    {
        std::cerr << "Too many argument" << std::endl;
        wrongNbOfArguments = true;
    }

    if (wrongNbOfArguments)
    {
        std::cerr << argv[0] << " "
                  << " INPUTFILENAME [LOGFILE]" << std::endl;
        std::cerr << "\tINPUTFILENAME Name of the file to use as input." << std::endl;
        std::cerr << "\tLOGFILE name of the log file (optional)." << std::endl;
        return 1;
    }

    hasLogFile = (argc == maxNbOfNeededArguments);
    return 0;
}

//==============================================================================

int main(const int argc, const char** argv)
{
    std::cerr << argv[0] << " (" << appName << ")"
              << " using IbeoSDK " << ibeoSdk.getVersion().toString() << std::endl;

    bool hasLogFile;
    const int checkResult = checkArguments(argc, argv, hasLogFile);
    if (checkResult != 0)
        exit(checkResult);
    int currArg = 1;

    std::string filename = argv[currArg++];

    if (hasLogFile)
    {
        ibeo::common::logging::FileLoggerBackendSPtr fileLoggerBackend
            = std::dynamic_pointer_cast<ibeo::common::logging::FileLoggerBackend>(
                ibeo::common::logging::LogManager::getInstance().getBackendById(
                    ibeo::common::logging::FileLoggerBackend::getBackendId()));
        fileLoggerBackend->setFilePath(argv[currArg++]);
    }

    ibeo::common::logging::LogManager::getInstance().setDefaultLogLevel("Debug");

    if (hasLogFile)
    {
        LOGINFO(appLogger,
                argv[0] << " (" << appName << ")"
                        << " using IbeoSDK " << ibeoSdk.getVersion().toString());
    }

    ScalaSim sim(filename, 2000);
    sim.run();

    exit(0);
}

//==============================================================================
