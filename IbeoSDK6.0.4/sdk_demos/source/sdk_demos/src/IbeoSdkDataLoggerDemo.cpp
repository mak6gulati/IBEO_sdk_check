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
//!\example IbeoSdkDataLoggerDemo.cpp
//!
//! Demo project for data logging.
//! This tool is connecting to devices like a LUX sensor and saves the data into an IDC file.
//! This is basically an IbeoSdkWriterDemo with more elaborated
//! disk management.
//!
//! This implementation is only working on Linux (posix systems, not on windows).
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/lux.hpp>
#include <ibeo/common/sdk/scala.hpp>
#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/minilux.hpp>
#include <ibeo/common/sdk/devices/IdcFile.hpp>
#include <ibeo/common/sdk/IpHelper.hpp>

#include <boost/program_options.hpp>
#include <boost/asio.hpp>

#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/vfs.h>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkDataLoggerDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr logger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

class IdcWriter : ibeo::common::sdk::IdcFile, public ibeo::common::sdk::DataStreamer
{
public:
    IdcWriter(const std::string filename,
              IbeoEthDevice* device,
              const off_t fileSizeLimit,
              const double memoryConsumptionLimit);

    IdcWriter(const IdcWriter&) = delete; // forbidden
    IdcWriter& operator=(const IdcWriter&) = delete; // forbidden

    ~IdcWriter() override;

public:
    virtual bool create(const std::string& filename, const bool append = false) override;
    virtual void onData(const IbeoDataHeader& dh, const char* const bodyBuf) override;

    void checkFilesystemUsage(const std::string& devPath, uint64_t& diskSize, uint64_t& totalFreeBytes);
    bool isFileSystemUsageExceeded() const { return m_isFilesystemUsageExceeded; }

protected:
    std::string getFileName() const;
    void splitFileIfNeeded();

protected:
    std::string m_filenameTemplate;
    std::string m_currentFileName;
    off_t m_currentFileSize;
    const off_t m_fileSizeLimit;

    const double m_maxFilesystemUsage;
    bool m_isFilesystemUsageExceeded;
    bool m_isNewFile;
    uint32_t m_currFileIndex;
}; // IDCWriter

//==============================================================================

IdcWriter::IdcWriter(const std::string filename,
                     IbeoEthDevice* device,
                     const off_t fileSizeLimit,
                     const double memoryConsumptionLimit)
  : IdcFile(),
    m_filenameTemplate(filename),
    m_currentFileName(),
    m_currentFileSize(0),
    m_fileSizeLimit(fileSizeLimit),
    m_maxFilesystemUsage(memoryConsumptionLimit),
    m_isFilesystemUsageExceeded(false),
    m_isNewFile(true)
{
    const std::size_t len = m_filenameTemplate.length();
    if (len > 4)
    {
        // in case the provided filename ends with the .idc suffix
        // this will be stripped from the filename template.
        if (m_filenameTemplate.substr(len - 4) == ".idc")
        {
            m_filenameTemplate = m_filenameTemplate.substr(0, len - 4);
        }
    }

    m_currFileIndex = 0;
    this->create(this->getFileName(), false);

    if (device && this->isOpen())
    {
        device->registerStreamer(this);
    }
}

//==============================================================================

IdcWriter::~IdcWriter()
{
    // Calling this close method, the trailer will be written
    // to finalize the IDC file.
    this->close();
}

//==============================================================================

void IdcWriter::checkFilesystemUsage(const std::string& devPath, uint64_t& diskSize, uint64_t& totalFreeBytes)
{
    struct statfs fs;

    if ((statfs(devPath.c_str(), &fs)) < 0)
    {
        printf("Failed to stat %s: %s\n", devPath.c_str(), strerror(errno));
        diskSize       = 0;
        totalFreeBytes = 0;
    }
    else
    {
        diskSize       = static_cast<uint64_t>(fs.f_blocks) * static_cast<uint64_t>(fs.f_bsize);
        totalFreeBytes = static_cast<uint64_t>(fs.f_bfree) * static_cast<uint64_t>(fs.f_bsize);
    }
}

//==============================================================================

std::string split1000000(const unsigned long sz, const char sep)
{
    std::stringstream ss;
    if (sz < 1000000)
    {
        ss << '0';
    }
    else
    {
        ss << sz / 1000000;
    }
    ss << sep;
    ss << std::setfill('0');
    ss << std::setw(3) << (sz % 1000000);
    return ss.str();
}

//==============================================================================

