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
//!\date Oct 23, 2015
//!
//!\example IbeoSdkTrackingBoxLiveDemo.cpp Demo project for connecting to a LUX and process the received
//! data containers.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/trackingbox.hpp>
#include <ibeo/common/sdk/IpHelper.hpp>

#include <ibeo/common/sdk/listener/DataContainerListener.hpp>

#include <ibeo/common/sdk/datablocks/commands/ecucommands/ecucommands.hpp>

#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkTrackingBoxLiveDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void live_demo(std::string ip);

//==============================================================================

TimeConversion tc;

//==============================================================================

class AllTrackingBoxListener
  : public ibeo::common::sdk::DataContainerListener<Scan2202, DataTypeId::DataType_Scan2202>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2221, DataTypeId::DataType_ObjectList2221>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2805, DataTypeId::DataType_VehicleStateBasic2805>,
    public ibeo::common::sdk::DataContainerListener<LogMessageError6400, DataTypeId::DataType_LogError6400>,
    public ibeo::common::sdk::DataContainerListener<LogMessageWarning6410, DataTypeId::DataType_LogWarning6410>,
    public ibeo::common::sdk::DataContainerListener<LogMessageNote6420, DataTypeId::DataType_LogNote6420>,
    public ibeo::common::sdk::DataContainerListener<LogMessageDebug6430, DataTypeId::DataType_LogDebug6430>
{
public:
    virtual ~AllTrackingBoxListener() {}

public:
    //========================================
    void onData(const Scan2202& scan) override
    {
        LOGINFO(appLogger,
                "Scan received: # " << scan.getScanNumber()
                                    << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
    }

    //========================================
    void onData(const ObjectList2221& objList) override
    {
        LOGINFO(appLogger, "Objects 2221 container received: # " << objList.getNbOfObjects());
    }

    //========================================
    void onData(const VehicleState2805& vs) override
    {
        LOGINFO(appLogger, "VS for Scan #: " << vs.getScanNumber() << "  " << tc.toString(vs.getTimestamp().toPtime()));
    }

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
}; // AllTrackingBoxListener

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
        std::cerr << "\tIP is the ip address of the LUX sensor, e.g. 192.168.0.1." << std::endl;
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
    AllTrackingBoxListener allListener;

    const uint16_t port = getPort(ip, 12002);
    IbeoTrackingBox trackingBox(ip, port);

    trackingBox.registerContainerListener(&allListener);

    trackingBox.getConnected();

    // Just to keep the program alive
    while (true)
    {
        if (!trackingBox.isConnected())
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
