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
//!\date May 4, 2017
//!
//!\example ScalaUdpLiveDemo.cpp Demo project for connecting to a Scala via UDP and process the received
//! data containers.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/scala.hpp>
#include <ibeo/common/sdk/devices/IbeoScala.hpp>
#include <ibeo/common/sdk/IpHelper.hpp>

#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkScalaLiveDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void printHelp(const char* name);

bool getArguments(const int argc,
                  const char** argv,
                  bool& useMulticast,
                  std::string& ip,
                  std::string& ifIp,
                  std::string& port,
                  std::string& logFile);

void live_demo(const bool& useMulticast,
               const std::string& ip,
               const std::string& port,
               const boost::asio::ip::address_v4& ifIp = boost::asio::ip::address_v4::any());

//==============================================================================

TimeConversion tc;

FrameEndSeparator1100 a;

//==============================================================================

class AllScalaListener
  : public ibeo::common::sdk::DataContainerListener<FrameEndSeparator1100, DataTypeId::DataType_FrameEndSeparator1100>,
    public ibeo::common::sdk::DataContainerListener<Scan2202, DataTypeId::DataType_Scan2202>,
    public ibeo::common::sdk::DataContainerListener<Scan2208, DataTypeId::DataType_Scan2208>,
    public ibeo::common::sdk::DataContainerListener<Scan, DataTypeId::DataType_Scan2202>,
    public ibeo::common::sdk::DataContainerListener<Scan, DataTypeId::DataType_Scan2208>,
    public ibeo::common::sdk::DataContainerListener<Scan2310, DataTypeId::DataType_Scan2310>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2221, DataTypeId::DataType_ObjectList2221>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2270, DataTypeId::DataType_ObjectList2270>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2271, DataTypeId::DataType_ObjectList2271>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2805, DataTypeId::DataType_VehicleStateBasic2805>,
    public ibeo::common::sdk::DataContainerListener<DeviceStatus6301, DataTypeId::DataType_DeviceStatus6301>,
    public ibeo::common::sdk::DataContainerListener<DeviceStatus6303, DataTypeId::DataType_DeviceStatus6303>,
    public ibeo::common::sdk::DataContainerListener<LogMessageError6400, DataTypeId::DataType_LogError6400>,
    public ibeo::common::sdk::DataContainerListener<LogMessageWarning6410, DataTypeId::DataType_LogWarning6410>,
    public ibeo::common::sdk::DataContainerListener<LogMessageNote6420, DataTypeId::DataType_LogNote6420>,
    public ibeo::common::sdk::DataContainerListener<LogMessageDebug6430, DataTypeId::DataType_LogDebug6430>
{
public:
    virtual ~AllScalaListener() {}

public:
    //========================================
    void onData(const FrameEndSeparator1100& fes) override
    {
        LOGINFO(appLogger, std::setw(5) << "Frame received: # " << fes.getFrameId());
    }

    //========================================
    void onData(const Scan& scan) override
    {
        LOGINFO(appLogger,
                std::setw(5) << " Bytes  "
                             << "Scan 2202 received: # " << scan.getScanNumber()
                             << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
    }

    //========================================
    void onData(const Scan2202& scan) override
    {
        LOGINFO(appLogger,
                std::setw(5) << " Bytes  "
                             << "Scan 2202 received: # " << scan.getScanNumber()
                             << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
    }

    //========================================
    void onData(const Scan2208& scan) override
    {
        LOGINFO(appLogger,
                std::setw(5) << " Bytes  "
                             << "Scan 2208 received: # " << scan.getScanNumber() << "  time: "
                             << tc.toString(scan.getSubScans().at(0).getStartScanTimestamp().toPtime(), 3));
    }

    //=======================================
    void onData(const Scan2310&) override { LOGINFO(appLogger, std::setw(5) << "Scan 2310 Container received"); }

    //========================================
    void onData(const ObjectList2221& objList) override
    {
        LOGINFO(appLogger, "ObjectList 2221 container received. #Obj:" << objList.getNbOfObjects());
    }

    //========================================
    void onData(const ObjectList2270& objList) override
    {
        LOGINFO(appLogger,
                "ObjectList 2270 received. Scan: " << objList.getScanNumber() << "  #Obj:" << objList.getNbOfObjects());
    }

    //========================================
    void onData(const ObjectList2271& objList) override
    {
        LOGINFO(appLogger,
                "ObjectList 2271 received. Scan: " << objList.getScanNumber()
                                                   << "  ObjLstId: " << int(objList.getObjectListId())
                                                   << "  #Obj:" << objList.getNbOfObjects());
    }

    //========================================

    void onData(const VehicleState2805& vs) override
    {
        LOGINFO(appLogger, "VS for Scan #: " << vs.getScanNumber() << "  " << tc.toString(vs.getTimestamp().toPtime()));
    }

    //========================================
    void onData(const DeviceStatus6301&) override { LOGINFO(appLogger, "DevStat 0x6303 container received"); }

    //========================================
    void onData(const DeviceStatus6303&) override { LOGINFO(appLogger, "DevStat 0x6303 container received"); }

    //========================================
    void onData(const LogMessageError6400& logMsg) override
    {
        LOGTRACE(appLogger,
                 "LogMessage (Error) received: time: " << int(logMsg.getTraceLevel()) << ": " << logMsg.getMessage());
    }

    //========================================
    void onData(const LogMessageWarning6410& logMsg) override
    {
        LOGTRACE(appLogger,
                 "LogMessage (Warning) received: time: " << int(logMsg.getTraceLevel()) << ": " << logMsg.getMessage());
    }

    //========================================
    void onData(const LogMessageNote6420& logMsg) override
    {
        LOGTRACE(appLogger,
                 "LogMessage (Note) received: time: " << int(logMsg.getTraceLevel()) << ": " << logMsg.getMessage());
    }

    //========================================
    void onData(const LogMessageDebug6430& logMsg) override
    {
        LOGTRACE(appLogger,
                 "LogMessage (Debug) received: time: " << int(logMsg.getTraceLevel()) << ": " << logMsg.getMessage());
    }
}; // AllScalaListener

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

void printHelp(const char* name)
{
    std::cerr << name << " "
              << " UDP [LOGFILE]" << std::endl;
    std::cerr << "\t -h, --help, print help" << std::endl;
    std::cerr << "\t--ip is the ip of the multicast group, default is 224.100.100.100" << std::endl;
    std::cerr << "\t--ifIp ip address of interface to use, default is address:any()" << std::endl;
    std::cerr << "\t--port is the udp port the Scala sensor sends to, default is 22017" << std::endl;
    std::cerr << "\t-u Scala sensor uses udp unicast, default if not specified." << std::endl;
    std::cerr << "\t-m Scala sensor uses udp multicast." << std::endl;
    std::cerr << "\tLOGFILE name of the log file (optional)." << std::endl;
}

//==============================================================================

bool getArguments(const int argc,
                  const char** argv,
                  bool& useMulticast,
                  std::string& ip,
                  std::string& ifIp,
                  std::string& port,
                  std::string& logFile)
{
    bool printHelpUsed = false;

    for (int i = 0; i < argc; i++)
    {
        if (std::string(argv[i]) == "--ip")
        {
            if (i + 1 < argc)
                ip = std::string(argv[i + 1]);
        }
        if (std::string(argv[i]) == "--ifIp")
        {
            if (i + 1 < argc)
                ifIp = std::string(argv[i + 1]);
        }
        if (std::string(argv[i]) == "--port")
        {
            if (i + 1 < argc)
                port = std::string(argv[i + 1]);
        }
        if (std::string(argv[i]) == "-m")
        {
            useMulticast = true;
        }
        if (std::string(argv[i]) == "-l")
        {
            if (i + 1 < argc)
                logFile = std::string(argv[i + 1]);
        }
        if ((std::string(argv[i]) == "-h") || (std::string(argv[i]) == "--help"))
        {
            printHelpUsed = true;
            printHelp(argv[0]);
        }
    }

    return !printHelpUsed;
}

//==============================================================================

int main(const int argc, const char** argv)
{
    std::cerr << argv[0] << " (" << appName << ")"
              << " using IbeoSDK " << ibeoSdk.getVersion().toString() << std::endl;

    bool useMulticast   = false;
    std::string port    = "22017";
    std::string ip      = "224.100.100.100";
    std::string ifIp    = "";
    std::string logFile = "";

    if (getArguments(argc, argv, useMulticast, ip, ifIp, port, logFile))
    {
        if (logFile.length())
        {
            ibeo::common::logging::FileLoggerBackendSPtr fileLoggerBackend
                = std::dynamic_pointer_cast<ibeo::common::logging::FileLoggerBackend>(
                    ibeo::common::logging::LogManager::getInstance().getBackendById(
                        ibeo::common::logging::FileLoggerBackend::getBackendId()));
            fileLoggerBackend->setFilePath(logFile);
        }

        ibeo::common::logging::LogManager::getInstance().setDefaultLogLevel("Debug");

        if (logFile.length())
        {
            LOGINFO(appLogger,
                    argv[0] << " (" << appName << ")"
                            << " using IbeoSDK " << ibeoSdk.getVersion().toString());
        }

        if (ifIp.length())
        {
            live_demo(useMulticast, ip, port, boost::asio::ip::address_v4::from_string(ifIp));
        }
        else
        {
            live_demo(useMulticast, ip, port);
        }
    }

    exit(0);
}

//==============================================================================

void live_demo(const bool& useMulticast,
               const std::string& ip,
               const std::string& port,
               const boost::asio::ip::address_v4& ifIp)
{
    AllScalaListener allScalaListener;

    uint16_t portVal;
    std::stringstream ss;
    ss.str(port);
    ss >> portVal;

    std::shared_ptr<IbeoScala> scala;

    if (useMulticast)
    {
        scala.reset(new IbeoScala(ip, portVal, IbeoTypeEthUdpMulticast(), ifIp));
    }
    else
    {
        scala.reset(new IbeoScala(ip, portVal, IbeoTypeEthUdp(), ifIp));
    }

    scala->registerContainerListener(&allScalaListener);
    scala->connect();

    // Just to keep the program alive
    while (true)
    {
        if (!scala->isConnected())
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
