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
//!\date July 20, 2017
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/devices/IbeoEthDevice.hpp>

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

IbeoEthDevice::~IbeoEthDevice()
{
    {
        Lock lock(m_mutex);
        m_threadState = ThreadState::NotRunning;
    }

    if (m_receiveThread)
    {
        m_receiveThread->stop();
        delete m_receiveThread;
        m_receiveThread = nullptr;
    }
}

//==============================================================================

void IbeoEthDevice::receivedDataBlock(const IbeoDataHeader* dh, const char* bodyBuf)
{
    LOGTRACE(m_logger, "Received " << toHex(dh->getDataType()));

    if (!m_streamers.empty())
    {
        // Message has been completely received. So, we can notify all streamers
        notifyStreamers(*dh, bodyBuf);
    }

    //	if (dh->getDataType() == DataTypeId::DataType_VehicleStateBasic2805) {
    //		LOGTRACE(m_logger, "Dummy"); // for debugging
    //	}

    if (!m_registeredContainerListeners.empty())
    {
        auto cllmIter = m_registeredContainerListeners.find(dh->getDataType());
        if (cllmIter != m_registeredContainerListeners.end())
        {
            ContainerListenerListMap& cllm = cllmIter->second;

            for (auto& containerTypeIter : cllm)
            {
                auto containerHashId = containerTypeIter.first.second;

                boost::iostreams::stream<boost::iostreams::array_source> strm(bodyBuf, dh->getMessageSize());
                ImporterBase* importer;
                const DataContainerBase* const container = onData(*dh, strm, containerHashId, importer);
                notifyContainerListeners(container, importer);
            }
        }
    }

    if ((!m_listeners.empty()) && (m_listeners.find(dh->getDataType()) != m_listeners.end()))
    {
        // Message has been completely received. So, we can parse it and notify all clients
        boost::iostreams::stream<boost::iostreams::array_source> strm(bodyBuf, dh->getMessageSize());
        notifyListeners(onData(*dh, strm));
    }
}

//==============================================================================

void IbeoEthDevice::connect(const uint32_t timeoutSec)
{
    m_recvTimeoutSeconds = timeoutSec;

    m_receiveThread->setExpiryTime(boost::posix_time::seconds(m_recvTimeoutSeconds));
    m_receiveThread->run();
    m_threadState = ThreadState::Running;
}

//==============================================================================

void IbeoEthDevice::disconnect()
{
    IbeoDeviceBase::disconnect();
    try
    {
        Lock lock(m_mutex);
        m_threadState = ThreadState::NotRunning;
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(m_logger, e.what());
    }

    if (m_receiveThread)
    {
        m_receiveThread->stop();
        delete m_receiveThread;
        m_receiveThread = nullptr;
    }
}

//==============================================================================

bool IbeoEthDevice::isConnected() const
{
    if (!isRunning())
    {
        // Not running -> not connected.
        return false;
    }
    else
    {
        return m_receiveThread->isConnected();
    }
}

//==============================================================================

bool IbeoEthDevice::isRunning() const
{
    if (m_receiveThread)
    {
        return m_receiveThread->isRunning();
    }
    else
    {
        // No thread -> not running.
        return false;
    }
}

//==============================================================================

statuscodes::Codes IbeoEthDevice::sendCommand(const CommandCBase& cmd,
                                              const SpecialExporterBase<CommandCBase>& exporter)
{
    if (m_receiveThread && m_receiveThread->isRunning())
    {
        return m_receiveThread->sendCommand(cmd, exporter);
    }
    else
    {
        return statuscodes::SendingCommandFailed;
    }
}

//==============================================================================

statuscodes::Codes IbeoEthDevice::sendCommand(const CommandCBase& cmd,
                                              const SpecialExporterBase<CommandCBase>& exporter,
                                              CommandReplyBase& reply,
                                              const boost::posix_time::time_duration timeOut)
{
    if (m_receiveThread && m_receiveThread->isRunning())
    {
        return m_receiveThread->sendCommand(cmd, exporter, reply, timeOut);
    }
    else
    {
        return statuscodes::SendingCommandFailed;
    }
}

//==============================================================================

void IbeoEthDevice::setRecvTimeoutSeconds(const uint32_t seconds)
{
    m_recvTimeoutSeconds = seconds;
    if (m_receiveThread)
    {
        m_receiveThread->setExpiryTime(boost::posix_time::seconds(m_recvTimeoutSeconds));
    }
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
