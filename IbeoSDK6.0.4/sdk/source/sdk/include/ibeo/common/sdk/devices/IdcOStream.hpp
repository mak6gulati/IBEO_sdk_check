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
//!\date Aug 22, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130.hpp>
#include <ibeo/common/sdk/datablocks/DataBlock.hpp>
#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>

#include <fstream>
#include <memory>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
//!\brief An IDC output stream.
//------------------------------------------------------------------------------
class IdcOStream
{
private:
    //========================================
    //!\brief A wrapper class providing a std::ostream.
    //!
    //! The origin of the stored ostream (reference)
    //! can be an ostream passed in the constructor
    //! call or an internally hold fstream.
    //----------------------------------------
    class OStreamWrapper
    {
    public:
        //========================================
        //!\brief Constructor. Wraps the given ostream.
        //!\param[in] os  ostream to be wrapped.
        //----------------------------------------
        OStreamWrapper(std::ostream& os);

        //========================================
        //!\brief Constructor. Wraps an internally held
        //!       fstream.
        //!
        //! The file will be opened in binary write mode.
        //!
        //!\param[in] filename  Name of the file the
        //!                     fstream will be associated
        //!                     with.
        //----------------------------------------
        OStreamWrapper(const std::string& filename);

        //========================================
        //!\brief Destructor.
        //!
        //! Closes an open fstream in case it has been
        //! opened.
        //----------------------------------------
        ~OStreamWrapper() = default;

    public:
        //========================================
        //!\brief Return the ostream.
        //!\return A reference to the wrapped ostream.
        //----------------------------------------
        std::ostream& operator()() { return m_os; }

    public:
        //========================================
        //!\brief Checks whether the fstream is still open
        //!       if it is a file.
        //!\return \c true if this instance is not wrapping
        //!        a fstream or if the fstream is associated
        //!        to a file.
        //!        \c false if the instance is holding an
        //!        fstream which is not associated with a file.
        //----------------------------------------
        bool isOpen() const { return (m_isFile && m_fs.is_open()) || (!m_isFile && m_os.good()); }

        //========================================
        //!\brief Returns whether this instance is wrapping
        //!       an ostream referring with the internal
        //!       fstream.
        //!\return \c true if this instance is wrapping
        //!        actually the internal fstream.
        //!        \c false if this instance was constructed
        //!        with an external ostream.
        //----------------------------------------
        bool isFile() const { return m_isFile; }

    private:
        //========================================
        //!\brief Internal fstream. Valid only if
        //!       \a m_isFile is \c true.
        //!
        //----------------------------------------
        std::fstream m_fs{};

        //========================================
        //!\brief The reference to the wrapped ostream.
        //----------------------------------------
        std::ostream& m_os;

        //========================================
        //!\brief \c true if \a m_os is referring to
        //!       \m_fs.
        //----------------------------------------
        bool m_isFile;
    }; // OStreamWrapper

private:
    //========================================
    //!\brief Get the default FramingPolicy.
    //!\return The default FramingPolicy.
    //----------------------------------------
    static ibeo::common::sdk::FramingPolicyIn6130 getDefaultFramingPolicy();

public:
    //========================================
    //!\brief Creates an IdcIStream which is associated
    //!       with the file given by \a filename
    //!       using the default FramingPolicy.
    //!\param[in] filename  The name of the file to be
    //!                     wrapped as ostream.
    //----------------------------------------
    explicit IdcOStream(const std::string& filename);

    //========================================
    //!\brief Creates an IdcIStream which is associated
    //!       with the file given by \a filename
    //!       using the given FramingPolicy \a policy.
    //!\param[in] filename  The name of the file to be
    //!                     wrapped as ostream.
    //!\param[in] policy    Policy to be used to create the
    //!                     FrameIndex6130 which will be placed
    //!                     at the end of the file right before
    //!                     the IdcTrailer.
    //----------------------------------------
    explicit IdcOStream(const std::string& filename, const ibeo::common::sdk::FramingPolicyIn6130& policy);

