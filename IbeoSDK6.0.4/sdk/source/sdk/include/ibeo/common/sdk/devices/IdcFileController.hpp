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
//! \date Jun 28, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class IdcFile;

//==============================================================================
//!\brief A class adds some more control for an IdcFile as skipping forwards and
//!       backwards.
//------------------------------------------------------------------------------
class IdcFileController final
{
    friend class IdcFile;

private:
    //========================================
    //!\brief Constructor
    //!\param[in] idcFile  The IDC file this controller controls.
    //!\param[in] strm     The underlying fstream of \a idcFile.
    //!                    (It is an extra parameter since IdcFileController
    //!                    has no access to the fstream via the public IdcFile
    //!                    interface.
    //----------------------------------------
    IdcFileController(IdcFile& idcFile, std::fstream& strm) : m_idcFile(idcFile), m_strm(strm) {}

public:
    //========================================
    //!\brief Destructor.
    //----------------------------------------
    ~IdcFileController() = default;

public:
    //========================================
    //!\brief Get the controlled file.
    //!\return The controlled file.
    //----------------------------------------
    IdcFile& getIdcFile() { return m_idcFile; }

public:
    //========================================
    //!\brief Get the current stream read position.
    //!\return current position in stream.
    //----------------------------------------
    int64_t getPos() const;

    //========================================
    //!\brief Set the current read position to a known stream position.
    //!\param[in] position  Position to jump to.
    //! \note All stream error flags will be resetted (setting goodbit).
    //----------------------------------------
    void setPos(const int64_t position);

    //========================================
    //!\brief Get the size of the file.
    //!\return The size of the file in bytes.
    //----------------------------------------
    int64_t getFileSize();

public:
    //========================================
    //!\brief Advance \a nbOfMessages messages/DataBlocks
    //!       in the file.
    //!
    //!\param[in] nbOfMessagesToSkip  Number of messages to
    //!                               skip forward.
    //!\param[in] clearStreamFlags    If \c true, the stream
    //!                               flags will be cleared
    //!                               before the operation will
    //!                               be performed.
    //!\return \c true if the operation was successfull, i.e.
    //!        the stream is still good. \c false otherwise.
    //----------------------------------------
    bool skipDataBlocksForwards(const uint32_t nbOfMessagesToSkip, const bool clearStreamFlags = false);

    //========================================
    //!\brief Advance \a nbOfMessages messages/DataBlocks
    //!       in the file.
    //!
    //!\param[in] nbOfMessagesToSkip  Number of messages to
    //!                               skip backward.
    //!\param[in] clearStreamFlags    If \c true, the stream
    //!                               flags will be cleared
    //!                               before the operation will
    //!                               be performed.
    //!\return \c true if the operation was successful, i.e.
    //!        the stream is still good. \c false otherwise.
    //----------------------------------------
    bool skipDataBlocksBackwards(const uint32_t nbOfMessagesToSkip, const bool clearStreamFlags = false);

    //========================================
    //!\brief Move the file pointer in front of
    //!       the first DataBlock.
    //!
    //! The file pointer is moved in front of the first
    //! message, the IbeoDataHeader is read and the
    //! file pointer is moved back in front of the first message.
    //!
    //!\param[in] clearStreamFlags  If \c true, the stream
    //!                             flags will be cleared
    //!                             before the operation will
    //!                             be performed.
    //!\return \c true if the operation was successful, i.e.
    //!        the stream was set in front of the first DataBlock
    //!        and at this position a IbeoDataHeader could be
    //!        read.
    //----------------------------------------
    bool setToFirstDataBlock(const bool clearStreamFlags = false);

    //========================================
    //!\brief Move the file pointer in front of
    //!       the last DataBlock.
    //!
    //! The file pointer is moved in front of the last
    //! message, the DataBlock is read and the
    //! file pointer is moved back in front of the last message.
    //!
    //!\param[in] clearStreamFlags  If \c true, the stream
    //!                             flags will be cleared
    //!                             before the operation will
    //!                             be performed.
    //!\return \c true if the operation was successful, i.e.
    //!        the stream was set in front of the last DataBlock
    //!        and at this position a DataBlock could be
    //!        read.
    //----------------------------------------
    bool setToIdcTrailer(const bool clearStreamFlags = false);

    //========================================
    //!\brief Reads the next IbeoDataHeader from the file.
    //!\param[out] dh  The header next in file.
    //!\return \c true if the header was successfully has been read.
    //!        \c false if either no file is open or the
    //!        deserialization of the header failed.
    //!\note The file pointer will at the same position
    //!     as before the call.
    //----------------------------------------
    bool getNextHeader(IbeoDataHeader& dh);

    //========================================
    //!\brief Returns the start time and end time of the file.
    //!\param[out] startTime  The start time is the time stamp of the
    //!                       IbeoDataHeader at the beginning of the
    //!                       IDC file.
    //!\param[out] endTime    The end time is the time stamp of the
    //!                       IbeoDataHeader at the end of the
    //!                       IDC file or, if exists, the time stamp
    //!                       of the time stamp before the FrameIndex
    //!                       data block.
    //!\return \c true if the last and the first header in the file
    //!        were successfully read. \c false otherwise.
    //!\note It is assumed that the IDC file ends with and IdcTrailer and
    //!      preceeded by the FrameIndex.
    //----------------------------------------
    bool getTimeRange(NTPTime& startTime, NTPTime& endTime);

    //========================================
    //!\brief Convenient version of getTimerange(NTPTime&, NTPTime&).
    //----------------------------------------
    bool getTimeRange(boost::posix_time::ptime& startTime, boost::posix_time::ptime& endTime);

private:
    //========================================
    //!\brief Reference to the IdcFile object
    //!       this instance is controlling.
    //----------------------------------------
    IdcFile& m_idcFile;

    //========================================
    //!\brief Reference to the internal stream
    //!       of m_idcFile.
    //----------------------------------------
    std::fstream& m_strm;

    //========================================
    //!\brief Variable for internal use.
    //----------------------------------------
    IbeoDataHeader m_dh{};
}; // IcdFileControler

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
