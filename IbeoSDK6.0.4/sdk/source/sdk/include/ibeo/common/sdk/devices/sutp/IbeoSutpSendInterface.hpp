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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/logging/logging.hpp>

#include <boost/function.hpp>
#include <boost/asio.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class IbeoSutpSendInterface
{
public:
    using SendingFunction = boost::function<bool(boost::asio::streambuf& outBuff)>;

public:
    IbeoSutpSendInterface(SendingFunction sender);
    virtual ~IbeoSutpSendInterface();

public:
    void send(const IbeoDataHeader& dh, const char* const buffer);
    //	void send(const IbeoDataHeader& dh, std::istream& is);

protected:
    void serializeSutpHeader(std::ostream& os,
                             const uint16_t fragmentId,
                             const uint16_t nbOfFragments,
                             const DataTypeId dtId);

protected:
    static const uint64_t timeOutDurationMs;
    static const int64_t fragmentSize;

    static constexpr const char* loggerId = "ibeo::common::sdk::IbeoSutpSendInterface";
    static ibeo::common::logging::LoggerSPtr logger;

protected:
    SendingFunction m_sending;

    //! sequenceNumber counter for sending SUTP packages
    uint16_t m_segNo;

    //! id of the device that owns this connection
    uint8_t m_deviceId;

    uint32_t m_nbOfSendPackages;

}; // IbeoSutpSendInterface

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
