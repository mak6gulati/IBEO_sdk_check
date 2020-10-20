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
//!\example IbeoSdkMiniLuxLiveDemo.cpp Demo project for connecting to a MiniLux and process the received
//! data containers.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/minilux.hpp>
#include <ibeo/common/sdk/IpHelper.hpp>

#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/miniluxcommands.hpp>
#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkMiniLuxLiveDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void live_demo(std::string ip);

//==============================================================================

TimeConversion tc;

//==============================================================================

class AllMiniLuxListener
  : public ibeo::common::sdk::DataContainerListener<FrameEndSeparator1100, DataTypeId::DataType_FrameEndSeparator1100>,
    public ibeo::common::sdk::DataContainerListener<Scan2208, DataTypeId::DataType_Scan2208>
{
public:
    virtual ~AllMiniLuxListener() {}

public:
    //========================================
    void onData(const FrameEndSeparator1100& fes) override
    {
        LOGINFO(appLogger, "Frame received: # " << fes.getFrameId());
    }

    //========================================
    void onData(const Scan2208& scan) override
    {
        std::stringstream logStream;

        logStream << "Scan received: # " << scan.getScanNumber()
                  << "  time: " << tc.toString(scan.getSubScans().at(0).getStartScanTimestamp().toPtime(), 3)
                  << std::endl
                  << "ScStartTs: " << scan.getSubScans().at(0).getStartScanTimestamp().toPtime() << std::endl
                  << "ScRevTs: " << boost::posix_time::microsec_clock::local_time() << std::endl;

        LOGINFO(appLogger, logStream.str());
    }
}; // AllMiniLuxListener

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
        std::cerr << "\tIP is the ip address of the Ibeo MiniLux, e.g. 192.168.0.1." << std::endl;
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
    AllMiniLuxListener allMiniLuxListener;

    const uint16_t port = getPort(ip, 12006);
    IbeoMiniLux miniLux(ip, port);

    miniLux.registerContainerListener(&allMiniLuxListener);

    miniLux.connect();

    // Just to keep the program alive
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

//			CommandMiniLuxReset resetCmd;

//			CommandMiniLuxGetStatusC getStatus;
//			CommandMiniLuxGetStatus2010Exporter2010 getStatusExporter;
//			ReplyMiniLuxGetStatus replyStatus;
//			miniLux.sendCommand(getStatus, getStatusExporter, replyStatus);
//			LOGERROR(appLogger, "Status: " << replyStatus.toString());
//
//			CommandMiniLuxGetParameterC getParam(ParameterIndex(0x1200));
//			CommandMiniLuxGetParameter2010Exporter2010 getParamExporter;
//			ReplyMiniLuxGetParameter replyParam;
//			miniLux.sendCommand(getParam, getParamExporter, replyParam);
//			LOGERROR(appLogger, "SENSORMOUNTING_X: " << int16_t(replyParam.getParameterData()));
//
//			CommandMiniLuxSetParameterC setParam(ParameterIndex(0x1200), ParameterData(1500));
//			CommandMiniLuxSetParameter2010Exporter2010 setParamExporter;
//			ReplyMiniLuxSetParameter replySetParam;
//			miniLux.sendCommand(setParam, setParamExporter, replySetParam);
//
//			miniLux.sendCommand(getParam, getParamExporter, replyParam);
//			LOGERROR(appLogger, "SENSORMOUNTING_X: " << int16_t(replyParam.getParameterData()));
//			LOGERROR(appLogger, "========================================================");
//			LOGERROR(appLogger, "Current time: " << Time::localTime());
//			CommandMiniLuxSetNtpTimestampSyncC timeSync(NTPTime(Time::localTime()));
//			CommandMiniLuxSetNtpTimestampSync2010Exporter2010 exporter;
//			ReplyMiniLuxSetNTPTimestampSync syncReply;
//			miniLux.sendCommand(timeSync, exporter, syncReply);
#endif // _WIN32
    }
}

//==============================================================================
