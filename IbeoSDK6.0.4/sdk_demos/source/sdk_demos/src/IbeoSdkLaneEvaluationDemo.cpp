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
//!\date Aug 03, 2015
//!
//!\example IbeoSdkLaneEvaluationDemo.cpp Demo project for evaluating a DUT producing Lanes
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/lux.hpp>
#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/minilux.hpp>
#include <ibeo/common/sdk/scala.hpp>

#include <ibeo/common/sdk/devices/IdcFile.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayList.hpp>
#include <ibeo/common/sdk/LaneHandler.hpp>

#include <iostream>
#include <limits>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

#ifdef _WIN32
#    if _MSC_VER < 1800 //VS 2013 is not tested 1900 == VS 2015
float roundf(const float v) { return v < 0.0 ? ceil(v - 0.5F) : floor(v + 0.5F); }
#    endif // before VS 2013
#endif // _WIN32

//==============================================================================

const std::string appName = "IbeoSdkLaneEvaluationDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void file_evaluation(const std::string& dutFilename, const std::string& refFileName);

//==============================================================================

TimeConversion tc;

//==============================================================================
class LaneFrameStatistic
{
public:
    float m_maxErrorRight; // indication for error bars
    float m_maxErrorLeft;
    float m_rightLanePositionRef; // reference LanePosition
    float m_leftLanePositionRef;
    float m_rightLanePosition; //estimated LanePosition
    float m_leftLanePosition;
}; // LaneFrameStatistic
//==============================================================================

class LaneEvaluation
{
public:
    LaneEvaluation() {}
    virtual ~LaneEvaluation();

public:
    void
    process(const VehicleState& vs, const CarriageWayList::CarriageWays& cw, const LogPolygonList2dFloat6817& lane);

private:
    void print(const Vector2<float>& sp, const bool inLane, const float dist);

    //return lateral distance to lane // NAN if supportPoint is outside LaneWindow
    float checkSupportLaneSupportPoint(const Vector2<float>& vehCoords,
                                       const lanes::LaneHandler::LanePosition& egoLane,
                                       bool& inLane);

    float calcDistanceToLaneBoundary(const Vector2<float>& vehCoords,
                                     const lanes::LaneHandler::LanePosition& egoLane,
                                     bool left = true);

    void incCounter(const float dist, uint16_t& match, uint16_t& missMatch, const bool inLane);

private:
    static const float maximalLateralEvalDistance;

private:
    lanes::LaneHandler* m_currenLaneHandler{nullptr};

    uint32_t m_totalLanesExpected{0};
    uint32_t m_totalLanesMeasured{0}; // measured Lanes Left/right within search window

    std::vector<LaneFrameStatistic> m_frameStatistics{};

    std::ofstream m_evalFile;

    std::ofstream m_falseNegativeLeft; //files for explicit eval
    std::ofstream m_falseNegativeRight;
    std::ofstream m_falseNegativeBoth;

    uint32_t m_frameCounter{0};
}; // LaneEvaluation

//==============================================================================

const float LaneEvaluation::maximalLateralEvalDistance = 0.35F;

//==============================================================================
//==============================================================================
//==============================================================================

LaneEvaluation::~LaneEvaluation()
{
    // TODO Auto-generated destructor stub
    const float detectionRate = float(m_totalLanesMeasured) / float(m_totalLanesExpected);
    LOGINFO(appLogger, " DetectionRate" << detectionRate);

    m_evalFile.open("LaneEvalResult.csv", std::ofstream::out | std::ofstream::app);
    m_evalFile << detectionRate << std::endl;

    std::vector<LaneFrameStatistic>::const_iterator it = m_frameStatistics.begin();
    for (; it != m_frameStatistics.end(); ++it)
    {
        m_evalFile << it->m_leftLanePosition << ";" << it->m_leftLanePositionRef << ";" << it->m_maxErrorLeft << ";"
                   << it->m_rightLanePosition << ";" << it->m_rightLanePositionRef << ";" << it->m_maxErrorRight
                   << std::endl;
    }

    m_evalFile.close();
}
//==============================================================================

