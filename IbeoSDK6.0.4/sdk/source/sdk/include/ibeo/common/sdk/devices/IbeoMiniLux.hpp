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
//!\date Oct 04, 2013
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoTcpDevice.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/miniluxcommands.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
//!\brief Class to connect to a MiniLux sensor.
//!\date Oct 1, 2013
//------------------------------------------------------------------------------
class IbeoMiniLux : public IbeoTcpDevice<IbeoMiniLux>
{
public:
    //========================================
    //!\brief Create an IbeoMiniLux (connection class).
    //!
    //! This constructor will create an IbeoMiniLux class object
    //! which will try to connect to a MiniLux sensor,
    //! using the given IP address and port number.
    //!
    //! \param[in] ip    IP address of the scanner
    //!                  to be connected with.
    //! \param[in] port  Port number for the connection
    //!                  with the scanner.
    //----------------------------------------
    IbeoMiniLux(const std::string& ip, const unsigned short port = 12006);

    //========================================
    //!\brief Destructor.
    //!
    //! Will disconnect before destruction.
    //----------------------------------------
    virtual ~IbeoMiniLux();

public:
    //========================================
    //!\brief Send a command which expects no reply.
    //! \param[in] cmd  Command to be sent.
    //! \return The result of the operation.
    //----------------------------------------
    virtual statuscodes::Codes sendCommand(const MiniLuxCommandCBase& cmd,
                                           const SpecialExporterBase<CommandCBase>& exporter);

    //========================================
    //!\brief Send a command and wait for a reply.
    //!
    //! The command will be sent. The calling thread
    //! will sleep until a reply has been received
    //! but not longer than the number of milliseconds
    //! given in \a timeOut.
    //!
    //! \param[in]       cmd    Command to be sent.
    //! \param[in, out]  reply  The reply container for
    //!                         the reply to be stored into.
    //! \param[in]       timeOut  Number of milliseconds to
    //!                           wait for a reply.
    //! \return The result of the operation.
    //----------------------------------------
    virtual statuscodes::Codes sendCommand(const MiniLuxCommandCBase& cmd,
                                           const SpecialExporterBase<CommandCBase>& exporter,
                                           MiniLuxCommandReplyBase& reply,
                                           const boost::posix_time::time_duration timeOut
                                           = boost::posix_time::milliseconds(500));

private:
    using IbeoTcpDevice::sendCommand;
}; // IbeoMiniLux

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoMiniLux>& getImporterCreatorMap<IbeoMiniLux>();

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
