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
//! \date May 3, 2017
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/devices/sutp/IbeoSutpSendInterface.hpp>
#include <ibeo/common/sdk/devices/sutp/SutpHeader.hpp>
#include <ibeo/common/sdk/Time.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

const uint64_t IbeoSutpSendInterface::timeOutDurationMs = 800;
const int64_t IbeoSutpSendInterface::fragmentSize       = 8024;

//==============================================================================

ibeo::common::logging::LoggerSPtr IbeoSutpSendInterface::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

IbeoSutpSendInterface::IbeoSutpSendInterface(SendingFunction sender)
  : m_sending(sender), m_segNo(0U), m_deviceId(0U), m_nbOfSendPackages(0U)
{}

//==============================================================================

IbeoSutpSendInterface::~IbeoSutpSendInterface() { LOGINFO(logger, m_nbOfSendPackages << " send packages"); }

//==============================================================================

void IbeoSutpSendInterface::serializeSutpHeader(std::ostream& os,
                                                const uint16_t fragmentId,
                                                const uint16_t nbOfFragments,
                                                const DataTypeId dtId)
{
    const boost::posix_time::time_duration recvTime = time::universalTime().time_of_day();
    const uint64_t timeStamp
        = uint64_t(uint64_t(uint64_t(recvTime.total_seconds()) << 32) | uint32_t(recvTime.fractional_seconds()));

    const SutpHeader shd(timeStamp,
                         static_cast<uint16_t>(SutpHeader::ProtocolVersion::Version_01),
                         m_segNo++,
                         uint8_t(0U),
                         m_deviceId,
                         dtId,
                         uint16_t(06655),
                         uint16_t(0xffff),
                         nbOfFragments,
                         uint16_t(fragmentId + 1));

    shd.serialize(os);
}

//==============================================================================

void IbeoSutpSendInterface::send(const IbeoDataHeader& dh, const char* const dataPayloadBuffer)
{
    if (!m_sending)
    {
        LOGERROR(logger, "No sending function declared");
        return;
    }
    const uint16_t sutpOverheadPerFragment          = uint16_t(SutpHeader::getSerializedSize_Static());
    const int64_t totalDatatypePayloadSize          = dh.getMessageSize() + IbeoDataHeader::getHeaderSize();
    const int64_t maxDataTypePayloadSizePerFragment = fragmentSize - sutpOverheadPerFragment;
    const uint16_t nbOfFragments
        = uint16_t(std::ceil(float(totalDatatypePayloadSize) / float(maxDataTypePayloadSizePerFragment)));
    const int64_t totalUdpPayloadSize = (nbOfFragments * sutpOverheadPerFragment) + totalDatatypePayloadSize;

    std::stringstream stream;
    stream << std::endl
           << "DataBlock: " << toHex(dh.getDataType()) << "  size: " << dh.getMessageSize() << std::endl
           << "totalPayloadSize: " << totalDatatypePayloadSize << std::endl
           << "maxPayloadSize: " << maxDataTypePayloadSizePerFragment << std::endl
           << "nbOfFragments: " << nbOfFragments << std::endl
           << "totalSize: " << totalUdpPayloadSize;
    LOGINFO(logger, stream.str());

    // Create output buffer and write
    boost::asio::streambuf outBuf;
    std::ostream os(&outBuf);

    int64_t remainingDatatypePayloadSize = totalDatatypePayloadSize;
    //int64_t remainingUtpPayloadSize = totalUdpPayloadSize;
    const char* nextDatatypePayloadByte = dataPayloadBuffer;

    for (uint16_t fragIdx = 0; fragIdx < nbOfFragments; ++fragIdx)
    {
        serializeSutpHeader(os, fragIdx, nbOfFragments, dh.getDataType());
        //remainingDatatypePayloadSize -= sutpOverheadPerFragment;

        int64_t remainingFrameDatatypePayloadSize = maxDataTypePayloadSizePerFragment;
        if (fragIdx == 0)
        {
            dh.serialize(os);
            remainingFrameDatatypePayloadSize -= IbeoDataHeader::getHeaderSize();
        }

        const int64_t datatypePayloadOfThisFrame
            = std::min(remainingFrameDatatypePayloadSize, remainingDatatypePayloadSize);
        os.write(nextDatatypePayloadByte, datatypePayloadOfThisFrame);
        nextDatatypePayloadByte += datatypePayloadOfThisFrame;
        remainingDatatypePayloadSize -= datatypePayloadOfThisFrame;
        //remainingUtpPayloadSize -= datatypePayloadOfThisFrame + sutpOverheadPerFragment;

        m_sending(outBuf);
        ++m_nbOfSendPackages;
        outBuf.consume(2 * fragmentSize);
    }
}

//==============================================================================

//void IbeoSutpSendInterface::send(const IbeoDataHeader& dh, std::istream& is)
//{
//	if (!m_sending) {
//		LOGERROR(logger, "No sending function declared");
//		return;
//	}
//	const int64_t totalPayloadSize = dh.getMessageSize() + IbeoDataHeader::getHeaderSize();
//	const int64_t maxPayloadSize = fragmentSize - SutpHeader::getSerializedSize_Static();
//	const uint16_t nbOfFragments = uint16_t(std::ceil(float(totalPayloadSize)/float(maxPayloadSize))); // is this save?
//	const int64_t totalSize = (nbOfFragments * SutpHeader::getSerializedSize_Static()) + totalPayloadSize;
//
//	// Create output buffer and write
//	boost::asio::streambuf outBuf;
//	std::ostream os(&outBuf);
//
//	int64_t remainingPayloadSize = totalPayloadSize;
//	int64_t remainingTotalSize = totalSize;
//
//	for (uint16_t f = 0; f < nbOfFragments; ++f) {
//		SutpHeader shd;
//
//		shd.setDatatype(dh.getDataType());
//		shd.setFlags(uint8_t(0U));
//		shd.setFragNo(uint16_t(f+1));
//		shd.setFragsTotal(nbOfFragments);
//		shd.setFwVersion(uint16_t(06655));
//		shd.setScanNo(uint16_t(0xffff));
//		shd.setScannerId(m_deviceId);
//		shd.setSeqNo(m_segNo++);
//
//		const boost::posix_time::time_duration recvTime = time::universalTime().time_of_day();
//		uint64_t timeStamp = uint32_t(recvTime.total_seconds());
//		timeStamp = timeStamp << 32;
//		timeStamp |= uint32_t(recvTime.fractional_seconds());
//		shd.setTimestamp(timeStamp);
//		shd.setVersion(SutpHeader::Version_01);
//
//		int64_t remainingFramePayloadSize = maxPayloadSize;
//		if (f==0) {
//			dh.serialize(os);
//			remainingFramePayloadSize -= IbeoDataHeader::getHeaderSize();
//		}
//
//		const int64_t payloadOfThisFrame = std::min(remainingFramePayloadSize, remainingPayloadSize);
//
//		// C++98
//		char* copyBuffer = new char[payloadOfThisFrame];
//		is.read(copyBuffer, payloadOfThisFrame);
//		os.write(copyBuffer, payloadOfThisFrame);
//		delete[] copyBuffer;
//		// C++11 ???
//		//std::copy_n(istreambuf_iterator<char>(is), payloadOfThisFrame, ostreambuf_iterator<char>(os));
//		remainingPayloadSize -= payloadOfThisFrame;
//		remainingTotalSize -= payloadOfThisFrame + SutpHeader::getSerializedSize_Static();
//
//		m_sending(outBuf);
//		outBuf.consume(maxPayloadSize + SutpHeader::getSerializedSize_Static());
//	}
//
//}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
