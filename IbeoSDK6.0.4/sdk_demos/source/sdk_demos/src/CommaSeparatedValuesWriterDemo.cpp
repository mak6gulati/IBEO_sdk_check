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
//!\date Aug 12, 2019
//!
//!\example CommaSeparatedValuesWriterDemo.cpp
//! Demo project reading an idc file and writing some of the data to
//! comma separated values.
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2209.hpp>
#include <ibeo/common/sdk/devices/IdcFile.hpp>
#include <ibeo/common/sdk/IbeoSdk.hpp>

#include <boost/program_options.hpp>
#include <boost/asio.hpp>

#include <sstream>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

const std::string appName = "IbeoSdkCommaSeparatedValuesWriterDemo";
IbeoSdk ibeoSdk;
ibeo::common::logging::LoggerSPtr appLogger = ibeo::common::logging::LogManager::getInstance().createLogger(appName);

//==============================================================================

//==============================================================================
//! \brief CsvWriter
//!
//! Simple csv file writer to dump data to a file.
//------------------------------------------------------------------------------
class CsvWriter
{
    constexpr static const char* colSeparator = ", ";

public:
    ~CsvWriter()
    {
        m_file.flush();
        m_file.close();
    }

public:
    //========================================
    //! \brief Create a csv writer helper
    //! \param[in] filename  Name of written csv file
    //! \return true if file is open for csv export
    //----------------------------------------
    bool create(const std::string& filename)
    {
        m_file.open(filename);
        return m_file.is_open();
    }

    //========================================
    //! \brief Check if csv file is open
    //! \return true if file is open for csv export
    //----------------------------------------
    bool isOpen() { return m_file.is_open(); }

    //========================================
    //! \brief Write value to csv file and add a separator behind it
    //! \tparam    T      Type of value to be written into the file
    //! \param[in] value  Value to be written as separated row entry
    //----------------------------------------
    template<typename T>
    CsvWriter& operator<<(const T& value)
    {
        m_file << value << colSeparator;
        return *this;
    }

    //========================================
    //! \brief End current row in csv file.
    //----------------------------------------
    void endl()
    {
        m_file << std::endl;
        m_file.flush();
    }

private:
    std::ofstream m_file;
};

//==============================================================================
//! \brief Write uint8_t value as integer to csv file
//! \param[in] value  Value to be written as separated row entry
//! uint8_t would end up as char without the cast
//------------------------------------------------------------------------------
template<>
CsvWriter& CsvWriter::operator<<(const uint8_t& value)
{
    m_file << static_cast<int>(value) << colSeparator;
    return *this;
}

//==============================================================================

//==============================================================================
//! \brief Scan Listener
//!
//! Class for listening to scans
//! More Information: \ref ibeo::common::sdk::DataContainerListener
//------------------------------------------------------------------------------
class ScanListener : public ibeo::common::sdk::DataContainerListener<Scan2209, DataTypeId::DataType_Scan2209>,
                     public CsvWriter
{
public:
    ~ScanListener() override = default;

public:
    //========================================
    //!\brief Called on receiving a new Scan.
    //!\param[in] scan  Scan that has been received.
    //----------------------------------------
    void onData(const Scan2209& scan) override
    {
        *this << scan.getScanNumber() << scan.getStartTimestamp() << scan.getEndTimeOffset()
              << scan.getNumberOfScanPoints();

        for (const auto& pt : scan.getScanPoints())
        {
            *this << pt.getDeviceId() << pt.getEchoPulseWidth() << pt.getPositionX() << pt.getPositionY()
                  << pt.getPositionZ();
        }

        endl();
    }
}; // ScanListener

//==============================================================================
//==============================================================================

void csvWriterFile(const std::string& inFilename, const std::string& outFilename);

//==============================================================================
//==============================================================================

//==============================================================================
//! \brief Command Line Arguments
//!
//! Class to check/store the Comandline Argumante
//------------------------------------------------------------------------------
class CommandLineArguments
{
public:
    CommandLineArguments(int argc, const char** argv)
    {
        using namespace boost::program_options;
        variables_map cmdVars;

        options_description desc(appName);
        desc.add_options() //
            ("input,i", value<std::string>(&m_inputFileName)->required(), "Name of the input IDC file") //
            ("output,o", value<std::string>(&m_outputFileName)->required(), "Name of the output file.") //
            ("help,h", "Show this message");
        positional_options_description pos_opts;
        pos_opts.add("input", 1);

        try
        {
            store(command_line_parser(argc, argv).options(desc).positional(pos_opts).run(), cmdVars);
            notify(cmdVars);
        }
        catch (const boost::program_options::multiple_occurrences& e)
        {
            std::cerr << "*** Error in command line arguments: " << e.what() << std::endl;
            desc.print(std::cerr);
            exit(1);
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

        IdcFile testFile;

        if (!testFile.open(m_inputFileName))
        {
            std::cerr << ("Couldn't open IDC file!");
            exit(1);
        }
    }

public:
    const std::string& getInputFileName() const { return m_inputFileName; }
    const std::string& getOutputFileName() const { return m_outputFileName; }

protected:
    std::string m_inputFileName{};
    std::string m_outputFileName{};
}; // CommandLineArguments

//==============================================================================
//==============================================================================

//! \brief Demo for writing csv File from idc input
int main(const int argc, const char** argv)
{
    std::cerr << argv[0] << " (" << appName << ")"
              << " using IbeoSDK " << ibeoSdk.getVersion().toString() << std::endl;

    CommandLineArguments cmdargs(argc, argv);

    ibeo::common::logging::LogManager::getInstance().setDefaultLogLevel("Debug");

    // start the csv export
    csvWriterFile(cmdargs.getInputFileName(), cmdargs.getOutputFileName());

    exit(0);
}

//==============================================================================

// demo loop dumping Scan2209 scans to a csv file
void csvWriterFile(const std::string& inFilename, const std::string& outFilename)
{
    ScanListener scanListenerCsv;

    scanListenerCsv.create(outFilename);
    if (!scanListenerCsv.isOpen())
    {
        LOGERROR(appLogger, "Output file not open!");
        return;
    }

    IdcFile file;
    file.open(inFilename);
    if (file.isOpen())
    {
        file.registerContainerListener(&scanListenerCsv);

        while (file.isGood())
        {
            const IdcFile::ContainerImporterPairs p = file.getNextDataContainer();
            file.notifyContainerListeners(p);

            std::this_thread::yield();
        }
    }
}

//==============================================================================
