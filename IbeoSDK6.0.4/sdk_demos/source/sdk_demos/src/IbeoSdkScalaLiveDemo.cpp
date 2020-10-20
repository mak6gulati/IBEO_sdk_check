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
//!\date Oct 5, 2013
//!
//!\example IbeoSdkScalaLiveDemo.cpp Demo project for connecting to a Scala and process the received
//! data containers.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/scala.hpp>
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

void live_demo(std::string ip);

//==============================================================================

TimeConversion tc;

//==============================================================================

class AllScalaListener
  : public ibeo::common::sdk::DataContainerListener<FrameEndSeparator1100, DataTypeId::DataType_FrameEndSeparator1100>,
    public ibeo::common::sdk::DataContainerListener<Scan2202, DataTypeId::DataType_Scan2202>,
    public ibeo::common::sdk::DataContainerListener<Scan2208, DataTypeId::DataType_Scan2208>,
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
    void onData(const Scan2202& scan) override
    {
        LOGINFO(appLogger,
                std::setw(5) << "Scan 2202 received: # " << scan.getScanNumber()
                             << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
    }

    //========================================
    void onData(const Scan2208& scan) override
    {
        LOGINFO(appLogger,
                std::setw(5) << "Scan 2208 received: # " << scan.getScanNumber() << "  time: "
                             << tc.toString(scan.getSubScans().at(0).getStartScanTimestamp().toPtime(), 3));
    }

    //========================================
    void onData(const ObjectList2221& objList) override
    {
        LOGINFO(appLogger, "ObjectList 2221 container received. #Obj:" << objList.getNbOfObjects());
    }

    //========================================
    void onData(const ObjectList2270& objList) override
    {
        LOGINFO(appLogger, "ObjectList2270 contianer received: # " << objList.getNbOfObjects());
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

    //=======================================
    void onData(const Scan2310&) override { LOGINFO(appLogger, std::setw(5) << "Scan 2310 Container received"); }

    //========================================
    void onData(const DeviceStatus6301&) override { LOGINFO(appLogger, "DevStat 0x6301 container received"); }

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
                  << " IP [LOGFILE]" << std::endl;
        std::cerr << "\tIP is the ip address of the Scala sensor, e.g. 192.168.0.1." << std::endl;
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
    {
        exit(checkResult);
    }
    int currArg = 1;

    std::string ip = argv[currArg++];

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

    live_demo(ip);

    exit(0);
}

//==============================================================================

void live_demo(std::string ip)
{
    AllScalaListener allScalaListener;

    const uint16_t port = getPort(ip, 22017);
    IbeoScala scala(ip, port, IbeoTypeEthUdp());

    scala.registerContainerListener(&allScalaListener);
    // A connection to the Scala sensor can be established in two ways. First:
    //scala.setRecvTimeoutSeconds(5);
    //scala.getConnected();
    // or, second, by one single command:
    scala.connect(5);

    // Just to keep the program alive
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
