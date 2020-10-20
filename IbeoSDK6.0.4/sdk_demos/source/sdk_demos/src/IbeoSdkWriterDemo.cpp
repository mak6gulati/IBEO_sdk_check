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
//!\date Jul 21, 2012
//!
//!\example IbeoSdkWriterDemo.cpp
//! Demo project connecting to a device like LUX or Scala and writing the received
//! data blocks to an IDC file.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/lux.hpp>
#include <ibeo/common/sdk/luxhr.hpp>
#include <ibeo/common/sdk/scala.hpp>
#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/minilux.hpp>
#include <ibeo/common/sdk/devices/IdcFile.hpp>
#include <ibeo/common/sdk/IpHelper.hpp>

#include <ibeo/common/sdk/datablocks/scan/ScanExporter2209.hpp>

#include <sstream>
#include <iomanip>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkWriterDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

class IdcWriter : ibeo::common::sdk::IdcFile, public ibeo::common::sdk::DataStreamer
{
public:
    IdcWriter(const std::string filename, const off_t fileSizeLimit);

    virtual ~IdcWriter();

private:
    IdcWriter(const IdcWriter&); // forbidden
    IdcWriter& operator=(const IdcWriter&); // forbidden

public:
    bool create(const std::string& filename, const bool append = false) override;

    bool isOpen() override { return ibeo::common::sdk::IdcFile::isOpen(); }

    void onData(const IbeoDataHeader& dh, const char* const bodyBuf) override;

protected:
    std::string getFileName() const;

    void splitFileIfNeeded();

    void writeDataContainer(const IbeoDataHeader& dh, const char* bodyBuf);

protected:
    std::string m_filenameTemplate;
    std::string m_currentFileName;
    off_t m_currentFileSize;
    const off_t m_fileSizeLimit;
    uint32_t m_sizeOfPreviousMessage;
    bool m_isNewFile;
    uint32_t m_currFileIndex;
}; // IdcWriter

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

IdcWriter::IdcWriter(const std::string filename, const off_t fileSizeLimit)
  : IdcFile(),
    m_filenameTemplate(filename),
    m_currentFileName(),
    m_currentFileSize(0),
    m_fileSizeLimit(fileSizeLimit),
    m_sizeOfPreviousMessage(0),
    m_isNewFile(true)
{
    const std::size_t len = m_filenameTemplate.length();
    if (len > 4)
    {
        if (m_filenameTemplate.substr(len - 4) == ".idc")
        {
            m_filenameTemplate = m_filenameTemplate.substr(0, len - 4);
        }
    }

    m_currFileIndex = 0;
    this->create(this->getFileName(), false);
}

//==============================================================================

IdcWriter::~IdcWriter()
{
    // Calling this close method, the trailer will be written
    // to finalize the IDC file.
    this->close();
}

//==============================================================================

bool IdcWriter::create(const std::string& filename, const bool append)
{
    const bool result = IdcFile::create(filename, append);

    if (result)
    {
        LOGINFO(appLogger, "Successfully open IDC file '" << filename << "'.");
    }
    else
    {
        LOGERROR(appLogger, "Failed to open IDC file '" << filename << "'.");
    }
    return result;
}

//==============================================================================

void IdcWriter::onData(const IbeoDataHeader& dh, const char* const bodyBuf)
{
    LOGDEBUG(appLogger, "Received message 0x" << std::hex << dh.getDataType() << std::dec);

    switch (dh.getDataType())
    {
    case DataTypeId::DataType_Scan2202:
    case DataTypeId::DataType_Scan2205:
    case DataTypeId::DataType_Scan2208:
    case DataTypeId::DataType_Scan2209:
        this->splitFileIfNeeded();
        break;

    case DataTypeId::DataType_IdcTrailer6120:
    case DataTypeId::DataType_FrameIndex6130:
        LOGDEBUG(appLogger, "Skip writing datatype " << toHex(dh.getDataType()));
        return;

    default:
        break;
    }

    writeDataContainer(dh, bodyBuf);
}

//==============================================================================

std::string IdcWriter::getFileName() const
{
    std::stringstream ss;
    ss << m_filenameTemplate;
    ss << "_" << std::setfill('0') << std::setw(4) << m_currFileIndex;
    ss << ".idc";
    return ss.str();
}

//==============================================================================

void IdcWriter::splitFileIfNeeded()
{
    if (m_currentFileSize >= m_fileSizeLimit)
    {
        this->close();

        ++m_currFileIndex;

        this->create(this->getFileName(), false);
        m_currentFileSize = 0;
        m_isNewFile       = true;
    }
}

//==============================================================================

void IdcWriter::writeDataContainer(const IbeoDataHeader& dh, const char* bodyBuf)
{
    const uint32_t sz = dh.getMessageSize();
    m_currentFileSize += sz;

    IbeoDataHeader ndh(dh);
    ndh.setPreviousMessageSize(m_isNewFile ? 0 : m_sizeOfPreviousMessage);

    if (m_isNewFile)
    {
        m_isNewFile = false;
    }
    write(ndh, bodyBuf);
    m_sizeOfPreviousMessage = ndh.getMessageSize();

    LOGTRACE(appLogger, "Total file size: " << m_currentFileSize);
}

//==============================================================================

//==============================================================================
//==============================================================================

//==============================================================================

void idcWriterLux_demo(const std::string& ip, const std::string& outFilename);

//==============================================================================

