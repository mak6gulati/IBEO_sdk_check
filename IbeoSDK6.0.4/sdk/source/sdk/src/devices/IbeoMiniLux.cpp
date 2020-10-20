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
//!
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/devices/IbeoMiniLux.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

IbeoMiniLux::IbeoMiniLux(const std::string& ip, const unsigned short port) : IbeoTcpDevice(ip, port) {}

//==============================================================================

IbeoMiniLux::~IbeoMiniLux() { this->disconnect(); }

//==============================================================================

statuscodes::Codes IbeoMiniLux::sendCommand(const MiniLuxCommandCBase& cmd,
                                            const SpecialExporterBase<CommandCBase>& exporter)
{
    return IbeoTcpDevice::sendCommand(cmd, exporter);
}

//==============================================================================

statuscodes::Codes IbeoMiniLux::sendCommand(const MiniLuxCommandCBase& cmd,
                                            const SpecialExporterBase<CommandCBase>& exporter,
                                            MiniLuxCommandReplyBase& reply,
                                            const boost::posix_time::time_duration timeOut)
{
    return IbeoTcpDevice::sendCommand(cmd, exporter, reply, timeOut);
}

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoMiniLux>& getImporterCreatorMap<IbeoMiniLux>()
{
    return ContainerBufferAndImporterProviderGlobal<IbeoMiniLux>::getInstance();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
