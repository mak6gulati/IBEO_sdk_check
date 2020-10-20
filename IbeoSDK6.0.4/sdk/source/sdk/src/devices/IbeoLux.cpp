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

#include <ibeo/common/sdk/devices/IbeoLux.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

IbeoLux::IbeoLux(const std::string& ip, const unsigned short port) : IbeoTcpDevice(ip, port) {}

//==============================================================================

IbeoLux::~IbeoLux() { this->disconnect(); }

//==============================================================================

statuscodes::Codes IbeoLux::sendCommand(const LuxCommandCBase& cmd, const SpecialExporterBase<CommandCBase>& exporter)
{
    return IbeoTcpDevice::sendCommand(cmd, exporter);
}

//==============================================================================

statuscodes::Codes IbeoLux::sendCommand(const LuxCommandCBase& cmd,
                                        const SpecialExporterBase<CommandCBase>& exporter,
                                        LuxCommandReplyBase& reply,
                                        const boost::posix_time::time_duration timeOut)
{
    return IbeoTcpDevice::sendCommand(cmd, exporter, reply, timeOut);
}

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoLux>& getImporterCreatorMap<IbeoLux>()
{
    return ContainerBufferAndImporterProviderGlobal<IbeoLux>::getInstance();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
