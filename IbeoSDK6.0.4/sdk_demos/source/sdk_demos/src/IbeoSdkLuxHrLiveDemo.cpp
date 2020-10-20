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
//!\date Jul 30, 2015
//!
//!\example IbeoSdkLuxHrLiveDemo.cpp Demo project for connecting to a LuxHr and process the received
//!data containers.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/frameendseparator/FrameEndSeparator1100.hpp>
#include <ibeo/common/sdk/luxhr.hpp>
#include <ibeo/common/sdk/IpHelper.hpp>

#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkLuxHrLiveDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void live_demo(std::string ip);

//==============================================================================

TimeConversion tc;

//==============================================================================

class AllLuxHrListener
  : public ibeo::common::sdk::DataContainerListener<FrameEndSeparator1100, DataTypeId::DataType_FrameEndSeparator1100>,
    public ibeo::common::sdk::DataContainerListener<Scan2208, DataTypeId::DataType_Scan2208>
{
public:
    virtual ~AllLuxHrListener() {}

public:
    //========================================
    void onData(const FrameEndSeparator1100& fes) override
    {
        LOGINFO(appLogger, "Frame received: # " << fes.getFrameId());
    }

    //========================================
    void onData(const Scan2208& scan) override
    {
        LOGINFO(appLogger,
                "Scan received: # " << scan.getScanNumber() << "  time: "
                                    << tc.toString(scan.getSubScans().at(0).getStartScanTimestamp().toPtime(), 3)
                                    << ibeo::common::logging::endl
                                    << "ScStartTs: " << scan.getSubScans().at(0).getStartScanTimestamp().toPtime()
                                    << ibeo::common::logging::endl
                                    << "ScRevTs: " << boost::posix_time::microsec_clock::local_time());
    }
}; // AllLuxHrListener

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
        std::cerr << "\tIP is the ip address of the Ibeo LuxHr, e.g. 192.168.0.1." << std::endl;
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
    AllLuxHrListener allLuxHrListener;

    const uint16_t port = getPort(ip, 12008);
    IbeoLuxHr luxHr(ip, port);

    luxHr.registerContainerListener(&allLuxHrListener);

    luxHr.connect();

    // Just to keep the program alive
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

//			LOGERROR(appLogger, "Current time: " << Time::localTime());
//			CommandMiniLuxSetNtpTimestampSync timeSync(NTPTime(Time::localTime()));
//			ReplyMiniLuxSetNTPTimestampSync syncReply;
//			luxHr.sendCommand(timeSync, syncReply);
#endif // _WIN32
    }
}

//==============================================================================