void LaneEvaluation::process(const VehicleState& vs,
                             const CarriageWayList::CarriageWays& cw,
                             const LogPolygonList2dFloat6817& lane)
{
    LOGINFO(appLogger, " start LaneEvaluationProcessing");
    using namespace lanes;

    LaneHandler lh(cw);
    m_currenLaneHandler                    = &lh;
    LaneHandler::LanePosition vehCoordsRef = lh.getLanePosition(vs);

    //increment TPs
    bool currentLeft  = false; // left lane is measured and available
    bool currentRight = false; // right lane is measured and available

    LogPolygonList2dFloat6817::const_iterator leftLaneB  = lane.getLogList().end();
    LogPolygonList2dFloat6817::const_iterator rightLaneB = lane.getLogList().end();
    float minDistLeft                                    = std::numeric_limits<float>::max();
    float minDistRight                                   = std::numeric_limits<float>::max();

    LogPolygonList2dFloat6817::const_iterator it = lane.getLogList().begin();
    for (; it != lane.getLogList().end(); ++it)
    {
        uint16_t foundMatch     = 0;
        uint16_t foundMissMatch = 0;

        Polygon2d<float>::const_iterator ot = it->getPoly().begin();
        for (; ot != it->getPoly().end(); ++ot)
        {
            bool inLane = false;

            const float dist = checkSupportLaneSupportPoint(*ot, vehCoordsRef, inLane);
            incCounter(dist, foundMatch, foundMissMatch, inLane);
            //			print(*ot,inLane,dist); //debug Output
        }

        bool middleInLane;
        const Vector2<float>& middleLaneP = it->getPoly().at(1);
        float middlePointDist             = checkSupportLaneSupportPoint(middleLaneP, vehCoordsRef, middleInLane);
        if (middleLaneP.getY() > 0.0F)
        {
            if (minDistLeft > middlePointDist)
            {
                minDistLeft = middlePointDist;
                leftLaneB   = it;
            }
        }
        else
        {
            if (minDistRight > middlePointDist)
            {
                minDistRight = middlePointDist;
                rightLaneB   = it;
            }
        }

        if (foundMatch >= 2)
        {
            if ((it->getPoly().begin()->getY() > 0.0F))
            {
                currentLeft = true;
            }
            else
            {
                currentRight = true;
            }
        }

    } // for
    if ((leftLaneB != lane.getLogList().end()) && (rightLaneB != lane.getLogList().end()))
    {
        LaneFrameStatistic stat;
        stat.m_leftLanePositionRef
            = calcDistanceToLaneBoundary(Vector2<float>(leftLaneB->getPoly().at(1).getX(), 0.0F), vehCoordsRef, true);
        stat.m_rightLanePositionRef
            = calcDistanceToLaneBoundary(Vector2<float>(rightLaneB->getPoly().at(1).getX(), 0.0F), vehCoordsRef, false);
        stat.m_maxErrorLeft      = minDistLeft;
        stat.m_maxErrorRight     = minDistRight;
        stat.m_leftLanePosition  = leftLaneB->getPoly().at(1).getY();
        stat.m_rightLanePosition = rightLaneB->getPoly().at(1).getY();

        m_frameStatistics.push_back(stat);
    }

    m_totalLanesMeasured = (currentLeft) ? m_totalLanesMeasured + 1 : m_totalLanesMeasured;
    m_totalLanesMeasured = (currentRight) ? m_totalLanesMeasured + 1 : m_totalLanesMeasured;
    m_totalLanesExpected += 2;

    ++m_frameCounter;
}

//==============================================================================

float LaneEvaluation::checkSupportLaneSupportPoint(const Vector2<float>& vehCoords,
                                                   const lanes::LaneHandler::LanePosition& egoLane,
                                                   bool& inLane)
{
    using namespace lanes;
    bool succ;
    //	{
    //		LOGINFO(appLogger, "EgoLane Distance " << egoLane.longitudinalDistance << "/" << egoLane.lateralDistance << ".");
    //	}

    float latDist = NaN;
    TransformationMatrix2d<float> goalMatrix(vehCoords);

    LaneHandler::LanePosition lp = m_currenLaneHandler->getReferenceLanePosition(egoLane, goalMatrix, inLane, succ);

    if (succ)
    {
        const float width = egoLane.laneSegment->getWidth(vehCoords.getX());
        const float delta = fabsf(fabsf(lp.lateralDistance) - (width * 0.5F));

        latDist = delta;
    }
    else
    {
        latDist = -1.0F;
    }

    return latDist;
}

//==============================================================================
//!\brief This function calculates the distance to the reference lane Boundary.
//!
//! As default it calculates the distance to the left lane boundary.
//! If left=false the distance to the right lane boundary will be calculated.
//------------------------------------------------------------------------------
float LaneEvaluation::calcDistanceToLaneBoundary(const Vector2<float>& vehCoords,
                                                 const lanes::LaneHandler::LanePosition& egoLane,
                                                 bool left)
{
    using namespace lanes;

    float latDist = NaN;
    TransformationMatrix2d<float> goalMatrix(vehCoords);
    bool inLane, succ;
    LaneHandler::LanePosition lp = m_currenLaneHandler->getReferenceLanePosition(egoLane, goalMatrix, inLane, succ);

    if (succ)
    {
        const float width                = egoLane.laneSegment->getWidth(vehCoords.getX());
        const float centerToLaneBoundary = (left) ? (width * 0.5F) : -(width * 0.5F);
        const float delta                = -lp.lateralDistance + centerToLaneBoundary;
        latDist                          = delta;
    }

    return latDist;
}

//==============================================================================

