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
//!\date Jun 1, 2012
//!
//! Demo project for connecting to an ECU and process the received
//! data containers.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/IpHelper.hpp>

#include <ibeo/common/sdk/datablocks/commands/ecucommands/ecucommands.hpp>
#include <ibeo/common/sdk/datablocks/commands/luxcommands/luxcommands.hpp>

#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/listener/DataListener.hpp>

#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkEcuLiveDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void live_demo(std::string ip);

//==============================================================================

TimeConversion tc;

//==============================================================================

class AllEcuListener
  : public ibeo::common::sdk::DataContainerListener<FrameEndSeparator1100, DataTypeId::DataType_FrameEndSeparator1100>,
    public ibeo::common::sdk::DataContainerListener<CanMessage1002, DataTypeId::DataType_CanMessage1002>,
    public ibeo::common::sdk::DataContainerListener<Scan2202, DataTypeId::DataType_Scan2202>,
    public ibeo::common::sdk::DataContainerListener<Scan2205, DataTypeId::DataType_Scan2205>,
    public ibeo::common::sdk::DataContainerListener<Scan, DataTypeId::DataType_Scan2205>,
    public ibeo::common::sdk::DataContainerListener<Scan2209, DataTypeId::DataType_Scan2209>,
    public ibeo::common::sdk::DataContainerListener<Scan, DataTypeId::DataType_Scan2209>,
    public ibeo::common::sdk::DataContainerListener<Scan2208, DataTypeId::DataType_Scan2208>,
    public ibeo::common::sdk::DataContainerListener<Scan2208, DataTypeId::DataType_Scan2310>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2225, DataTypeId::DataType_ObjectList2225>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2280, DataTypeId::DataType_ObjectList2280>,
    public ibeo::common::sdk::DataContainerListener<Image2403, DataTypeId::DataType_Image2403>,
    public ibeo::common::sdk::DataContainerListener<PositionWgs84_2604, DataTypeId::DataType_PositionWgs84_2604>,
    public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2805>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2805, DataTypeId::DataType_VehicleStateBasic2805>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2806, DataTypeId::DataType_VehicleStateBasic2806>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2807, DataTypeId::DataType_VehicleStateBasic2807>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2808, DataTypeId::DataType_VehicleStateBasic2808>,
    public ibeo::common::sdk::DataContainerListener<MeasurementList2821, DataTypeId::DataType_MeasurementList2821>,
    public ibeo::common::sdk::DataContainerListener<DeviceStatus6301, DataTypeId::DataType_DeviceStatus6301>,
    public ibeo::common::sdk::DataContainerListener<DeviceStatus6303, DataTypeId::DataType_DeviceStatus6303>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandEcuAppBaseCtrlC>,
    public ibeo::common::sdk::DataContainerListener<LogMessageError6400, DataTypeId::DataType_LogError6400>,
    public ibeo::common::sdk::DataContainerListener<LogMessageWarning6410, DataTypeId::DataType_LogWarning6410>,
    public ibeo::common::sdk::DataContainerListener<LogMessageNote6420, DataTypeId::DataType_LogNote6420>,
    public ibeo::common::sdk::DataContainerListener<LogMessageDebug6430, DataTypeId::DataType_LogDebug6430>
{
public:
    AllEcuListener()
      : ibeo::common::sdk::
            DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandEcuAppBaseCtrlC>()
    {}

    virtual ~AllEcuListener() {}

public:
    //========================================
    void onData(const FrameEndSeparator1100& fesc) override
    {
        LOGINFO(appLogger, "Received FrameEndeSeparator1100 " << static_cast<const void*>(&fesc));
    }

    //========================================
    void onData(const CanMessage1002& canMsg) override
    {
        LOGINFO(appLogger, "************Received CanMessage1002 " << static_cast<const void*>(&canMsg));
    }

    //========================================
    void onData(const CommandEcuAppBaseCtrlC*) override
    {
        LOGINFO(appLogger, "************Received CommandEcuAppBaseCtrlC ");
    }

    //========================================
    virtual void onData(const Scan& scan) override
    {
        LOGINFO(appLogger,
                "Scan received: # " << scan.getScanNumber()
                                    << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
    }

    //========================================
    virtual void onData(const Scan2202& scan) override
    {
        LOGINFO(appLogger,
                "Scan received: # " << scan.getScanNumber()
                                    << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
    }

    //========================================
    virtual void onData(const Scan2205& scan) override
    {
        LOGINFO(appLogger,
                "Scan received: # " << scan.getScanNumber()
                                    << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
    }

    //========================================
    virtual void onData(const Scan2208& scan) override
    {
        LOGINFO(appLogger, "Scan received: # " << scan.getScanNumber());
    }

    //========================================
    virtual void onData(const Scan2209& scan) override
    {
        LOGINFO(appLogger,
                "Scan received: # " << scan.getScanNumber()
                                    << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
    }

    //========================================
    virtual void onData(const ObjectList2225& objList) override
    {
        LOGINFO(appLogger, "Objects received: # " << objList.getNbOfObjects());
    }

    //========================================
    virtual void onData(const ObjectList2280& objList) override
    {
        LOGINFO(appLogger, "ET Objects container received: # " << objList.getNbOfObjects());
    }

    //========================================
    virtual void onData(const Image2403& image) override
    {
        LOGINFO(appLogger, "Image2403 received: time: " << tc.toString(image.getTimestamp().toPtime()));
    }

    //========================================
    void onData(const PositionWgs84_2604& wgs84) override
    {
        LOGINFO(appLogger,
                std::setw(5) << "PositionWGS84 container received: time: "
                             << tc.toString(wgs84.getPosition().getTimestamp().toPtime()));
    }

    //========================================
    void onData(const VehicleState& vs) override
    {
        LOGINFO(appLogger, "Received VehicleState " << static_cast<const void*>(&vs));
    }

    //========================================
    virtual void onData(const VehicleState2805& vs) override
    {
        LOGINFO(appLogger, "************** VS (0x2805) " << tc.toString(vs.getTimestamp().toPtime(), 3));
    }

    //========================================
    virtual void onData(const VehicleState2806& vs) override
    {
        LOGINFO(appLogger, "VS (0x2806) " << tc.toString(vs.getTimestamp().toPtime(), 3));
    }

    //========================================
    virtual void onData(const VehicleState2807& vs) override
    {
        LOGINFO(appLogger, "VS container 0x2807 " << tc.toString(vs.getTimestamp().toPtime(), 3));
    }

    //========================================
    virtual void onData(const VehicleState2808& vs) override
    {
        LOGINFO(appLogger, "VS container 0x2808 " << tc.toString(vs.getTimestamp().toPtime(), 3));
    }

    //========================================
    void onData(const MeasurementList2821& ml) override
    {
        LOGINFO(appLogger,
                std::setw(5) << "MeasurementList Conainer received: time: " << tc.toString(ml.getTimestamp().toPtime())
                             << " LN: '" << ml.getListName() << "' GN: '" << ml.getGroupName() << "'");
    }

    //========================================
    virtual void onData(const DeviceStatus6301&) override
    {
        LOGINFO(appLogger, std::setw(5) << "DevStat 6301 container received");
    }

    //========================================
    virtual void onData(const DeviceStatus6303&) override
    {
        LOGINFO(appLogger, std::setw(5) << "DevStat 6303 container received");
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
}; // AllEcuListener

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
        std::cerr << "\tIP is the ip address of the Ibeo Ecu, e.g. 192.168.0.1." << std::endl;
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
    AllEcuListener allEcuListener;

    const uint16_t port = getPort(ip, 12002);
    IbeoEcu ecu(ip, port);

    // Let the device handle connection losses automatically.
    ecu.setReconnectMode(IbeoEcu::ReconnectMode::WaitForRemoteDevice);
    ecu.setReconnectTime(boost::posix_time::seconds(1));

    ecu.registerContainerListener(&allEcuListener);
    ecu.getConnected();

    // 	CommandManagerAppBaseStatus cmabs;
    // 	ReplyEcuAppBaseStatus cmabsr;
    // 	LOGINFO(appLogger, "     ==================== Status ======================");
    // 	ecu.sendCommand(cmabs, cmabsr, boost::posix_time::milliseconds(500));
    // 	LOGERROR(appLogger, "CommandManagerAppBaseStatusReply: " << cmabsr.getData().size() << "  '"<< cmabsr.getData() << "'");
    //
    // 	LOGINFO(appLogger, "==================== Start Recording =======================");
    // 	CommandEcuAppBaseCtrl cmabcStart(CommandEcuAppBaseCtrl::AppBaseCtrlId_StartRecording);
    // 	ReplyEcuAppBaseCtrl cmabcr;
    // 	ecu.sendCommand(cmabcStart, cmabcr, boost::posix_time::milliseconds(1500));
    // 	LOGERROR(appLogger, "CommandManagerAppBaseCtrlReply: " << toHex(cmabcr.getCommandId()) << "'");
    //
    // 	LOGINFO(appLogger, "     ==================== Status ======================");
    // 	ecu.sendCommand(cmabs, cmabsr, boost::posix_time::milliseconds(500));
    // 	LOGERROR(appLogger, "CommandManagerAppBaseStatusReply: " << cmabsr.getData().size() << "  '"<< cmabsr.getData() << "'");

#ifdef _WIN32
    ::Sleep(1);
#else // _WIN32
    sleep(1);
#endif // _WIN32
    // 	LOGINFO(appLogger, "==================== Stop Recording =======================");
    // 	CommandEcuAppBaseCtrl cmabcStop(CommandEcuAppBaseCtrl::AppBaseCtrlId_StopRecording);
    // 	ecu.sendCommand(cmabcStop, cmabcr, boost::posix_time::milliseconds(1500));
    // 	LOGERROR(appLogger, "CommandManagerAppBaseCtrlReply: " << toHex(cmabcr.getCommandId()) << "'");
    //
    // 	LOGINFO(appLogger, "     ==================== Status ======================");
    // 	ecu.sendCommand(cmabs, cmabsr, boost::posix_time::milliseconds(500));
    // 	LOGERROR(appLogger, "CommandManagerAppBaseStatusReply: " << cmabsr.getData().size() << "  '"<< cmabsr.getData() << "'");

    // Just to keep the program alive
    while (ecu.isRunning())
    {
#ifdef _WIN32
        ::Sleep(1);
#else // _WIN32
        sleep(1);
#endif // _WIN32
    } // while
}

//==============================================================================
