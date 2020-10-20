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

#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/bufferIO.hpp>

#include <iostream>
using namespace std;

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

// static
const uint32_t IbeoDataHeader::magicWord = 0xAFFEC0C2;

ibeo::common::logging::LoggerSPtr IbeoDataHeader::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

IbeoDataHeader::IbeoDataHeader()
  : m_sizeOfPrevMessage(0),
    m_sizeOfThisMessage(0),
    m_deviceId(0),
    m_dataType(DataTypeId::DataType_Unknown),
    m_ntpTime(0)
{}

//==============================================================================

IbeoDataHeader::IbeoDataHeader(const DataTypeId dataType,
                               const uint32_t sizeOfPrevMessage,
                               const uint32_t sizeOfThisMessage,
                               const uint8_t deviceId,
                               const NTPTime ntpTime)
  : m_sizeOfPrevMessage(sizeOfPrevMessage),
    m_sizeOfThisMessage(sizeOfThisMessage),
    m_deviceId(deviceId),
    m_dataType(dataType),
    m_ntpTime(ntpTime)
{}

//==============================================================================

IbeoDataHeader::~IbeoDataHeader() {}

//==============================================================================

bool IbeoDataHeader::deserialize(std::istream& is)
{
    if (!IbeoDataHeader::findMagicWord(is))
        return false;

    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_sizeOfPrevMessage);
    ibeo::common::sdk::readBE(is, m_sizeOfThisMessage);

    uint8_t dummy;
    ibeo::common::sdk::readBE(is, dummy);
    //is.ignore(); // reserved byte

    ibeo::common::sdk::readBE(is, m_deviceId);

    this->m_dataType.readBE(is);

    ibeo::common::sdk::readBE(is, m_ntpTime); // 64 Bit NTP time stamp

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos)
               == this->getSerializedSize() - 4); // adjust because of magic word
}

//==============================================================================

//bool IbeoDataHeader::deserialize(const char*& buffer)
//{
//	const char* startPos = buffer;
//
//	ibeo::common::sdk::readBE(buffer, m_sizeOfPrevMessage);
//	ibeo::common::sdk::readBE(buffer, m_sizeOfThisMessage);
//
//	uint8_t dummy;
//	ibeo::common::sdk::readBE(buffer, dummy);
//	//is.ignore(); // reserved byte
//
//	ibeo::common::sdk::readBE(buffer, m_deviceId);
//
//	this->m_dataType.readBE(buffer);
//
//	ibeo::common::sdk::readBE(buffer, m_ntpTime); // 64 Bit NTP time stamp
//
//	return ((buffer - startPos) == this->getSerializedSize()-4) // adjust because of magic word
//		&& this->m_dataType != DataTypeId::DataType_Unknown;
//}

//==============================================================================

bool IbeoDataHeader::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, magicWord);
    ibeo::common::sdk::writeBE(os, this->m_sizeOfPrevMessage);
    ibeo::common::sdk::writeBE(os, this->m_sizeOfThisMessage);
    const char res1 = 0;
    ibeo::common::sdk::writeBE(os, res1);
    ibeo::common::sdk::writeBE(os, this->m_deviceId);
    this->m_dataType.writeBE(os);
    //	ibeo::common::sdk::writeBE(os, uint16_t(this->m_dataType));
    ibeo::common::sdk::writeBE(os, this->m_ntpTime);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

//bool IbeoDataHeader::serialize(char*& target) const
//{
//	const char* startPos = target;
//
//	ibeo::common::sdk::writeBE(target, magicWord);
//	ibeo::common::sdk::writeBE(target, this->m_sizeOfPrevMessage);
//	ibeo::common::sdk::writeBE(target, this->m_sizeOfThisMessage);
//	const char res1 = 0;
//	ibeo::common::sdk::writeBE(target, res1);
//	ibeo::common::sdk::writeBE(target, this->m_deviceId);
//	this->m_dataType.writeBE(target);
////	ibeo::common::sdk::writeBE(os, uint16_t(this->m_dataType));
//	ibeo::common::sdk::writeBE(target, this->m_ntpTime);
//
//	return ((target - startPos) == this->getSerializedSize());
//}

//==============================================================================

bool IbeoDataHeader::findMagicWord(std::istream& is)
{
    if (is.bad() || is.eof())
        return false;

    uint32_t nMagicWord  = 0;
    int nbOfSkippedBytes = -4;
    char cByte;

    // Read bytes from input stream until the next magic word is found
    while (nMagicWord != 0xAFFEC0C2)
    {
        // Note that the right-hand side of the &&-operator is evaluated
        // only if the left-hand side is true, i.e. is.get() will be
        // called only if the magic word is incorrect.
        ++nbOfSkippedBytes;
        is >> cByte;
        if (!is.good())
        {
            return false;
        }
        //std::cerr << " " << toHex(cByte) << dec;

        // By definition, header data have network byte order (Big Endian),
        // i.e. the high byte of the magic word is received first. Therefore
        // we must shift the received byte from the LSB side into the magic
        // word m_uVersion.
        nMagicWord <<= 8;
        nMagicWord |= cByte & 0x000000FF;
    }
    //	std::cerr << endl;

    if (nbOfSkippedBytes > 0)
    {
        LOGWARNING(logger, nbOfSkippedBytes << " Bytes skipped");
    }

    return true;
}

//==============================================================================

bool IbeoDataHeader::moveToMagicWord(std::istream& is)
{
    if (IbeoDataHeader::findMagicWord(is))
    {
        is.putback(char(0xc2));
        is.putback(char(0xc0));
        is.putback(char(0xfe));
        is.putback(char(0xaf));
        return true;
    }
    return false;
}

//==============================================================================

bool operator==(const IbeoDataHeader& lhs, const IbeoDataHeader& rhs)
{
    if (lhs.getPreviousMessageSize() != rhs.getPreviousMessageSize())
        return false;

    if (lhs.getMessageSize() != rhs.getMessageSize())
        return false;

    if (lhs.getDeviceId() != rhs.getDeviceId())
        return false;

    if (lhs.getDataType() != rhs.getDataType())
        return false;

    if (lhs.getTimestamp() != rhs.getTimestamp())
        return false;

    return true;
}

//==============================================================================

bool operator!=(const IbeoDataHeader& lhs, const IbeoDataHeader& rhs) { return !(lhs == rhs); }

//==============================================================================

bool compareIbeoDataHeaderWithoutDate(const IbeoDataHeader& lhs, const IbeoDataHeader& rhs)
{
    if (lhs.getPreviousMessageSize() != rhs.getPreviousMessageSize())
        return false;

    if (lhs.getMessageSize() != rhs.getMessageSize())
        return false;

    if (lhs.getDeviceId() != rhs.getDeviceId())
        return false;

    if (lhs.getDataType() != rhs.getDataType())
        return false;

    return true;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