void LaneEvaluation::incCounter(const float dist, uint16_t& match, uint16_t& missMatch, const bool inLane)
{
    if (dist <= maximalLateralEvalDistance)
        ++match;
    if (inLane && dist > maximalLateralEvalDistance)
        ++missMatch;
}

//==============================================================================

void LaneEvaluation::print(const Vector2<float>& sp, const bool /*inLane*/, const float dist)
{
    std::stringstream str;

    if (dist <= maximalLateralEvalDistance)
    {
        str << "dist:" << roundf(dist * 100.0F) / 100.0F << " SupportPoint:(" << sp.getX() << "/" << sp.getY() << ")";

        LOGINFO(appLogger, " Point is out of Evaluation distance" << str.str());
    }
}

//==============================================================================

class AllListener
  : public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2805>,
    public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2806>,
    public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2807>,
    public ibeo::common::sdk::DataContainerListener<VehicleState, DataTypeId::DataType_VehicleStateBasic2808>,
    public ibeo::common::sdk::DataContainerListener<LogPolygonList2dFloat6817,
                                                    DataTypeId::DataType_LogPolygonList2dFloat6817>,
    public ibeo::common::sdk::DataContainerListener<CarriageWayList, DataTypeId::DataType_CarriageWayList6970>,
    public ibeo::common::sdk::DataContainerListener<CarriageWayList, DataTypeId::DataType_CarriageWayList6972>
{
public:
    virtual ~AllListener() {}

public:
    //========================================
    void onData(const LogPolygonList2dFloat6817& lanes) override
    {
        // Copy LaneBoundaries
        m_lastLaneBoundaryList = lanes;

        if (!m_lastCarriageWay.empty())
        {
            m_laneEval.process(m_lastVehicleState, m_lastCarriageWay, m_lastLaneBoundaryList);
        }
    }

    //========================================
    void onData(const VehicleState& vs) override
    {
        //copy VehicleState
        m_lastVehicleState = vs;
    }

    //========================================
    void onData(const CarriageWayList& cwl) override
    {
        // copy CarriageWayIn6970
        m_lastCarriageWay = cwl.getCarriageWays();
    }

private:
    LaneEvaluation m_laneEval;
    LogPolygonList2dFloat6817 m_lastLaneBoundaryList;
    VehicleState m_lastVehicleState;
    CarriageWayList::CarriageWays m_lastCarriageWay;
}; // AllListener

//==============================================================================
//==============================================================================
//==============================================================================

int checkArguments(const int argc, const char** argv, bool& hasLogFile)
{
    const int minNbOfNeededArguments = 3;
    const int maxNbOfNeededArguments = 4;

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
                  << " DUTFILENAME REFERENCEFILENAME [LOGFILE]" << std::endl;
        std::cerr << "\tDUTFILENAME Name of the file to use for evaluation (Device under Test)." << std::endl;
        std::cerr << "\tREFERENCEFILENAME Name of the file to use as reference for evaluation test." << std::endl;
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
        exit(checkResult);
    int currArg = 1;

    const std::string dutFilename = argv[currArg++];
    const std::string refFilename = argv[currArg++];

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

    file_evaluation(dutFilename, refFilename);

    exit(0);
}

//==============================================================================

void file_evaluation(const std::string& dutFilename, const std::string& refFileName)
{
    IdcFile dutFile;
    dutFile.open(dutFilename);

    IdcFile refFile;
    refFile.open(refFileName);

    // this assumes that both idc files are in sync
    if (dutFile.isOpen() && refFile.isOpen())
    {
        AllListener allListener;
        dutFile.registerContainerListener(&allListener);
        refFile.registerContainerListener(&allListener);

        unsigned short nbMessages = 0; // # of messages we parsed

        const DataTypeId frameDataType = DataTypeId::DataType_Scan2205;

        IdcFile::ContainerImporterPairs p;
        while (dutFile.isGood() && refFile.isGood())
        {
            // TODO: in while refFile.isGood has always to be true
            do
            {
                p = refFile.getNextDataContainer();

                if (p.empty())
                {
                    continue;
                }
                refFile.notifyContainerListeners(p);

                ++nbMessages;
            } while (refFile.isGood() && (p.empty() || (p.at(0).second->getDataType() != frameDataType)));

            // TODO: in while dutFile.isGood has always to be true
            do
            {
                p = dutFile.getNextDataContainer();

                if (p.empty())
                {
                    continue;
                }
                refFile.notifyContainerListeners(p);

                ++nbMessages;
            } while (dutFile.isGood() && (p.empty() || (p.at(0).second->getDataType() != frameDataType)));
        } // while dutFile & refFile are good

        LOGTRACE(appLogger, "EOF reached. " << nbMessages << " known blocks found.");
    } // while dutFile & refFile are open
    else
    {
        LOGERROR(appLogger, "File not readable.");
    }
}

//==============================================================================
