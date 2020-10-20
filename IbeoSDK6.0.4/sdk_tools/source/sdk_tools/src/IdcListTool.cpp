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
//!\date Jul 22, 2015
//!
//! Tool to list the content of an IDC file
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/devices/IdcFile.hpp>
#include <ibeo/common/sdk/devices/IdcFileController.hpp>
#include <ibeo/common/sdk/IbeoSdk.hpp>

#include <inttypes.h>
#include <iostream>
#include <cstdlib>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IdcRepairTool";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

void extractList(const std::string& filename);

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

    extractList(filename);

    exit(0);
}

//==============================================================================

void extractList(const std::string& filename)
{
    IdcFile input;
    auto contr{input.createController()};

    if (input.open(filename))
    {
        //		TargetFile output(filename+"out.idc");

        IbeoDataHeader dh;
        unsigned short nbMessages = 0; // # of messages we parsed

        printf("%8s   %6s %10s %10s\n", "FilePos", "D-Type", "MsgSize", "PrevMsgSize");

        while (input.isGood())
        {
            std::shared_ptr<char> db = input.getNextDataBlockRaw(dh);
            if (db.get() == nullptr)
            {
                continue; // might be eof or unknown file type
            }

            if ((dh.getDataType() == DataTypeId::DataType_IdcTrailer6120)
                || (dh.getDataType() == DataTypeId::DataType_FrameIndex6130))
            {
                // do not copy the trailer and the index into the new
                // file. Those datablocks will be automatically generated
                // when the file will be closed.
                continue;
            }

            printf("%8" PRId64 "   0x%04x %10d %10d\n",
                   contr->getPos(),
                   int(dh.getDataType()),
                   dh.getMessageSize(),
                   dh.getPreviousMessageSize());

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