    //========================================
    //!\brief Creates an IdcIStream from an external stream
    //!       using the default FramingPolicy.
    //!\param[in] os  The external ostream to be wrapped.
    //----------------------------------------
    explicit IdcOStream(std::ostream& os);

    //========================================
    //!\brief Creates an IdcIStream from an external stream
    //!       using the given FramingPolicy \a policy.
    //!\param[in] os      The external ostream to be wrapped.
    //!\param[in] policy  Policy to be used to create the
    //!                   FrameIndex6130 which will be placed
    //!                   at the end of the file right before
    //!                   the IdcTrailer.
    //----------------------------------------
    explicit IdcOStream(std::ostream& os, const ibeo::common::sdk::FramingPolicyIn6130& policy);

    //========================================
    //!\brief Destructor.
    //!
    //! If isOpen returns true, before destroying
    //! this instance, a FrameIndex6130 will be
    //! written to the stream followed by an IdcTrailer.
    //----------------------------------------
    virtual ~IdcOStream();

public:
    //========================================
    //!\brief Create/Open a file for write access using the
    //!       default FramingPolicy.
    //!\param[in] filename  Create a new (write-only) IDC file.
    //!\return \c true if the file was successful
    //!        opened/created. \c false otherwise.
    //----------------------------------------
    bool create(const std::string& filename);

    //========================================
    //!\brief Create/Open a file for write access.
    //!\param[in] filename  Create a new (write-only) IDC file.
    //!\param[in] policy    Policy to be used to create the
    //!                     FrameIndex6130 which will be placed
    //!                     at the end of the file right before
    //!                     the IdcTrailer.
    //!\return \c true if the file was successful
    //!        opened/created. \c false otherwise.
    //----------------------------------------
    bool create(const std::string& filename, const ibeo::common::sdk::FramingPolicyIn6130& policy);

public:
    //========================================
    //!\brief Write a DataBlock and its IbeoDataHeader
    //!        to this file.
    //!
    //! \param[in] dh    IbeoDataHeader for the
    //!                  serialized DataBlock in
    //!                  \a body.
    //! \param[in] body  Serialized version of
    //!                  the DataBlock to be
    //!                  written to the IdcFile.
    //!\return \c true if the write operation was successful.
    //!        \c false if no file is open or the serialization of
    //!        \a dh or writing the \a body failed.
    //----------------------------------------
    virtual bool write(const IbeoDataHeader& dh, const char* const body);

    //========================================
    //!\brief Write a DataBlock and its IbeoDataHeader
    //!       to this file.
    //!
    //!\param[in] dh  IbeoDataHeader for the
    //!               serialized DataBlock in
    //!               \a db.
    //!\param[in] db  DataBlock to be written
    //!               to the IdcFile.
    //!\return \c true if the write operation was successful.
    //!        \c false if no file is open or the serialization of
    //!        \a dh or \a db failed.
    //----------------------------------------
    virtual bool write(const IbeoDataHeader& dh, const DataBlock* const db);

    //========================================
    //!\brief Write a DataContainer with help of an exporter
    //!       to this file.
    //!
    //!\param[in] dh        IbeoDataHeader for container
    //!                     to be serialized. DataType and
    //!                     serialized size will be calculated
    //!                     here.
    //!\param[in] c         DataContainer to be written
    //!                     to the IdcFile.
    //!\param[in] exporter  Exporter to be used to
    //!                     serialize the container.
    //!\return \c true if the write operation was successful.
    //!        \c false if no file is open or the serialization of
    //!        \a dh or \a c failed.
    //----------------------------------------
    virtual bool write(IbeoDataHeader dh, const DataContainerBase& c, const ExporterBase& exporter);

public:
    //========================================
    //!\brief Check whether the file is open.
    //!
    // !\return \c true if the file was successfully
    // !        opened/created. \c false otherwise.
    //----------------------------------------
    bool isOpen() { return m_strw.isOpen(); }

