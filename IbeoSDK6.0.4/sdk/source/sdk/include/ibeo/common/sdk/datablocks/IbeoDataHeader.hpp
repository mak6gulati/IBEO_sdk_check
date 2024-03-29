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
//! \date April 4, 2012
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/Time.hpp>

#include <ibeo/common/logging/logging.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//! \class IbeoDataHeader
//! \brief Header for all ibeo messages/DataBlock sent via TCP/IP or stored in a
//!        IDC file.
//! \date Apr 24, 2012
//!
//! The IbeoDataHeader is a uniform block of meta data that is prepended by the
//! IbeoSDK to all kinds of DataBlock at external communication as TCP/IP and
//! file output.
//!
//! The data of IbeoDataHeader are related to the DataBlock, as DataType,
//! size and origin.
//!
//! The size of the previous message allows faster file navigation.
//!
//! And finally the timestamp says when the message (header) was generated/sent.
//------------------------------------------------------------------------------
class IbeoDataHeader
{
public: // construtor/destructor
    //========================================
    //! \brief Default constructor.
    //!
    //! Creates an invalid IbeoDataHeader.
    //----------------------------------------
    IbeoDataHeader();

    //========================================
    //! \brief Constructor.
    //! \param[in] dataType           DataType of the DataBlock
    //!                               this header is for.
    //! \param[in] sizeOfPrevMessage  In a stream of DataBlocks,
    //!                               this is the size of the
    //!                               previous DataBlock
    //!                               (without the header).
    //! \param[in] sizeOfThisMessage  The size of the DataBlock
    //!                               this header is for.
    //! \param[in] deviceId           Id of the device which is
    //!                               the source of this message.
    //! \param[in] ntpTime            Timestamp of this header
    //!                               (not the DataBlock).
    //----------------------------------------
    IbeoDataHeader(const DataTypeId dataType,
                   const uint32_t sizeOfPrevMessage,
                   const uint32_t sizeOfThisMessage,
                   const uint8_t deviceId,
                   const NTPTime ntpTime);

    //========================================
    //! \brief Destructor. Does nothing special.
    //----------------------------------------
    virtual ~IbeoDataHeader();

public:
    //========================================
    //! \brief Parse a stream and fill the attributes of this IbeoDataHeader.
    //!
    //! Before reading the data from the stream the #magicWord
    //! will be searched. Only after reading the #magicWord, the
    //! data will be deserialized.
    //!
    //! \param[in, out] is  Stream to read the data from.
    //!                     On output the read pointer will
    //!                     point to the first byte behind
    //!                     the last byte belongs to the
    //!                     IbeoDataHeader serialization.
    //! \return Whether the deserialization was successful.
    //! \retval true The deserialization was successful.
    //! \retval false Either no #magicWord has been found or
    //!               the method failed to read enough bytes
    //!               from the stream needed for the deserialization.
    //----------------------------------------
    virtual bool deserialize(std::istream& is);

    //========================================
    //! \brief Write a serialization of this IbeoDataHeader into the
    //!        output stream \a os.
    //! \param[in, out] os  Stream to write the serialization of
    //!                     this IbeoDataHeader to.
    //! \return Whether the serialization was successful.
    //----------------------------------------
    virtual bool serialize(std::ostream& os) const;

    //bool serialize(char*& target) const;
    //bool deserialize(const char*& buffer);

    //========================================
    //! \brief Get the serialized size of the IbeoDataHeader.
    //! \return  Number of bytes used for the serialization.
    //----------------------------------------
    virtual std::streamsize getSerializedSize() const { return getHeaderSize(); }

public:
    //========================================
    //! \brief Gobbles all byte from the stream before the
    //!        next IbeoDataHeader#magicWord.
    //! \param[in, out] is  The stream where to find the
    //!                     #magicWord in. If a #magicWord
    //!                     has been found, on exit the first
    //!                     4 bytes in the stream will be the
    //!                     #magicWord.
    //! \return Whether a #magicWord has been found.
    //----------------------------------------
    static bool moveToMagicWord(std::istream& is);

public: // getter
    //========================================
    //! \brief Get the DataType of the associated
    //!        DataBlock.
    //! \return The DataType of the associated
    //!         DataBlock.
    //----------------------------------------
    DataTypeId getDataType() const { return m_dataType; }

    //========================================
    //! \brief Get the id of the source device of
    //!        the associated DataBlock.
    //! \return The id of the source device of
    //!         the associated DataBlock.
    //----------------------------------------
    uint8_t getDeviceId() const { return m_deviceId; }

    //========================================
    //! \brief Get the size of serialization of the
    //!        associated DataBlock.
    //! \return The size of serialization of the
    //!         associated DataBlock.
    //----------------------------------------
    uint32_t getMessageSize() const { return m_sizeOfThisMessage; }

    //========================================
    //! \brief Get the size of serialization of the
    //!        previous DataBlock.
    //! \return The size of serialization of the
    //!         previous DataBlock.
    //----------------------------------------
    uint32_t getPreviousMessageSize() const { return m_sizeOfPrevMessage; }

