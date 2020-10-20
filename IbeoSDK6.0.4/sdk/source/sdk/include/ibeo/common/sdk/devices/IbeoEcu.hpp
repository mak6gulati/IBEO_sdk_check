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
//!\date Apr 24, 2012
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoTcpDevice.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/EcuCommandC.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/EmptyEcuCommandReply.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class IbeoEcu : public IbeoTcpDevice<IbeoEcu>
{
public:
    //========================================
    //!\brief Create an IbeoEcu (connection class).
    //!
    //! This constructor will create an IbeoEcu class object
    //! which will try to connect to an ECU,
    //! using the given IP address and port number.
    //!
    //!\param[in] ip    IP address of the ECU
    //!                  to be connected with.
    //!\param[in] port  Port number for the connection
    //!                  with the scanner.
    //-------------------------------------
    IbeoEcu(const std::string& ip, const unsigned short port = 12002);

    //========================================
    //!\brief Destructor.
    //!
    //! Will disconnect before destruction.
    //-------------------------------------
    virtual ~IbeoEcu();

public:
    //========================================
    //!\brief Establish the connection to the hardware.
    //!
    //! Reimplements IbeoDevice::getConnected. In
    //! addition it will send a setFilter command
    //! to the ECU to make all messages passes its
    //! output filter.
    //!\param[in] timeoutSec set device connection timeout in sec.
    //-------------------------------------
    virtual void getConnected(const uint32_t timeoutSec = IbeoEthDevice::defaultReceiveTimeoutSeconds);

public:
    //========================================
    //!\brief Send a command which expects no reply.
    //!\param[in] cmd  Command to be sent.
    //!\return The result of the operation.
    //-------------------------------------
    virtual statuscodes::Codes sendCommand(const EcuCommandCBase& cmd,
                                           const SpecialExporterBase<CommandCBase>& exporter);

    //========================================
    //!\brief Send a command and wait for a reply.
    //!
    //! The command will be sent. The calling thread
    //! will sleep until a reply has been received
    //! but not longer than the number of milliseconds
    //! given in \a timeOut.
    //!
    //!\param[in]       cmd    Command to be sent.
    //!\param[in, out]  reply  The reply container for
    //!                        the reply to be stored into.
    //!\param[in]       timeOut  Number of milliseconds to
    //!                          wait for a reply.
    //!\return The result of the operation.
    //-------------------------------------
    virtual statuscodes::Codes sendCommand(const EcuCommandCBase& cmd,
                                           const SpecialExporterBase<CommandCBase>& exporter,
                                           EcuCommandReplyBase& reply,
                                           const boost::posix_time::time_duration timeOut
                                           = boost::posix_time::milliseconds(500));

private:
    using IbeoTcpDevice::sendCommand;

    //========================================
    //!\brief setFilter command to the TrackingBox to make all messages passes
    //!       its output filter
    //-------------------------------------
    void setDataTypeFilter();

private:
    ThreadRunner m_filterCommandThread;

}; // IbeoEcu

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoEcu>& getImporterCreatorMap<IbeoEcu>();

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
