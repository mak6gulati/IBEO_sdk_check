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
//!\date Oct 23, 2015
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/devices/IbeoTrackingBox.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/ecucommands.hpp>

#include <boost/array.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

IbeoTrackingBox::IbeoTrackingBox(const std::string& ip, const unsigned short port) : IbeoTcpDevice(ip, port) {}

//==============================================================================

IbeoTrackingBox::~IbeoTrackingBox() { this->disconnect(); }

//==============================================================================

void IbeoTrackingBox::setDataTypeFilter()
{
    // clear data type filter
    const DataTypeId startRange(DataTypeId::DataType_Unknown);
    const DataTypeId endRange(DataTypeId::DataType_LastId);
    CommandEcuSetFilterC setFilterCmd(startRange, endRange);
    const CommandEcuSetFilter2010Exporter2010 exporter;
    ReplyEcuSetFilter reply;
    this->sendCommand(setFilterCmd, exporter, reply, boost::posix_time::milliseconds(500));
}

//==============================================================================

void IbeoTrackingBox::getConnected(const uint32_t timeoutSec)
{
    IbeoTcpDevice::connect(timeoutSec);
    setDataTypeFilter();
}

//==============================================================================

statuscodes::Codes IbeoTrackingBox::sendCommand(const EcuCommandCBase& cmd,
                                                const SpecialExporterBase<CommandCBase>& exporter)
{
    return IbeoTcpDevice::sendCommand(cmd, exporter);
}

//==============================================================================

statuscodes::Codes IbeoTrackingBox::sendCommand(const EcuCommandCBase& cmd,
                                                const SpecialExporterBase<CommandCBase>& exporter,
                                                EcuCommandReplyBase& reply,
                                                const boost::posix_time::time_duration timeOut)
{
    return IbeoTcpDevice::sendCommand(cmd, exporter, reply, timeOut);
}

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoTrackingBox>& getImporterCreatorMap<IbeoTrackingBox>()
{
    return ContainerBufferAndImporterProviderGlobal<IbeoTrackingBox>::getInstance();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
