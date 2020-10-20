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
//!\date March 11, 2015
//!
//!\example IbeoSdkCarriageWayListDemo.cpp
//! Demo project for reading IDC files and process the CarriageWayList.
//!\sa IbeoSdkFileDemo.cpp
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/lux.hpp>
#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/minilux.hpp>
#include <ibeo/common/sdk/scala.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayList.hpp>
#include <ibeo/common/sdk/devices/IdcFile.hpp>
#include <ibeo/common/sdk/LaneHandler.hpp>

#include <iostream>
#include <cstdlib>
#include <fstream>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkCarriageWayListDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void file_demo(const std::string& filename);

//==============================================================================

TimeConversion tc;

//==============================================================================

class AllListener
  : public ibeo::common::sdk::DataContainerListener<ObjectList, DataTypeId::DataType_ObjectList2221>,
    public ibeo::common::sdk::DataContainerListener<ObjectList, DataTypeId::DataType_ObjectList2225>,
    public ibeo::common::sdk::DataContainerListener<ObjectList, DataTypeId::DataType_ObjectList2271>,
    public ibeo::common::sdk::DataContainerListener<ObjectList, DataTypeId::DataType_ObjectList2280>,
    public ibeo::common::sdk::DataContainerListener<ObjectList, DataTypeId::DataType_ObjectList2281>,
    public ibeo::common::sdk::DataContainerListener<ObjectList, DataTypeId::DataType_ObjectList2290>,
    public ibeo::common::sdk::DataContainerListener<ObjectList, DataTypeId::DataType_ObjectList2291>,
    public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2805>,
    public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2806>,
    public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2807>,
    public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2808>,
    public ibeo::common::sdk::DataContainerListener<CarriageWayList, DataTypeId::DataType_CarriageWayList6970>,
    public ibeo::common::sdk::DataContainerListener<CarriageWayList, DataTypeId::DataType_CarriageWayList6972>
{
public:
    AllListener()
      : m_bufferedVehicleState(),
        m_bufferedObjectList(),
        m_hasBufferedVehicleState(false),
        m_hasBufferedObjectList(false)
    {}

    virtual ~AllListener() = default;

public:
    //========================================
    void onData(const ObjectList& objList) override
    {
        m_bufferedObjectList    = objList;
        m_hasBufferedObjectList = true;
    }

    //========================================
    void onData(const VehicleState& vs) override
    {
        m_bufferedVehicleState    = vs;
        m_hasBufferedVehicleState = true;
    }

    //========================================
    void onData(const CarriageWayList& cwl) override
    {
        std::string tab = "        ";

        // wait until a valid vehicle state and an object list are available
        if (m_hasBufferedVehicleState)
        {
            CarriageWayList::CarriageWays list = cwl.getCarriageWays();
            const lanes::LaneHandler lh(list);

            // compute ego position in lane
            lanes::LaneHandler::LanePosition egoPosition = lh.getLanePosition(m_bufferedVehicleState);

            // check if valid lane segment was found
            if (egoPosition.laneSegment)
            {
                LOGINFO(appLogger,
                        "Ego lateral offset is: " << std::setprecision(2) << egoPosition.lateralDistance << " m");

                if (m_hasBufferedObjectList)
                {
                    // compute object distances
                    for (const Object& obj : m_bufferedObjectList.getObjects())
                    {
                        // create transformation matrix of object relative to ego vehicle
                        Vector2<float> objectReferencePoint = convertRefPoint(obj.getReferencePointCoord(),
                                                                              obj.getCourseAngle(),
                                                                              obj.getObjectBoxSize(),
                                                                              obj.getReferencePointLocation(),
                                                                              RefPointBoxLocation::RearCenter);

                        TransformationMatrix2d<float> objSystem(obj.getCourseAngle(), objectReferencePoint);
                        bool inside_ego, success;

                        std::vector<Measurement> mml = obj.getMeasurementList().getMeasurements();
                        float latDis                 = 0.0F;
                        bool inside_egoLane          = false;

                        // extract Oela information stored in Objects
                        for (const Measurement& measurement : mml)
                        {
                            if (measurement.getKey() == MeasurementKey::Oela_LateralEgoLaneDistance)
                                latDis = measurement.getData<float>();
                            else if (measurement.getKey() == MeasurementKey::Oela_EgoLaneFlag)
                                inside_egoLane = measurement.getData<bool>();
                        } // for itmm

                        lanes::LaneHandler::LanePosition objPosition
                            = lh.getReferenceLanePosition(egoPosition, objSystem, inside_ego, success);

                        if (success)
                        {
                            LOGINFO(appLogger,
                                    "Object " << obj.getObjectId() << ": "
                                              << "\n"
                                              << tab << "lateral lane distance:      " << std::fixed
                                              << std::setprecision(2) << objPosition.lateralDistance << " m"
                                              << "\n"
                                              << tab << "longitudinal lane distance: " << std::fixed
                                              << std::setprecision(2) << objPosition.longitudinalDistance << " m"
                                              << "\n"
                                              << tab << "orientation in lane:        " << std::fixed
                                              << std::setprecision(2)
                                              << objPosition.transformationMatrix.getRotationMatrix().getAngle()
                                                     / static_cast<float>(M_PI) * 180.0F
                                              << " deg"
                                              << "\n"
                                              << tab << "inside ego vehicle lane:    " << inside_ego << "\n"
                                              << "\n"
                                              << tab << "lateral lane distance (stored): " << std::fixed
                                              << std::setprecision(2) << latDis << " m"
                                              << "\n"
                                              << tab << "inside ego vehicle lane (stored): " << std::fixed
                                              << std::setprecision(2) << inside_egoLane);
                        } // if success
                    } // for all ref objects
                } // if obj list has been initialized
            } // if valid lane segment was found
        } // if valid vehicle state and an object list are available
    }

protected:
    VehicleState m_bufferedVehicleState;
    ObjectList m_bufferedObjectList;

    bool m_hasBufferedVehicleState;
    bool m_hasBufferedObjectList;
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

    ibeo::common::logging::LogManager::getInstance().setDefaultLogLevel("Info");

    if (hasLogFile)
    {
        LOGINFO(appLogger,
                argv[0] << " (" << appName << ")"
                        << " using IbeoSDK " << ibeoSdk.getVersion().toString());
    }

    file_demo(filename);

    exit(0);
}

//==============================================================================

void file_demo(const std::string& filename)
{
    IdcFile file;
    file.open(filename);
    if (file.isOpen())
    {
        AllListener allListener;

        file.registerContainerListener(&allListener);

        unsigned short nbMessages = 0; // # of messages we parsed

        while (file.isGood())
        {
            const IdcFile::ContainerImporterPairs p = file.getNextDataContainer();
            file.notifyContainerListeners(p);
            ++nbMessages;
        } // while file is good

        LOGTRACE(appLogger, "EOF reached. " << nbMessages << " known blocks found.");
    } // if file is open
    else
    {
        LOGERROR(appLogger, "File not readable.");
    }
}

//==============================================================================
