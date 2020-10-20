//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jun 6, 2016
//!
//!\example IbeoSdkMetaInformationDemo.cpp Demo project for reading meta information from an idc-file.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/IbeoSdk.hpp>
#include <ibeo/common/sdk/misc/Version.hpp>
#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/devices/IdcFile.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationBase.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationList.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationAppBaseConfig.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationEcuId.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationKeywords.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationVersionNumber.hpp>

#include <boost/algorithm/string/join.hpp>

using namespace ibeo::common::sdk;

const std::string appName = "IbeoSdkMetaInformationDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void file_demo(const std::string& filename);

//==============================================================================

class MetaInformationListener
  : public ibeo::common::sdk::DataContainerListener<MetaInformationList, DataTypeId::DataType_MetaInformationList7110>
{
public:
    MetaInformationListener() {}
    virtual ~MetaInformationListener() {}

public:
    virtual void onData(const MetaInformationList& mil) override;
}; // MetaInformationListener

//==============================================================================

void MetaInformationListener::onData(const MetaInformationList& mil)
{
    using MetaInfoMap = MetaInformationList::MetaInformationMap;
    using InfoVector  = MetaInformationList::MetaInformationSPtrVector;

    const MetaInformationList metaList = mil;
    const MetaInfoMap& metaInfoMap     = metaList.getMetaInformationMap();

    std::stringstream stream;
    stream << std::endl << "The following meta information is provided within the file: ";

    for (MetaInfoMap::const_iterator infoMapIter = metaInfoMap.begin(); infoMapIter != metaInfoMap.end(); ++infoMapIter)
    {
        const InfoVector& infoVec = infoMapIter->second;
        stream << std::endl << "  Type: " << infoMapIter->first;
        for (InfoVector::const_iterator infoIter = infoVec.begin(); infoIter != infoVec.end(); ++infoIter)
        {
            const MetaInformationBaseSPtr& info = *infoIter;
            switch (info->getType())
            {
            case MetaInformationBase::MetaInformationType::AppBaseConfig:
            {
                const MetaInformationAppBaseConfig& abconfig = dynamic_cast<const MetaInformationAppBaseConfig&>(*info);
                stream << std::endl << "    " << abconfig.getAppBaseConfig();
                break;
            }
            case MetaInformationBase::MetaInformationType::EcuId:
            {
                const MetaInformationEcuId& ecuId = dynamic_cast<const MetaInformationEcuId&>(*info);
                stream << std::endl << "    " << ecuId.getEcuId();
                break;
            }
            case MetaInformationBase::MetaInformationType::Keywords:
            {
                const MetaInformationKeywords& keywords         = dynamic_cast<const MetaInformationKeywords&>(*info);
                const MetaInformationKeywords::StringSet& kwSet = keywords.getKeywords();
                stream << std::endl << "    " << boost::algorithm::join(kwSet, "; ");

                break;
            }
            case MetaInformationBase::MetaInformationType::VersionNumber:
            {
                const MetaInformationVersionNumber& versionNumber
                    = dynamic_cast<const MetaInformationVersionNumber&>(*info);
                stream << std::endl
                       << "    " << versionNumber.getSoftwareType() << ": " << versionNumber.getMajorVersion() << "."
                       << versionNumber.getMinorVersion() << "." << versionNumber.getPatchVersion() << "."
                       << versionNumber.getExtraString();
                break;
            }
            default:
                break;
            }
        }
    }

    LOGINFO(appLogger, stream.str());
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
        MetaInformationListener listener;

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

        LOGDEBUG(appLogger, "EOF reached. " << nbMessages << " known blocks found.");
    }
    else
    {
        LOGERROR(appLogger, "File not readable.");
    }
}

//==============================================================================
