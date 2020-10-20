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

#include <ibeo/common/sdk/devices/IbeoEcu.hpp>
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

IbeoEcu::IbeoEcu(const std::string& ip, const unsigned short port)
  : IbeoTcpDevice(ip, port), m_filterCommandThread{boost::bind(&IbeoEcu::setDataTypeFilter, this)}
{}

//==============================================================================

IbeoEcu::~IbeoEcu()
{
    this->m_filterCommandThread.join();
    this->m_filterCommandThread.stop();
    this->disconnect();
}

//==============================================================================

void IbeoEcu::setDataTypeFilter()
{
    this->m_filterCommandThread.setThreadState(ThreadRunner::ThreadState::Running);

    // clear data type filter
    const DataTypeId startRange(DataTypeId::DataType_Unknown);
    const DataTypeId endRange(DataTypeId::DataType_LastId);
    CommandEcuSetFilterC setFilterCmd(startRange, endRange);
    const CommandEcuSetFilter2010Exporter2010 exporter;
    ReplyEcuSetFilter reply;
    this->sendCommand(setFilterCmd, exporter, reply, boost::posix_time::milliseconds(500));
}

//==============================================================================

void IbeoEcu::getConnected(const uint32_t timeoutSec)
{
    IbeoTcpDevice::connect(timeoutSec);
    this->m_filterCommandThread.start();
}

//==============================================================================

statuscodes::Codes IbeoEcu::sendCommand(const EcuCommandCBase& cmd, const SpecialExporterBase<CommandCBase>& exporter)
{
    return IbeoTcpDevice::sendCommand(cmd, exporter);
}

//==============================================================================

statuscodes::Codes IbeoEcu::sendCommand(const EcuCommandCBase& cmd,
                                        const SpecialExporterBase<CommandCBase>& exporter,
                                        EcuCommandReplyBase& reply,
                                        const boost::posix_time::time_duration timeOut)
{
    return IbeoTcpDevice::sendCommand(cmd, exporter, reply, timeOut);
}

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoEcu>& getImporterCreatorMap<IbeoEcu>()
{
    return ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
