//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date May 25, 2016
//!
//! This tool is comparing the two given IDC files byte by byte.
//! Only the timestamps in the IbeoDataHeader will be ignored and
//! allowed to be different.
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/lux.hpp>
#include <ibeo/common/sdk/ecu.hpp>
#include <ibeo/common/sdk/minilux.hpp>
#include <ibeo/common/sdk/scala.hpp>

#include <ibeo/common/sdk/devices/IdcFile.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

//==============================================================================

using namespace ibeo::common::sdk;
using namespace std;

//==============================================================================

const std::string appName = "IdcCompare";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

class IdcComparator
{
public:
    //========================================
    //! \brief Create an IdcComparator instance.
    //!
    //! \param[in] filename1         Name of the first file to be compared.
    //! \param[in] filename2         Name of the second file to be compared.
    //----------------------------------------
    IdcComparator(const string& filename1, const string& filename2);
    ~IdcComparator();

private:
    IdcComparator(const IdcComparator&) = delete; // forbidden
    IdcComparator& operator=(const IdcComparator&) = delete; // forbidden

public:
    //========================================
    //! \brief Start the compare process.
    //!
    //! \return Returns whether the two files are
    //!         equal (\c true) or not (\c false).
    //----------------------------------------
    bool compare();

protected:
    //========================================
    //! \brief Open all files.
    //! \return Returns whether opening the files
    //!         was successfull or not.
    //----------------------------------------
    bool openFiles();

    //========================================
    //! \brief Checks whether all input files are open.
    //! \return \c true if both input files are open.
    //!         \c false otherwise.
    //----------------------------------------
    bool areFilesOpen() const;

    //========================================
    //! \brief Compare the current datablocks
    //!        from the two files.
    //! \return \c true if the data block from
    //!         file1 (\a dh1, \a rawData1) is
    //!         identically to file2 (\a dh2, \a rawData2).
    //!         Only the header time stamps may
    //!         be different.
    //!         \c false otherwise.
    //----------------------------------------
    bool onData(const IbeoDataHeader& dh1,
                const std::shared_ptr<char> rawData1,
                const IbeoDataHeader& dh2,
                const std::shared_ptr<char> rawData2);

protected:
    string m_filename1;
    string m_filename2;

    std::shared_ptr<IdcFile> m_inFile1;
    std::shared_ptr<IdcFile> m_inFile2;
}; // IdcComparator

//==============================================================================

IdcComparator::IdcComparator(const string& filename1, const string& filename2)
  : m_filename1(filename1), m_filename2(filename2), m_inFile1(), m_inFile2()
{}

//==============================================================================

IdcComparator::~IdcComparator() {}

//==============================================================================

bool IdcComparator::compare()
{
    openFiles();

    if (!areFilesOpen())
    {
        LOGERROR(appLogger, "Input files are not open");
        return false;
    }

    while (m_inFile1->isGood() && m_inFile2->isGood())
    {
        IbeoDataHeader dh1;
        std::shared_ptr<char> data1 = m_inFile1->getNextDataBlockRaw(dh1);
        IbeoDataHeader dh2;
        std::shared_ptr<char> data2 = m_inFile2->getNextDataBlockRaw(dh2);

        if (!onData(dh1, data1, dh2, data2))
            return false;
    } // while

    return true;
}

//==============================================================================

bool IdcComparator::openFiles()
{
    m_inFile1.reset(new IdcFile);
    if (!m_inFile1->open(m_filename1))
    {
        LOGERROR(appLogger, "Could not open idc file '" << m_filename1 << "' for input");
        return false;
    }
    m_inFile2.reset(new IdcFile);
    if (!m_inFile2->open(m_filename2))
    {
        LOGERROR(appLogger, "Could not open idc file '" << m_filename2 << "' for input");
        return false;
    }
    return true;
}

//==============================================================================

bool IdcComparator::areFilesOpen() const
{
    if (!m_inFile1.get())
        return false;
    if (!m_inFile1->isOpen())
        return false;
    if (!m_inFile2.get())
        return false;
    if (!m_inFile2->isOpen())
        return false;

    return true;
}

//==============================================================================

