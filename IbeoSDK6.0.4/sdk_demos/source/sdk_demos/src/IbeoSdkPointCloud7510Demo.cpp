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
//!\date Mar 29, 2016
//!
//!\example IbeoSdkPointCloud7510Demo.cpp Demo project for reading IDC files and process the PointCloud7510.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/EcefPoint.hpp>
#include <ibeo/common/sdk/devices/IdcFile.hpp>

#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkPointCloud7510Demo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void file_demo(const std::string& filename);

//==============================================================================

class Listener
  : public ibeo::common::sdk::DataContainerListener<VehicleState2808, DataTypeId::DataType_VehicleStateBasic2808>,
    public ibeo::common::sdk::DataContainerListener<PointCloud7510, DataTypeId::DataType_PointCloud7510>
{
public:
    Listener();
    virtual ~Listener() {}

public:
    void onData(const VehicleState2808& vs) override;
    void onData(const PointCloud7510& pcp) override;

    void generatePointCloud(const PointCloud7510* const pcp, const VehicleState2808* const vsb);

protected:
    VehicleState2808 m_bufferedVehicleState;
    bool m_hasBufferedVehicleState;
}; // Listener

//==============================================================================

Listener::Listener() : m_bufferedVehicleState(), m_hasBufferedVehicleState(false) {}

//==============================================================================

void Listener::onData(const VehicleState2808& vs)
{
    m_bufferedVehicleState    = vs;
    m_hasBufferedVehicleState = true;
}

//==============================================================================

void Listener::onData(const PointCloud7510& pcp)
{
    if (m_hasBufferedVehicleState)
        generatePointCloud(&pcp, &m_bufferedVehicleState);
}

//==============================================================================

void Listener::generatePointCloud(const PointCloud7510* const pcp, const VehicleState2808* const vsb)
{
    ReferencePlane targetRefPlane(*vsb);

    EcefPoint targetRefPointsEcef;

    PositionWgs84::llaToEcef(targetRefPlane.getGpsPoint().getLatitudeInRad(),
                             targetRefPlane.getGpsPoint().getLongitudeInRad(),
                             targetRefPointsEcef);

    Matrix3x3<float> invTargetRotMatrix = targetRefPlane.getRotationMatrix().getInverse();

    for (const PointCloudPointIn7510& point : pcp->getPoints())
    {
        const ReferencePlane& originRefPlane = pcp->getReferencePlane();
        const Vector3<float>& originOffset   = point.getPoint3D();
        Vector3<float> targetOffset;

        if (targetRefPlane != originRefPlane)
        {
            PointBase::transformToShiftedReferencePlaneF3d(
                originRefPlane, targetRefPointsEcef, invTargetRotMatrix, originOffset, targetOffset);
        }
        else
        {
            targetOffset = originOffset;
        }
    }
}

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
        Listener listener;

        file.registerContainerListener(&listener);

        unsigned short nbMessages = 0; // # of messages we parsed

        while (file.isGood())
        {
            const auto db = file.getNextDataContainer();
            if (db.empty())
            {
                continue; // might be eof or unknown file type
            }
            file.notifyContainerListeners(db);
            ++nbMessages;
        }

        LOGTRACE(appLogger, "EOF reached. " << nbMessages << " known blocks found.");
    }
    else
    {
        LOGERROR(appLogger, "File not readable.");
    }
}

//==============================================================================