void idcWriterEcu_demo(const std::string& ip, const std::string& outFilename);

//==============================================================================

void idcWriterScala_demo(const std::string& ip, const std::string& outFilename);

//==============================================================================

void idcWriterMiniLux_demo(const std::string& ip, const std::string& outFilename);

//==============================================================================

void idcWriterLuxHr_demo(const std::string& ip, const std::string& outFilename);

//==============================================================================
//==============================================================================
//==============================================================================

int checkArguments(const int argc, const char** argv, bool& useEcu, bool& hasLogFile)
{
    useEcu = false;
    if (argc > 1 && argv[1] == std::string("-e"))
    {
        useEcu = true;
    }
    const int minNbOfNeededArguments = 3 + (useEcu ? 1 : 0);
    const int maxNbOfNeededArguments = 4 + (useEcu ? 1 : 0);

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
                  << "[-e] IP OUTPUTFILENAME [LOGFILE]" << std::endl;
        std::cerr << "\t-e:\tIf given and the given port is 12002: Sensor is an ECU instead of a LUX." << std::endl;
        std::cerr << "\tIP is the ip address of the sensor and its port, e.g. 192.168.0.1:12004." << std::endl
                  << "\t\tIf the port is omitted, port 12002 will be used." << std::endl
                  << "\t\tPort 12002: Lux or Ecu" << std::endl
                  << "\t\tPort 12004: Scala" << std::endl
                  << "\t\tPort 12006: MiniLux" << std::endl
                  << "\t\tPort 12008: LuxHR" << std::endl;
        std::cerr << "\tOUTPUTFILENAME name of the output file." << std::endl;
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

    bool useEcu;
    bool hasLogFile;
    const int checkResult = checkArguments(argc, argv, useEcu, hasLogFile);
    if (checkResult != 0)
    {
        exit(checkResult);
    }

    int currArg = 1 + (useEcu ? 1 : 0);

    std::string ip                = argv[currArg++];
    const uint16_t port           = getPort(ip, 12002);
    const std::string outFilename = argv[currArg++];

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

    switch (port)
    {
    case 12002:
        if (useEcu)
        {
            idcWriterEcu_demo(ip, outFilename);
        }
        else
        {
            idcWriterLux_demo(ip, outFilename);
        }
        break;

    case 12004:
        idcWriterScala_demo(ip, outFilename);
        break;

    case 12006:
        idcWriterMiniLux_demo(ip, outFilename);
        break;

    case 12008:
        idcWriterLuxHr_demo(ip, outFilename);
        break;

    default:
        LOGERROR(appLogger, "Port " << port << " is not supported by any known device.");
        break;
    }

    exit(0);
}

//==============================================================================

void idcWriterLux_demo(const std::string& ip, const std::string& outFilename)
{
    IbeoLux lux(ip);

    IdcWriter idcWriter(outFilename, 10000000);
    if (idcWriter.isOpen())
    {
        lux.registerStreamer(&idcWriter);
    }
    lux.connect();

    while (true)
    {
        if (!lux.isConnected())
        {
            return;
        }
#ifdef _WIN32
        ::Sleep(1);
#else // _WIN32
        sleep(1);
#endif // _WIN32
    }
}

//==============================================================================

void idcWriterEcu_demo(const std::string& ip, const std::string& outFilename)
{
    IbeoEcu ecu(ip);

    IdcWriter idcWriter(outFilename, 1000000000);
    if (idcWriter.isOpen())
    {
        ecu.registerStreamer(&idcWriter);
    }
    ecu.getConnected();

    while (true)
    {
        if (!ecu.isConnected())
        {
            return;
        }
#ifdef _WIN32
        ::Sleep(1);
#else // _WIN32
        sleep(1);
#endif // _WIN32
    }
}

//==============================================================================

void idcWriterScala_demo(const std::string& ip, const std::string& outFilename)
{
    IbeoScala scala(ip);

    IdcWriter idcWriter(outFilename, 10000000);
    if (idcWriter.isOpen())
    {
        scala.registerStreamer(&idcWriter);
    }
    scala.connect();

    while (true)
    {
        if (!scala.isConnected())
        {
            return;
        }
#ifdef _WIN32
        ::Sleep(1);
#else // _WIN32
        sleep(1);
#endif // _WIN32
    }
}

//==============================================================================

void idcWriterMiniLux_demo(const std::string& ip, const std::string& outFilename)
{
    IbeoMiniLux miniLux(ip);

    IdcWriter idcWriter(outFilename, 10000000);
    if (idcWriter.isOpen())
    {
        miniLux.registerStreamer(&idcWriter);
    }
    miniLux.connect();

    while (true)
    {
        if (!miniLux.isConnected())
        {
            return;
        }
#ifdef _WIN32
        ::Sleep(1);
#else // _WIN32
        sleep(1);
#endif // _WIN32
    }
}

//==============================================================================

void idcWriterLuxHr_demo(const std::string& ip, const std::string& outFilename)
{
    IbeoLuxHr luxHr(ip);

    IdcWriter idcWriter(outFilename, 10000000);
    if (idcWriter.isOpen())
    {
        luxHr.registerStreamer(&idcWriter);
    }
    luxHr.connect();

    while (true)
    {
        if (!luxHr.isConnected())
        {
            return;
        }
#ifdef _WIN32
        ::Sleep(1);
#else // _WIN32
        sleep(1);
#endif // _WIN32
    }
}

//==============================================================================