bool IdcComparator::onData(const IbeoDataHeader& dh1,
                           const std::shared_ptr<char> rawData1,
                           const IbeoDataHeader& dh2,
                           const std::shared_ptr<char> rawData2)
{
    if (rawData1.get() && rawData2.get())
    {
        LOGTRACE(appLogger, "Compare " << toHex(dh1.getDataType()) << "  and  " << toHex(dh2.getDataType()));

        if (!ibeo::common::sdk::compareIbeoDataHeaderWithoutDate(dh1, dh2))
        {
            LOGINFO(appLogger, "Header where different.");
            return false;
        }

        if (0 != (strncmp(rawData1.get(), rawData2.get(), dh1.getMessageSize())))
        {
            LOGINFO(appLogger, "Body where different.");
            return false;
        }
    }
    else if (rawData1.get())
    {
        LOGINFO(appLogger, "File '" << m_filename2 << "' is shorter than '" << m_filename1 << "'");
        return false;
    }
    else if (rawData2.get())
    {
        LOGINFO(appLogger, "File '" << m_filename1 << "' is shorter than '" << m_filename2 << "'");
        return false;
    }

    return true;
}

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

class CommandLineArguments
{
public:
    CommandLineArguments(int argc, const char** argv) : m_inputFile(2), m_hasLogFile(false), m_logFilename()
    {
        using namespace boost::program_options;
        variables_map cmdVars;

        options_description desc("IdcComparator");
        desc.add_options()(
            "input1,1", value<std::string>(&m_inputFile[0])->required(), "Name of the first IDC input file")(
            "input2,2", value<std::string>(&m_inputFile[1])->required(), "Name of the second IDC input file")(
            "logfile,l", value<std::string>(&m_logFilename), "Name of the log file (optional).")("help,h",
                                                                                                 "Show this message");

        positional_options_description pos_opts;
        pos_opts.add("input1", 1);
        pos_opts.add("input2", 1);
        pos_opts.add("output", 1);
        pos_opts.add("logfile", 1);

        try
        {
            store(command_line_parser(argc, argv).options(desc).positional(pos_opts).run(), cmdVars);
        }
        catch (const boost::program_options::multiple_occurrences&)
        {
            std::cerr << "*** Command line option has given more than once or too many parameters provided."
                      << std::endl;
            desc.print(std::cerr);
            exit(1);
        }
        catch (const boost::program_options::error& e)
        {
            std::cerr << "*** Error in command line arguments: " << e.what() << std::endl;
            desc.print(std::cerr);
            exit(1);
        }

        try
        {
            notify(cmdVars);
        }
        catch (const boost::program_options::error& e)
        {
            std::cerr << "*** Error in command line arguments: " << e.what() << std::endl;
            desc.print(std::cerr);
            exit(1);
        }

        if (cmdVars.count("help"))
        {
            desc.print(std::cerr);
            exit(0);
        }

        m_hasLogFile = cmdVars.count("logfile") >= 1;
    }

public:
    const std::vector<std::string> getInputFiles() { return m_inputFile; }
    const std::string& getOutputFile() const { return m_outputFile; }
    const std::string& getLogFileName() const { return m_logFilename; }
    bool hasLogFile() const { return m_hasLogFile; }

protected:
    std::vector<std::string> m_inputFile;
    std::string m_outputFile;
    bool m_hasLogFile;
    std::string m_logFilename;
}; // CommandLineArguments

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

int main(const int argc, const char** argv)
{
    std::cerr << argv[0] << " (" << appName << ")"
              << " using IbeoSDK " << ibeoSdk.getVersion().toString() << std::endl;

    CommandLineArguments cmdargs(argc, argv);

    if (cmdargs.hasLogFile())
    {
        ibeo::common::logging::FileLoggerBackendSPtr fileLoggerBackend
            = std::dynamic_pointer_cast<ibeo::common::logging::FileLoggerBackend>(
                ibeo::common::logging::LogManager::getInstance().getBackendById(
                    ibeo::common::logging::FileLoggerBackend::getBackendId()));
        fileLoggerBackend->setFilePath(cmdargs.getLogFileName());
    }

    ibeo::common::logging::LogManager::getInstance().setDefaultLogLevel("Debug");

    if (cmdargs.hasLogFile())
    {
        LOGINFO(appLogger,
                argv[0] << " (" << appName << ")"
                        << " using IbeoSDK " << ibeoSdk.getVersion().toString());
    }

    IdcComparator comparator(cmdargs.getInputFiles().at(0), cmdargs.getInputFiles().at(1));

    if (comparator.compare())
    {
        LOGINFO(appLogger, "Files are equal.");
    }
    else
    {
        LOGINFO(appLogger, "Files are not equal.");
    }
    exit(0);
}

//==============================================================================
