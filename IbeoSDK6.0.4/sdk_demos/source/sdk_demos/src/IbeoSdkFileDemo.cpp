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
//!\example IbeoSdkFileDemo.cpp Demo project for reading IDC files and process the data containers.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/lux.hpp>
#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/minilux.hpp>
#include <ibeo/common/sdk/scala.hpp>

#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/devices/IdcFile.hpp>

#include <ibeo/common/sdk/datablocks/commands/ecucommands/ecucommands.hpp>
#include <ibeo/common/sdk/datablocks/commands/luxcommands/luxcommands.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/miniluxcommands.hpp>

#ifdef WITHJPEGSUPPORT
#    include <ibeosdk/jpegsupport/jmemio.h>
#endif // WITHJPEGSUPPORT

#ifdef WITHJPEGSUPPORTDEF
#    include <ibeosdk/jpegsupport/jmemio.h>
#endif

#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkFileDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void file_demo_container(const std::string& filename);

//==============================================================================

TimeConversion tc;

//==============================================================================

class AllListener
  : public ibeo::common::sdk::DataContainerListener<FrameEndSeparator1100, DataTypeId::DataType_FrameEndSeparator1100>,
    public ibeo::common::sdk::DataContainerListener<CanMessage1002, DataTypeId::DataType_CanMessage1002>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandEcuAppBaseCtrlC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandEcuAppBaseStatusC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandEcuSetFilterC>,

    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandLuxGetParameterC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandLuxGetStatusC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandLuxResetC>,
    public ibeo::common::sdk::DataContainerSpecialListener<Command2010,
                                                           DataTypeId::DataType_Command2010,
                                                           CommandLuxResetToDefaultParametersC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandLuxSaveConfigC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandLuxSetNtpTimestampSyncC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandLuxSetParameterC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandLuxStartMeasureC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandLuxStopMeasureC>,

    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandMiniLuxGetParameterC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandMiniLuxGetStatusC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandMiniLuxResetC>,
    public ibeo::common::sdk::DataContainerSpecialListener<Command2010,
                                                           DataTypeId::DataType_Command2010,
                                                           CommandMiniLuxResetToDefaultParametersC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandMiniLuxSaveConfigC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandMiniLuxSetNtpTimestampSyncC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandMiniLuxSetParameterC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandMiniLuxStartMeasureC>,
    public ibeo::common::sdk::
        DataContainerSpecialListener<Command2010, DataTypeId::DataType_Command2010, CommandMiniLuxStopMeasureC>,

    public ibeo::common::sdk::DataContainerListener<Command2010, DataTypeId::DataType_Command2010>,

    public ibeo::common::sdk::DataContainerListener<Scan2202, DataTypeId::DataType_Scan2202>,
    public ibeo::common::sdk::DataContainerListener<Scan2205, DataTypeId::DataType_Scan2205>,
    public ibeo::common::sdk::DataContainerListener<Scan2208, DataTypeId::DataType_Scan2208>,
    public ibeo::common::sdk::DataContainerListener<Scan2209, DataTypeId::DataType_Scan2209>,
    public ibeo::common::sdk::DataContainerListener<Scan2310, DataTypeId::DataType_Scan2310>,
    public ibeo::common::sdk::DataContainerListener<Scan, DataTypeId::DataType_Scan2202>,
    public ibeo::common::sdk::DataContainerListener<Scan, DataTypeId::DataType_Scan2205>,
    public ibeo::common::sdk::DataContainerListener<Scan, DataTypeId::DataType_Scan2208>,
    public ibeo::common::sdk::DataContainerListener<Scan, DataTypeId::DataType_Scan2209>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2221, DataTypeId::DataType_ObjectList2221>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2225, DataTypeId::DataType_ObjectList2225>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2270, DataTypeId::DataType_ObjectList2270>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2271, DataTypeId::DataType_ObjectList2271>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2280, DataTypeId::DataType_ObjectList2280>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2281, DataTypeId::DataType_ObjectList2281>,
    public ibeo::common::sdk::DataContainerListener<ObjectList2291, DataTypeId::DataType_ObjectList2291>,
    public ibeo::common::sdk::DataContainerListener<Image2403, DataTypeId::DataType_Image2403>,
    public ibeo::common::sdk::DataContainerListener<PositionWgs84_2604, DataTypeId::DataType_PositionWgs84_2604>,
    public ibeo::common::sdk::DataContainerListener<OGpsImuMessage2610, DataTypeId::DataType_OGpsImuMessage2610>,
    public ibeo::common::sdk::DataContainerListener<MeasurementList2821, DataTypeId::DataType_MeasurementList2821>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2805, DataTypeId::DataType_VehicleStateBasic2805>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2806, DataTypeId::DataType_VehicleStateBasic2806>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2807, DataTypeId::DataType_VehicleStateBasic2807>,
    public ibeo::common::sdk::DataContainerListener<VehicleState2808, DataTypeId::DataType_VehicleStateBasic2808>,
    public ibeo::common::sdk::DataContainerListener<ObjectAssociationList4001,
                                                    DataTypeId::DataType_ObjectAssociationList4001>,
    public ibeo::common::sdk::DataContainerListener<DeviceStatus6301, DataTypeId::DataType_DeviceStatus6301>,
    public ibeo::common::sdk::DataContainerListener<DeviceStatus6303, DataTypeId::DataType_DeviceStatus6303>,
    public ibeo::common::sdk::DataContainerListener<LogMessageError6400, DataTypeId::DataType_LogError6400>,
    public ibeo::common::sdk::DataContainerListener<LogMessageWarning6410, DataTypeId::DataType_LogWarning6410>,
    public ibeo::common::sdk::DataContainerListener<LogMessageNote6420, DataTypeId::DataType_LogNote6420>,
    public ibeo::common::sdk::DataContainerListener<LogMessageDebug6430, DataTypeId::DataType_LogDebug6430>,
    public ibeo::common::sdk::DataContainerListener<ObjectLabelList6503, DataTypeId::DataType_ObjectLabel6503>,
    public ibeo::common::sdk::DataContainerListener<PointCloud, DataTypeId::DataType_PointCloud7500>,
    public ibeo::common::sdk::DataContainerListener<PointCloud7500, DataTypeId::DataType_PointCloud7500>,
    public ibeo::common::sdk::DataContainerListener<PointCloud7510, DataTypeId::DataType_PointCloud7510>,
    public ibeo::common::sdk::DataContainerListener<TimeRecord9000, DataTypeId::DataType_TimeRecord9000>,
    public ibeo::common::sdk::DataContainerListener<Odometry9002, DataTypeId::DataType_Odometry9002>,
    public ibeo::common::sdk::DataContainerListener<GpsImu9001, DataTypeId::DataType_GpsImu9001>,
    public ibeo::common::sdk::DataContainerListener<SystemMonitoringCanStatus6700,
                                                    DataTypeId::DataType_SystemMonitoringCanStatus6700>,
    public ibeo::common::sdk::DataContainerListener<SystemMonitoringDeviceStatus6701,
                                                    DataTypeId::DataType_SystemMonitoringDeviceStatus6701>,
    public ibeo::common::sdk::DataContainerListener<SystemMonitoringSystemStatus6705,
                                                    DataTypeId::DataType_SystemMonitoringSystemStatus6705>,
    public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2805>
{
public:
    virtual ~AllListener() {}

public:
    //========================================
    void onData(const CommandEcuAppBaseCtrlC* const) override
    {
        LOGINFO(appLogger, "************Received CommandEcuAppBaseCtrlC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandEcuAppBaseStatusC* const) override
    {
        LOGINFO(appLogger, "***+++++++**Received CommandEcuAppBaseStatusC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandEcuSetFilterC* const) override
    {
        LOGINFO(appLogger, "***$$$$$$**Received CommandEcuSetFilterC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandLuxGetParameterC* const) override
    {
        LOGINFO(appLogger, "***######***Received CommandLuxGetParameterC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandLuxGetStatusC* const) override
    {
        LOGINFO(appLogger, "***??????***Received CommandLuxGetStatusC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandLuxResetC* const) override
    {
        LOGINFO(appLogger, "***!!!!!!***Received CommandLuxResetC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandLuxResetToDefaultParametersC* const) override
    {
        LOGINFO(appLogger, "***@@@@@@***Received CommandLuxResetToDefaultParametersC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandLuxSaveConfigC* const) override
    {
        LOGINFO(appLogger, "***~~~~~~**Received CommandLuxSaveConfigC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandLuxSetNtpTimestampSyncC* const) override
    {
        LOGINFO(appLogger, "***&&&&&&**Received CommandLuxSetNtpTimestampSyncC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandLuxSetParameterC* const) override
    {
        LOGINFO(appLogger, "***§§§§§§**Received CommandLuxSetParameterC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandLuxStartMeasureC* const) override
    {
        LOGINFO(appLogger, "***//////**Received CommandLuxStartMeasureC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandLuxStopMeasureC* const) override
    {
        LOGINFO(appLogger, "***''''''**Received CommandLuxStopMeasureC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandMiniLuxGetParameterC* const) override
    {
        LOGINFO(appLogger, "***######***Received CommandMiniLuxGetParameterC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandMiniLuxGetStatusC* const) override
    {
        LOGINFO(appLogger, "***??????***Received CommandMiniLuxGetStatusC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandMiniLuxResetC* const) override
    {
        LOGINFO(appLogger, "***!!!!!!***Received CommandMiniLuxResetC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandMiniLuxResetToDefaultParametersC* const) override
    {
        LOGINFO(appLogger, "***@@@@@@***Received CommandMiniLuxResetToDefaultParametersC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandMiniLuxSaveConfigC* const) override
    {
        LOGINFO(appLogger, "***~~~~~~**Received CommandMiniLuxSaveConfigC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandMiniLuxSetNtpTimestampSyncC* const) override
    {
        LOGINFO(appLogger, "***&&&&&&**Received CommandMiniLuxSetNtpTimestampSyncC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandMiniLuxSetParameterC* const) override
    {
        LOGINFO(appLogger, "***§§§§§§**Received CommandMiniLuxSetParameterC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandMiniLuxStartMeasureC* const) override
    {
        LOGINFO(appLogger, "***//////**Received CommandMiniLuxStartMeasureC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const CommandMiniLuxStopMeasureC* const) override
    {
        LOGINFO(appLogger, "***''''''**Received CommandMiniLuxStopMeasureC ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const Command2010&) override
    {
        LOGINFO(appLogger, ":):):):):)Received Command2010 ");
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const FrameEndSeparator1100& fes) override
    {
        LOGTRACE(appLogger, std::setw(5) << "Frame received: # " << fes.getFrameId());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const CanMessage1002& canMsg) override
    {
        LOGTRACE(appLogger, "Received CanMessage1002Container " << static_cast<const void*>(&canMsg));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    virtual void onData(const Scan& scan) override
    {
        LOGTRACE(appLogger,
                 "Scan container received: # " << scan.getScanNumber()
                                               << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    virtual void onData(const Scan2202& scan) override
    {
        LOGTRACE(appLogger,
                 "Scan container 0x2202: # " << scan.getScanNumber()
                                             << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    virtual void onData(const Scan2205& scan) override
    {
        LOGTRACE(appLogger,
                 "Scan container 0x2205 received: # "
                     << scan.getScanNumber() << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    virtual void onData(const Scan2208& scan) override
    {
        LOGTRACE(appLogger, "Scan container 0x2208 received " << scan.getScanNumber());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    virtual void onData(const Scan2209& scan) override
    {
        LOGTRACE(appLogger,
                 "Scan container 0x2209: # " << scan.getScanNumber()
                                             << "  time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
        LOGTRACE(appLogger, "========================================================");
    }

    //=======================================
    void onData(const Scan2310& scan) override
    {
        LOGTRACE(appLogger, "Scan container 0x2310: # " << scan.getHeader().getScanCounter());
        LOGTRACE(appLogger, std::setw(5) << "Scan 2310 Container received");
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const VehicleState& vs) override
    {
        LOGTRACE(appLogger, "Received VehicleState " << static_cast<const void*>(&vs));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const ObjectList2221& objList) override
    {
        LOGTRACE(appLogger, "ObjectList2221 received: # " << objList.getNbOfObjects());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const ObjectList2225& objList) override
    {
        LOGTRACE(appLogger, "ObjectList2225 received: # " << objList.getNbOfObjects());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const ObjectList2270& objList) override
    {
        LOGTRACE(appLogger, "ObjectList2270 contianer received: # " << objList.getNbOfObjects());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const ObjectList2271& objList) override
    {
        LOGTRACE(appLogger,
                 "ObjectList 2271 received. Scan: " << objList.getScanNumber()
                                                    << "  ObjLstId: " << int(objList.getObjectListId())
                                                    << "  #Obj:" << objList.getNbOfObjects());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    virtual void onData(const ObjectList2280& objList) override
    {
        LOGTRACE(appLogger, "ET Objects container received: # " << objList.getNbOfObjects());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const ObjectList2281& objList) override
    {
        LOGTRACE(appLogger,
                 "ObjectList2281 container received: # "
                     << objList.getNbOfObjects() << ibeo::common::logging::endl
                     << "  ObjListId: " << toHex(objList.getObjectListId())
                     << "  DevIntfVr: " << toHex(objList.getDeviceInterfaceVersion())
                     << "  ObjListId: " << toHex(int(objList.getDeviceType())));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const ObjectList2291& refObjList) override
    {
        LOGTRACE(appLogger,
                 "ObjectList2291 container received: # "
                     << refObjList.getNbOfObjects() << ibeo::common::logging::endl
                     << "  ObjListId: " << toHex(refObjList.getObjectListId())
                     << "  DevIntfVr: " << toHex(refObjList.getDeviceInterfaceVersion())
                     << "  ObjListId: " << toHex(refObjList.getDeviceType()));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const Image2403& image) override
    {
        LOGTRACE(appLogger, "Image2403 received: time: " << tc.toString(image.getTimestamp().toPtime()));

#ifdef WITHJPEGSUPPORT
        if ((image.getFormat() == Image2403::JPEG) || (image.getFormat() == Image2403::MJPEG))
        {
            const char* rawBuffer;
            unsigned int compressedSize;

            const bool ok = image.getImageBuffer(rawBuffer, compressedSize);

            if (!ok)
            {
                return;
            }

            const unsigned int rgbBufferSize = (unsigned int)(image.getWidth() * image.getHeight() * 3);
            unsigned char* rgbBuffer         = new unsigned char[size_t(rgbBufferSize)];

            unsigned int width  = 0;
            unsigned int height = 0;
            // fill rgbBuffer, width and height
            const int retCode = readJpegFromMemory(
                rgbBuffer, &width, &height, reinterpret_cast<const unsigned char*>(rawBuffer), compressedSize);

            LOGTRACE(appLogger, "ok: " << ok << " retCode: " << retCode << " Size: " << width << " x " << height);

            {
                unsigned int cprSize;
                unsigned char* cprBuffer = new unsigned char[rgbBufferSize];
                writeJpegToMemory(rgbBuffer, width, height, cprBuffer, rgbBufferSize, 100, &cprSize);

                FILE* f = fopen("jpeg.jpg", "wb");
                fwrite(cprBuffer, cprSize, 1, f);
                delete[] cprBuffer;
            }

            delete[] rgbBuffer;
        } // if image is JPEG or MJPEG
#endif // WITHJPEGSUPPORT
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const PositionWgs84_2604& wgs84) override
    {
        LOGTRACE(appLogger,
                 std::setw(5) << "PositionWGS84 container received: time: "
                              << tc.toString(wgs84.getPosition().getTimestamp().toPtime()));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const OGpsImuMessage2610&) override
    {
        LOGTRACE(appLogger, std::setw(5) << "OGpsImuMessage2610 container received");
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const VehicleState2805& vs) override
    {
        LOGTRACE(appLogger, "VS (LUX) received: time: " << tc.toString(vs.getTimestamp().toPtime()));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const VehicleState2806& vs) override
    {
        LOGTRACE(appLogger, "VS (ECU;old) received: time: " << tc.toString(vs.getTimestamp().toPtime()));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const VehicleState2807& vs) override
    {
        LOGTRACE(appLogger, "VS (0x2807) container received: time: " << tc.toString(vs.getTimestamp().toPtime()));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const VehicleState2808& vs) override
    {
        LOGTRACE(appLogger, "VS (0x2808) container received: time: " << tc.toString(vs.getTimestamp().toPtime()));
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const MeasurementList2821& ml) override
    {
        LOGTRACE(appLogger,
                 std::setw(5) << "MeasurementList Container received: time: "
                              << tc.toString(ml.getTimestamp().toPtime()) << " LN: '" << ml.getListName() << "' GN: '"
                              << ml.getGroupName() << "'"
                              << "Num: " << ml.getMeasList().getSize());

        using MLVector = std::vector<Measurement>;

        MLVector::const_iterator itMl = ml.getMeasList().getMeasurements().begin();
        int ctr                       = 0;
        for (; itMl != ml.getMeasList().getMeasurements().end(); ++itMl, ++ctr)
        {
            LOGTRACE(appLogger, " M" << ctr << ":" << (*itMl));
        }
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const ObjectAssociationList4001& oaList) override
    {
        LOGTRACE(appLogger,
                 "ObjectAssociationList4001 received"
                     << ibeo::common::logging::endl
                     << "  RObjListId: " << toHex(oaList.getRefObjListId())
                     << "  RDevIntfVr: " << toHex(oaList.getRefDevInterfaceVersion())
                     << "  DevType: " << toHex(oaList.getRefDevType()) << ibeo::common::logging::endl
                     << "  DObjListId: " << toHex(oaList.getDutObjListId()) << "  DDevIntfVr: "
                     << toHex(oaList.getDutDevInterfaceVersion()) << "  DevType: " << toHex(oaList.getDutDevType())
                     << "  # of associations: " << oaList.getObjectAssociations().size());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const DeviceStatus6301&) override
    {
        LOGTRACE(appLogger, "DevStat 0x6301 container received");
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const DeviceStatus6303&) override
    {
        LOGTRACE(appLogger, "DevStat 0x6303 container received");
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const LogMessageError6400& logMsg) override
    {
        LOGTRACE(appLogger,
                 "LogMessage (Error) received: time: " << int(logMsg.getTraceLevel()) << ": " << logMsg.getMessage());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const LogMessageWarning6410& logMsg) override
    {
        LOGTRACE(appLogger,
                 "LogMessage (Warning) received: time: " << int(logMsg.getTraceLevel()) << ": " << logMsg.getMessage());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const LogMessageNote6420& logMsg) override
    {
        LOGTRACE(appLogger,
                 "LogMessage (Note) received: time: " << int(logMsg.getTraceLevel()) << ": " << logMsg.getMessage());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const LogMessageDebug6430& logMsg) override
    {
        LOGTRACE(appLogger,
                 "LogMessage (Debug) received: time: " << int(logMsg.getTraceLevel()) << ": " << logMsg.getMessage());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const ObjectLabelList6503& oll) override
    {
        LOGTRACE(appLogger, std::setw(5) << " #Labels: " << oll.getLabels().size() << "   ");
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const PointCloud& pcl) override
    {
        LOGTRACE(appLogger,
                 "PointCloud received. Is empty: " << pcl.getPoints().empty() << "  ReferencePlane at position: "
                                                   << pcl.getReferencePlane().getGpsPoint().getLatitudeInDeg() << "  "
                                                   << pcl.getReferencePlane().getGpsPoint().getLongitudeInDeg());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const PointCloud7500& pcl) override
    {
        LOGTRACE(appLogger,
                 "PointCloud7500 received. Is empty: " << pcl.getPoints().empty() << "  ReferencePlane at position: "
                                                       << pcl.getReferencePlane().getGpsPoint().getLatitudeInDeg()
                                                       << "  "
                                                       << pcl.getReferencePlane().getGpsPoint().getLongitudeInDeg());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const PointCloud7510& pcl) override
    {
        LOGTRACE(appLogger,
                 "PointCloud7510 received. Is empty: " << pcl.getPoints().empty() << "  ReferencePlane at position: "
                                                       << pcl.getReferencePlane().getGpsPoint().getLatitudeInDeg()
                                                       << "  "
                                                       << pcl.getReferencePlane().getGpsPoint().getLongitudeInDeg());
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const TimeRecord9000& tim) override
    {
        LOGTRACE(appLogger,
                 "Internal Clock Times Received with size: " << tim.getInternalClockTimes().size()
                                                             << "External Clock Times Received with size: "
                                                             << tim.getExternalClockTimes().size());
        LOGTRACE(appLogger, "========================================================");
    }
    //========================================
    void onData(const Odometry9002& odo) override
    {
        LOGTRACE(appLogger, "Steering angle: " << odo.getSteeringAngle());
        LOGTRACE(appLogger, "========================================================");
    }
    //========================================
    void onData(const GpsImu9001& gpsImu) override
    {
        LOGTRACE(appLogger,
                 "GpsImu9001 received: time: " << tc.toString(gpsImu.getTimestamp().getReceivedTimeEcu().toPtime())
                                               << " "
                                               << "Source: " << GpsImu::toString(gpsImu.getSource()) << "  ");
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const SystemMonitoringCanStatus6700& canStatus) override
    {
        LOGTRACE(appLogger, "SystemMonitoringCANStatus6700 received: " << canStatus.toString() << "  ");
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const SystemMonitoringDeviceStatus6701& deviceStatus) override
    {
        LOGTRACE(appLogger, "SystemMonitoringDeviceStatus6701 received: " << deviceStatus.toString() << "  ");
        LOGTRACE(appLogger, "========================================================");
    }

    //========================================
    void onData(const SystemMonitoringSystemStatus6705& systemStatus) override
    {
        LOGTRACE(appLogger, "SystemMonitoringSystemStatus6705 received: " << systemStatus.toString() << "  ");
        LOGTRACE(appLogger, "========================================================");
    }
}; // AllListener

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
        std::cerr << "\tINPUTFILENAME Name of the file to use as input instead of a sensor." << std::endl;
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

    file_demo_container(filename);

    exit(0);
}

//==============================================================================

void file_demo_container(const std::string& filename)
{
    IdcFile file;
    file.open(filename);
    if (file.isOpen())
    {
        AllListener allListener;

        file.registerContainerListener(&allListener);

        uint32_t nbMessages = 0; // # of messages we parsed

        while (file.isGood())
        {
            const IdcFile::ContainerImporterPairs p = file.getNextDataContainer();
            //			for (auto p1: p) {
            //				LOGINFO(appLogger, toHex(p1.second->getDataType()));
            //			}

            file.notifyContainerListeners(p);
            ++nbMessages;
        }

        LOGDEBUG(appLogger, "EOF reached. " << nbMessages << " known blocks found.");
    }
    else
    {
        LOGERROR(appLogger, "File not readable.");
    }
}

//==============================================================================