    //========================================
    //!\brief Check whether the eofbit is set.
    //!\return \c true if the eofbit is set.
    //!        \c false otherwise.
    //----------------------------------------
    bool isEof() { return m_strw().eof(); }

    //========================================
    //!\brief Check if no error bit is set.
    //! \return \c true if the not error bit is set.
    //!         \c false otherwise.
    //----------------------------------------
    bool isGood() { return m_strw().good(); }

    //========================================
    //!\brief Check whether the stream is associated
    //!       with a file.
    //! \return \c true if the stream is associated
    //!         with a file.
    //!         \c false otherwise.
    //----------------------------------------
    bool isFile() { return m_strw.isFile(); }

public:
    //========================================
    //!\brief Return the frame index.
    //!\return The frame index.
    //----------------------------------------
    const FrameIndex6130& getFrameIndex() const { return m_frameIndex; }

public:
    //========================================
    //!\brief Returns the filename of the stream.
    //!\return The filename, if the IdcIStream was
    //!        created with a filename. An empty
    //!        string otherwise.
    //----------------------------------------
    const std::string& getFilename() const { return m_filename; }

protected:
    //========================================
    //!\brief Serialize the given IbeoDataHeder to the
    //!       internal stream.
    //!
    //! Before serializing \a dh, the frame index will
    //! be updated if necessary and the first header
    //! timestamp will be set if not yet done.
    //!
    //!\param[in] dh  IbeoDataHeader to be serialized.
    //!\return \c false if an error occurred serializing
    //!        \a dh, \c true otherwise.
    //----------------------------------------
    bool writeHeader(IbeoDataHeader dh);

    //========================================
    //!\brief Write \a length bytes starting at
    //!       \a data to the internal stream.
    //!\param[in] data    byte array to be written to
    //!                   to the stream.
    //!\param[in] length  Number of bytes to be
    //!                   written.
    //!\return \c true if writing the data was
    //!        successful, \c false otherwise.
    //----------------------------------------
    virtual bool write(const char* const data, const uint32_t length);

private:
    //========================================
    //!\brief Closes a write-only IdcFile.
    //!
    //! Is this IdcFile an output file, this method
    //! will write a FrameIndex6130 and a IdcTrailer6120 to
    //! the file. After that it will close the
    //! underlying stream.
    //----------------------------------------
    void close();

protected:
    //========================================
    //!\brief The FrameIndex6130 of the currently open file.
    //!
    //! This is the frame index which will be filled
    //! while writing into the file.
    //!
    //!\attention m_frameIndex is only valid if a file is currently open.
    //----------------------------------------
    FrameIndex6130 m_frameIndex{};

    //========================================
    //!\brief Internal stream, the IDC file.
    //----------------------------------------
    OStreamWrapper m_strw;

    //========================================
    //!\brief The name of an open file.
    //----------------------------------------
    std::string m_filename{}; //idc filename (only valid for opened file)

    //========================================
    //!\brief The size of the last message that
    //!       has been written. (Only for writing
    //!       an IDC file).
    //----------------------------------------
    uint32_t m_latestMsgSize{0};

    //========================================
    //!\brief The time stamp of the last header
    //!       written.
    //----------------------------------------
    NTPTime m_latestHeaderTimestamp{};

    //========================================
    //!\brief The time stamp of the first header
    //!       written.
    //----------------------------------------
    NTPTime m_firstHeaderTimestamp{};

    //========================================
    //!\brief Variable to hold the deserialization
    //!       of a IbeoDataHeader.
    //----------------------------------------
    IbeoDataHeader m_dh{};

    //========================================
    //!\brief Tells, whether yet a DataBlock has
    //!       been written into the file.
    //----------------------------------------
    bool m_firstDataBlockToBeWritten{false};

}; // IdcOStream

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
