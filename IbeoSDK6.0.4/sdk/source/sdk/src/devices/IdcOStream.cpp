//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Aug 22, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/devices/IdcOStream.hpp>

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130Exporter6130.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

IdcOStream::OStreamWrapper::OStreamWrapper(std::ostream& os) : m_os(os), m_isFile(false) {}

//==============================================================================

IdcOStream::OStreamWrapper::OStreamWrapper(const std::string& filename) : m_os(m_fs), m_isFile(true)
{
    m_fs.open(filename.c_str(), std::fstream::out | std::fstream::binary);
}

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

ibeo::common::sdk::FramingPolicyIn6130 IdcOStream::getDefaultFramingPolicy()
{
    ibeo::common::sdk::FramingPolicyIn6130::TriggerSet triggers;
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2205,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    //triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2202, ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2208,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2209,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2310,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_IdcTrailer6120,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));

    ibeo::common::sdk::FramingPolicyIn6130 policy;
    policy.setTriggerInNewFrame(true);
    policy.setTriggers(triggers);

    return policy;
}

//==============================================================================

IdcOStream::IdcOStream(const std::string& filename) : IdcOStream{filename, getDefaultFramingPolicy()} {}

//==============================================================================

IdcOStream::IdcOStream(const std::string& filename, const ibeo::common::sdk::FramingPolicyIn6130& policy)
  : m_strw{filename}, m_filename{filename}
{
    m_frameIndex.setFramingPolicy(policy);
    m_frameIndex.clearFrames();
}

//==============================================================================

IdcOStream::IdcOStream(std::ostream& os) : IdcOStream{os, getDefaultFramingPolicy()} {}

//==============================================================================

IdcOStream::IdcOStream(std::ostream& os, const ibeo::common::sdk::FramingPolicyIn6130& policy)
  : m_strw{os}, m_filename{}
{
    m_frameIndex.setFramingPolicy(policy);
    m_frameIndex.clearFrames();
}

//==============================================================================

IdcOStream::~IdcOStream() { close(); }

//==============================================================================

void IdcOStream::close()
{
    if (!this->isOpen())
    {
        return;
    }

    FrameIndex6130Exporter6130 fiExporter;
    IbeoDataHeader frameIndexHeader(DataTypeId::DataType_FrameIndex6130,
                                    m_latestMsgSize,
                                    uint32_t(fiExporter.getSerializedSize(m_frameIndex)),
                                    FramingPolicyIn6130::deviceIdAny,
                                    m_latestHeaderTimestamp);
    this->writeHeader(frameIndexHeader);

    fiExporter.serialize(m_strw(), m_frameIndex);

    IbeoDataHeader trailerHeader(DataTypeId::DataType_IdcTrailer6120,
                                 m_latestMsgSize,
                                 0,
                                 FramingPolicyIn6130::deviceIdAny,
                                 m_latestHeaderTimestamp);
    this->writeHeader(trailerHeader);
}

//==============================================================================

bool IdcOStream::write(const IbeoDataHeader& dh, const char* const body)
{
    if (!isOpen())
    {
        return false;
    }

    const bool headerOk = writeHeader(dh);

    if (headerOk)
    {
        return write(body, dh.getMessageSize());
    }
    return false;
}

//==============================================================================
// DEPRECATED
bool IdcOStream::write(const IbeoDataHeader& dh, const DataBlock* const db)
{
    if (!isOpen())
    {
        return false;
    }

    const bool headerOk = writeHeader(dh);

    if (headerOk)
    {
        return db->serialize(m_strw());
    }
    return false;
}

//==============================================================================

bool IdcOStream::write(IbeoDataHeader dh, const DataContainerBase& c, const ExporterBase& exporter)
{
    if (!isOpen())
    {
        return false;
    }

    dh.setDataType(exporter.getDataType());
    dh.setMessageSize(static_cast<uint32_t>(exporter.getSerializedSize(c)));

    const bool headerOk = writeHeader(dh);
    if (headerOk)
    {
        return exporter.serialize(m_strw(), c);
    }
    return false;
}

//==============================================================================

bool IdcOStream::writeHeader(IbeoDataHeader dh)
{
    if (!this->isOpen())
    {
        return false;
    }

    if (m_firstHeaderTimestamp == NTPTime())
    {
        m_firstHeaderTimestamp = dh.getTimestamp();
    }

    if (!m_firstDataBlockToBeWritten)
    {
        dh.setPreviousMessageSize(m_latestMsgSize);
    }
    else
    {
        dh.setPreviousMessageSize(0);
        m_firstDataBlockToBeWritten = false;
    }

    // update frame index if necessary
    if (m_frameIndex.getFramingPolicy().isTrigger(dh.getDataType(), dh.getDeviceId()))
    {
        // add the frame before the header is written
        const uint64_t frameOffsetMs = (dh.getTimestamp() - m_firstHeaderTimestamp).getMilliseconds();

        ibeo::common::sdk::FrameIndexEntryIn6130 entry(
            uint64_t(streamposToInt64(m_strw().tellp())), frameOffsetMs, dh.getDeviceId());
        m_frameIndex.addFrame(entry);
    }

    if (dh.serialize(m_strw()))
    {
        m_latestHeaderTimestamp = dh.getTimestamp();
        m_latestMsgSize         = dh.getMessageSize();
        return true;
    }
    else
    {
        return false;
    }
}

//==============================================================================

bool IdcOStream::write(const char* const data, const uint32_t length)
{
    if (!this->isOpen())
    {
        return false;
    }
    m_strw().write(data, length);

    return isGood();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
