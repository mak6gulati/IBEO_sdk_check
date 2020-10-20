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
//!\date Apr 7, 2018
//!
//!\example IbeoSdkGeneralFileDemo.cpp Demo project for reading IDC files and process the data containers with general
//!data types. See the <a href='sdk_user manual.pdf'>sdk_user manual.pdf</a> for more info.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/lux.hpp>
#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/minilux.hpp>
#include <ibeo/common/sdk/scala.hpp>

#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/devices/IdcFile.hpp>

#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkGeneralFileDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

std::string getScannerTypeName(const ScannerType scannerType);
std::string getObjectClassName(ObjectClass objectClass);
void generalFileDemoContainer(const std::string& filename);

//==============================================================================

TimeConversion tc;

//==============================================================================

class AllListener : public ibeo::common::sdk::GeneralDataContainerListener<Scan>,
                    public ibeo::common::sdk::GeneralDataContainerListener<ObjectList>,
                    public ibeo::common::sdk::GeneralDataContainerListener<VehicleState>
{
public:
    virtual ~AllListener() = default;

public:
    //========================================
    virtual void onData(const Scan& scan) override
    {
        // Get scanners per type.
        std::map<ScannerType, uint32_t> scannersPerType;

        for (const ScannerInfo& scannerInfo : scan.getScannerInfos())
        {
            ScannerType scannerType = scannerInfo.getScannerType();
            if (scannersPerType.find(scannerType) == scannersPerType.end())
            {
                scannersPerType[scannerType] = 1;
            }
            else
            {
                ++scannersPerType[scannerType];
            }
        }

        LOGINFO(appLogger,
                "Scan container received: # "
                    << scan.getScanNumber() << "  start time: " << tc.toString(scan.getStartTimestamp().toPtime(), 3));
        LOGINFO(appLogger, "  # scan points: " << scan.getNumberOfScanPoints());

        if (scan.getScannerInfos().empty())
        {
            LOGINFO(appLogger, "  no scanner infos found");
        }
        else
        {
            LOGINFO(appLogger, "  scanners:");
            for (const std::pair<ScannerType, uint32_t>& scannerCount : scannersPerType)
            {
                LOGINFO(appLogger, "    # " << getScannerTypeName(scannerCount.first) << ": " << scannerCount.second);
            }
        }

        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const VehicleState& vs) override
    {
        LOGINFO(appLogger, "Vehicle state container received: ");
        LOGINFO(appLogger, "  position: " << vs.getRelativeXPosition() << "/" << vs.getRelativeYPosition());
        LOGINFO(appLogger, "  yaw rate: " << vs.getYawRate());
        LOGINFO(appLogger, "  speed: " << vs.getLongitudinalVelocity());
        LOGINFO(appLogger, "========================================================");
    }

    //========================================
    void onData(const ObjectList& objList) override
    {
        // Get (static/dynamic) objects per class.
        std::map<ObjectClass, uint32_t> staticObjectsPerClass;
        std::map<ObjectClass, uint32_t> dynamicObjectsPerClass;

        for (const Object& object : objList.getObjects())
        {
            std::map<ObjectClass, uint32_t>& objectsPerClass
                = object.isMobile() ? dynamicObjectsPerClass : staticObjectsPerClass;

            ObjectClass objectClass = object.getClassification();
            if (objectsPerClass.find(objectClass) == dynamicObjectsPerClass.end())
            {
                objectsPerClass[objectClass] = 1;
            }
            else
            {
                ++objectsPerClass[objectClass];
            }
        }

        LOGINFO(appLogger, "ObjectList container received:");

        LOGINFO(appLogger, "  static objects:");
        if (staticObjectsPerClass.empty())
        {
            LOGINFO(appLogger, "    none");
        }
        else
        {
            for (const std::pair<ObjectClass, uint32_t>& objectCount : staticObjectsPerClass)
            {
                LOGINFO(appLogger, "    # " << getObjectClassName(objectCount.first) << ": " << objectCount.second);
            }
        }

        LOGINFO(appLogger, "  dynamic objects:");
        if (dynamicObjectsPerClass.empty())
        {
            LOGINFO(appLogger, "    none");
        }
        else
        {
            for (const std::pair<ObjectClass, uint32_t>& dynamicObjectCount : dynamicObjectsPerClass)
            {
                LOGINFO(appLogger,
                        "    # " << getObjectClassName(dynamicObjectCount.first) << ": " << dynamicObjectCount.second);
            }
        }

        LOGINFO(appLogger, "========================================================");
    }

    //========================================
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
        exit(checkResult);
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

    generalFileDemoContainer(filename);

    exit(0);
}

//==============================================================================

std::string getScannerTypeName(const ScannerType scannerType)
{
    switch (scannerType)
    {
    case ScannerType::Invalid:
        return "<invalid>";
    case ScannerType::Ecu:
        return "Ibeo Ecu";
    case ScannerType::Lux:
        return "Ibeo Lux3";
    case ScannerType::Lux4:
        return "Ibeo Lux4";
    case ScannerType::MiniLux:
        return "Ibeo MiniLux";
    case ScannerType::SickLMS200:
        return "Sick LMS200/291";
    case ScannerType::SickLMS100:
        return "Sick LMS100/111";
    case ScannerType::SickLMS500:
        return "Sick LMS500/511";
    case ScannerType::ScalaB2:
        return "Ibeo/Valeo ScalaB2";
    case ScannerType::ThirdPartyVLidarVH32:
        return "ThirdPartyVLidar VH32";
    case ScannerType::ThirdPartyVLidarVH64:
        return "ThirdPartyVLidar VH64";

    default:
    {
        std::stringstream str;
        str << "<0x" << std::hex << static_cast<uint8_t>(scannerType) << ">";
        return str.str();
    }
    } // switch
}

//==============================================================================

std::string getObjectClassName(ObjectClass objectClass)
{
    switch (objectClass)
    {
    case ObjectClass::Unclassified:
        return "<unclassified>";
    case ObjectClass::UnknownSmall:
        return "unknown small";
    case ObjectClass::UnknownBig:
        return "unknown big";
    case ObjectClass::Pedestrian:
        return "pedestrian";
    case ObjectClass::Bike:
        return "bike";
    case ObjectClass::Car:
        return "car";
    case ObjectClass::Truck:
        return "truck";
    case ObjectClass::Underdriveable:
        return "underdriveable";
    case ObjectClass::Motorbike:
        return "motorbike";
    case ObjectClass::Bicycle:
        return "bicycle";

    default:
    {
        std::stringstream str;
        str << "<0x" << std::hex << static_cast<uint8_t>(objectClass) << ">";
        return str.str();
    }
    } // switch
}

//==============================================================================

void generalFileDemoContainer(const std::string& filename)
{
    IdcFile file;
    file.open(filename);
    if (file.isOpen())
    {
        AllListener allListener;

        file.registerContainerListener(&allListener);

        uint32_t nbOfMessages = 0; // # of messages we parsed

        while (file.isGood())
        {
            const IdcFile::ContainerImporterPairs p = file.getNextDataContainer();
            //			for (auto p1: p)
            //			{
            //				LOGINFO(appLogger, toHex(p1.second->getDataType()));
            //			}

            file.notifyContainerListeners(p);
            ++nbOfMessages;
        }

        LOGINFO(appLogger, "EOF reached. " << nbOfMessages << " known blocks found.");
    }
    else
    {
        LOGERROR(appLogger, "File not readable.");
    }
}

//==============================================================================