bool IdcWriter::create(const std::string& filename, const bool append)
{
    if (filename.empty())
        return false;

    LOGINFO(logger, "========================================");

    std::string absPath;

    if (filename.at(0) == '/')
    {
        const size_t position = filename.rfind("/");
        absPath               = filename.substr(0, position > 0 ? position : 1);
    }
    else
    {
        char tempPath[200];
        absPath = getcwd(tempPath, 200);
    }

    bool result = false;

    uint64_t diskSize;
    uint64_t totalFreeBytes;
    this->checkFilesystemUsage(absPath, diskSize, totalFreeBytes);

    LOGINFO(logger, "Main path of the executable file: " << absPath);

    LOGINFO(logger, "Size of filesystem:       " << split1000000(diskSize, '.') << " MByte");
    LOGINFO(logger, "Free space on filesystem: " << split1000000(totalFreeBytes, '.') << " MByte");

    const double actualMemConsumptionPercent = 100.0 - ((double)totalFreeBytes * 100) / (double)diskSize;
    if (m_maxFilesystemUsage < actualMemConsumptionPercent)
    {
        m_isFilesystemUsageExceeded = true;
        this->close();
        result = false;
    }
    else
    {
        m_isFilesystemUsageExceeded = false;
        result                      = IdcFile::create(filename, append);
    }

    LOGINFO(logger,
            "Current harddrive usage: " << std::fixed << std::setprecision(3) << actualMemConsumptionPercent << "%");
    LOGINFO(logger, "Max harddrive usage:     " << std::fixed << std::setprecision(3) << m_maxFilesystemUsage << "%");

    if (m_isFilesystemUsageExceeded)
    {
        LOGINFO(logger, "==> Harddrive usage exceeds the limit.");
    }
    else
    {
        LOGINFO(logger, "==> Enough space on harddrive.");
    }

    if (result)
    {
        LOGINFO(logger, "Successfully open IDC file '" << filename << "'.");
    }
    else
    {
        LOGERROR(logger, "Failed to open IDC file '" << filename << "'.");
    }
    return result;
}

//==============================================================================

void IdcWriter::onData(const IbeoDataHeader& dh, const char* const bodyBuf)
{
    LOGDEBUG(logger, "Received message 0x" << std::hex << dh.getDataType());
    switch (dh.getDataType())
    {
    case DataTypeId::DataType_Scan2202:
    case DataTypeId::DataType_Scan2205:
    case DataTypeId::DataType_Scan2208:
        this->splitFileIfNeeded();
        break;
    default:
        break;
    }

    //dh.serialize(this->m_strm);
    const uint32_t sz = dh.getMessageSize();
    this->m_currentFileSize += sz;
    if (m_isNewFile)
    {
        IbeoDataHeader ndh(dh);
        ndh.setPreviousMessageSize(0);
        write(ndh, bodyBuf);
        m_isNewFile = false;
    }
    else
    {
        write(dh, bodyBuf);
    }
    //	this->write(bodyBuf, sz);
    LOGDEBUG(logger, "Total file size: " << this->m_currentFileSize);
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
    }
}

//==============================================================================

class CommandLineArguments
{
public:
    enum class Device : uint8_t
    {
        Ecu     = 1,
        Scala   = 2,
        Lux     = 3,
        MiniLux = 4
    };

public:
    CommandLineArguments(int argc, const char** argv)
    {
        using namespace boost::program_options;
        variables_map cmdVars;

        options_description desc("IbeoSdkDataLoggerDemo", 100);
        desc.add_options() //

            ("ip", value<std::string>(&m_ipAsStr)->required(), "Ip address of the sensor/ecu.") //
            ("port,p", value<uint16_t>(&m_port)->default_value(12002), "Port of the device.") //
            ("device,d",
             value<std::string>(&m_deviceAsString)->required(),
             "Name of the Device:"
             "\n    'ecu' for Ibeo Ecu"
             "\n    'scala' for Scala using TCP connection"
             "\n    'lux' for Ibeo Lux"
             "\n    'minilux' for Ibeo Minilux") //
            ("output,o", value<std::string>(&m_outputFile)->required(), "Name of the output IDC file") //
            ("maxfilesize,s",
             value<off_t>(&m_maxFileSize)->default_value(100000000),
             "Exceeding this size will trigger splitting the output file.") //
            ("maxharddriveusage,u",
             value<double>(&m_maxHarddriveUsage)->default_value(80.0),
             "If more space than this given percentage is occupied on the destination file system "
             "opening a new file will fail. The program will terminate."
             "This criteria will only be checked on program start and whenever the output file "
             "is split.") //
            ("logfile,l", value<std::string>(&m_logFileName), "Name of the log file (optional).") //
            ("help,h", "Show this message");

        positional_options_description pos_opts;
        pos_opts.add("ip", 1);
        pos_opts.add("output", 1);
        pos_opts.add("device", 1);
        pos_opts.add("logfile", 1);

        try
        {
            store(command_line_parser(argc, argv).options(desc).positional(pos_opts).run(), cmdVars);
            notify(cmdVars);
        }
        catch (const boost::program_options::multiple_occurrences& e)
        {
            std::cerr << "*** There are several occurrences of an option: " << e.what() << std::endl;
            desc.print(std::cerr);
            exit(1);
        }
        catch (const boost::program_options::error& e)
        {
            std::cerr << "*** Error in command line arguments: " << e.what() << std::endl;
            desc.print(std::cerr);
            exit(1);
        }

        if (cmdVars.count("help"))
        {
            desc.print(std::cerr);
            exit(0);
        }

        m_hasLogFile = cmdVars.count("logfile");

        boost::system::error_code ec;
        m_ip = boost::asio::ip::address::from_string(m_ipAsStr, ec);
        if (ec)
        {
            std::cerr << "IP address '" << m_ipAsStr << "' is not valid: " << ec.message() << std::endl;
        }
        else
        {
            m_valid = true;
        }

        setDeviceMap();

        if (m_deviceMap.find(m_deviceAsString) == m_deviceMap.end())
        {
            std::cerr << "Device " << m_deviceAsString << " is not valid!" << std::endl;
            m_valid = false;
        }
        else
        {
            m_device = m_deviceMap[m_deviceAsString];
        }
    }

public:
    bool useEcu() const { return m_useEcu; }
    bool hasLogFile() const { return m_hasLogFile; }
    bool isValid() const { return m_valid; }
    boost::asio::ip::address getIp() const { return m_ip; }
    std::string getIpAsString() const { return m_ipAsStr; }
    uint16_t getPort() const { return m_port; }
    const Device& getDevice() const { return m_device; }
    std::string getDeviceAsString() const { return m_deviceAsString; }
    const std::string& getOutputFile() const { return m_outputFile; }
    off_t getMaxFileSize() const { return m_maxFileSize; }
    double getMaxHarddriveUsage() const { return m_maxHarddriveUsage; }
    const std::string& getLogFileName() const { return m_logFileName; }

public:
    void setDeviceMap()
    {
        m_deviceMap.insert(std::pair<std::string, Device>("ecu", Device::Ecu));
        m_deviceMap.insert(std::pair<std::string, Device>("scala", Device::Scala));
        m_deviceMap.insert(std::pair<std::string, Device>("lux", Device::Lux));
        m_deviceMap.insert(std::pair<std::string, Device>("minilux", Device::MiniLux));
    }

protected:
    bool m_useEcu{false};
    bool m_hasLogFile{false};
    bool m_valid{false};
    boost::asio::ip::address m_ip{};
    std::string m_ipAsStr{};
    uint16_t m_port{};
    Device m_device{};
    std::string m_deviceAsString{};
    std::map<std::string, Device> m_deviceMap{};
    std::string m_outputFile{};
    off_t m_maxFileSize{100000000}; // 100 mByte
    double m_maxHarddriveUsage{80.0};
    std::string m_logFileName{};
}; // CommandLineArguments