    //========================================
    //! \brief Get the timestamp of this IbeoDataHeader.
    //! \return The timestamp of this IbeoDataHeader.
    //----------------------------------------
    NTPTime getTimestamp() const { return m_ntpTime; }

public: // setter
    //========================================
    //! \brief Set the DataType of the associated
    //!        DataBlock.
    //! \param[in] dataType  The new dataType of the
    //!                      associated DataBlock.
    //----------------------------------------
    void setDataType(const DataTypeId dataType) { m_dataType = dataType; }

    //========================================
    //! \brief Set the id of the source device
    //!        of the associated DataBlock.
    //! \param[in] deviceId  The new id of the source device
    //!                      of the associated DataBlock.
    //----------------------------------------
    void setDeviceId(const uint8_t deviceId) { m_deviceId = deviceId; }

    //========================================
    //! \brief Set the size of the associated
    //!        DataBlock.
    //! \param[in] sizeOfThisMessage  The new size of the
    //!                               associated DataBlock.
    //----------------------------------------
    void setMessageSize(const uint32_t sizeOfThisMessage) { m_sizeOfThisMessage = sizeOfThisMessage; }

    //========================================
    //! \brief Set the size of the previous
    //!        DataBlock.
    //! \param[in] sizeOfPreviousMessage  The new  size of the
    //!                                   previous DataBlock.
    //----------------------------------------
    void setPreviousMessageSize(const uint32_t sizeOfPreviousMessage) { m_sizeOfPrevMessage = sizeOfPreviousMessage; }

    //========================================
    //! \brief Set the timestamp of the IbeoDataHeader.
    //! \param[in] ntpTime  The new timestamp of the
    //!                     IbeoDataHeader.
    //----------------------------------------
    void setTimestamp(const NTPTime ntpTime) { m_ntpTime = ntpTime; }

public:
    //========================================
    //! \brief Get the serialized size of an IbeoDataHeader.
    //! \return The number of bytes used by the
    //!         serialization of IbeoDataHeader.
    //----------------------------------------
    static uint8_t getHeaderSize() { return 24; }

private:
    //========================================
    //! \brief Gobbles all bytes from the input stream
    //!        till the magic word 0xAFFEC0C2 (big endian)
    //!        has been found.
    //!
    //! The stream will be read until the magic word has
    //! been read. In case the magic word has been read
    //! \c a true will be returned. The read position in
    //! the stream is behind the magic word.
    //!
    //! \param[in, out ] is  Stream to look in for the
    //!                      magic word. On exit this
    //!                      stream will be empty if no
    //!                      magic word has been found
    //!                      or the read position will
    //!                      be behind the magic word.
    //!
    //! \return Whether the magicWord has been read.
    //----------------------------------------
    static bool findMagicWord(std::istream& is);

public:
    //========================================
    //! \brief 4 bytes that prepends the other
    //!        attributes of the IbeoDataHeader.
    //----------------------------------------
    static const uint32_t magicWord;

private:
    static constexpr const char* loggerId = "ibeo::common::sdk::IbeoDataHeader";
    static ibeo::common::logging::LoggerSPtr logger;

private: // attributes
    // uint32_t MagicWord = 0xAFFEC0C2
    //========================================
    //! \brief Number of bytes in the previous message.
    //----------------------------------------
    uint32_t m_sizeOfPrevMessage;

    //========================================
    //! \brief Number of bytes used by the
    //!        Serialization of the associated
    //!        DataBlock.
    //----------------------------------------
    uint32_t m_sizeOfThisMessage;

    // uint8_t reserved

    //========================================
    //! \brief Id of the source of the associated
    //!        DataBlock
    //----------------------------------------
    uint8_t m_deviceId;

    //========================================
    //! \brief DataType of the associated DataBlock.
    //----------------------------------------
    DataTypeId m_dataType; // serialized as uint16_t

    //========================================
    //! \brief Timestamp of the IbeoDataHeader.
    //----------------------------------------
    NTPTime m_ntpTime;
}; // IbeoDataHeader

//==============================================================================

//==============================================================================
//! \brief Equal predicate for IbeoDataHeader.
//! \return \c true if \a lhs and \a rhs are equal.
//!         \c false otherwise.
//! \sa compareIbeoDataHeaderWithoutDate(const IbeoDataHeader& lhs, const IbeoDataHeader& rhs)
//------------------------------------------------------------------------------
bool operator==(const IbeoDataHeader& lhs, const IbeoDataHeader& rhs);

//==============================================================================
//! \brief Inqual predicate for IbeoDataHeader.
//! \return \c true if \a lhs and \a rhs are inequal.
//!         \c false otherwise.
//------------------------------------------------------------------------------
bool operator!=(const IbeoDataHeader& lhs, const IbeoDataHeader& rhs);

//==============================================================================
//! \brief Equal predicate for IbeoDataHeader omitting the timestamp entry.
//! \return \c true if \a lhs and \a rhs are equal (without timestamp)
//!         \c false otherwise.
//! \sa operator==(const IbeoDataHeader& lhs, const IbeoDataHeader& rhs)
//------------------------------------------------------------------------------
bool compareIbeoDataHeaderWithoutDate(const IbeoDataHeader& lhs, const IbeoDataHeader& rhs);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