//==============================================================================

void idcwriter_demo(const CommandLineArguments& cmdargs);

//==============================================================================

int main(const int argc, const char** argv)
{
    std::cerr << argv[0] << " (" << appName << ")"
              << " using IbeoSDK " << ibeoSdk.getVersion().toString() << std::endl;

    CommandLineArguments cmdargs(argc, argv);

    if (!cmdargs.isValid())
    {
        exit(1);
    }

    if (cmdargs.hasLogFile())
    {
        ibeo::common::logging::FileLoggerBackendSPtr fileLoggerBackend
            = std::dynamic_pointer_cast<ibeo::common::logging::FileLoggerBackend>(
                ibeo::common::logging::LogManager::getInstance().getBackendById(
                    ibeo::common::logging::FileLoggerBackend::getBackendId()));
        fileLoggerBackend->setFilePath(cmdargs.getLogFileName());
    }

    ibeo::common::logging::LogManager::getInstance().setDefaultLogLevel("Info");
    if (cmdargs.hasLogFile())
    {
        LOGINFO(logger,
                argv[0] << " (" << appName << ")"
                        << " using IbeoSDK " << ibeoSdk.getVersion().toString());
    }

    idcwriter_demo(cmdargs);

    exit(0);
}

//==============================================================================

void idcwriter_demo(const CommandLineArguments& cmdargs)
{
    std::unique_ptr<IbeoEthDevice> device{};
    std::unique_ptr<IdcWriter> writer{};

    switch (cmdargs.getDevice())
    {
    case CommandLineArguments::Device::Ecu:
        device.reset(new IbeoEcu{cmdargs.getIpAsString(), cmdargs.getPort()});
        break;
    case CommandLineArguments::Device::Lux:
        device.reset(new IbeoLux{cmdargs.getIpAsString(), cmdargs.getPort()});
        break;
    case CommandLineArguments::Device::Scala:
        device.reset(new IbeoScala{cmdargs.getIpAsString(), cmdargs.getPort()});
        break;
    case CommandLineArguments::Device::MiniLux:
        device.reset(new IbeoMiniLux{cmdargs.getIpAsString(), cmdargs.getPort()});
        break;
    default:
        LOGERROR(logger, "Device " << cmdargs.getDeviceAsString() << " is not supported by this Demo.");
        exit(1);
    }

    writer.reset(
        new IdcWriter(cmdargs.getOutputFile(), device.get(), cmdargs.getMaxFileSize(), cmdargs.getMaxHarddriveUsage()));
    device->connect();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (true)
    {
        if (!device->isConnected() || writer->isFileSystemUsageExceeded())
        {
            return;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

//==============================================================================
