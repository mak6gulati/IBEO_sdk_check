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
//!\date Aug 22, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/devices/IdcIStream.hpp>
#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ibeo::common::logging::LoggerSPtr IdcIStream::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

IdcIStream::IStreamWrapper::IStreamWrapper(std::istream& is) : m_is(is), m_isFile(false) {}

//==============================================================================

IdcIStream::IStreamWrapper::IStreamWrapper(const std::string& filename) : m_is(m_fs), m_isFile(true)
{
    m_fs.open(filename.c_str(), std::fstream::in | std::fstream::binary);
}

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

IdcIStream::IdcIStream(std::istream& is) : m_strw(is) {}

//==============================================================================

IdcIStream::IdcIStream(const std::string& filename) : m_strw(filename), m_filename(filename) {}

//==============================================================================

std::shared_ptr<char> IdcIStream::getNextDataBlockRaw(IbeoDataHeader& dh)
{
    std::shared_ptr<char> buf;
    if (!isOpen())
    {
        return buf; // nullptr
    }

    if (!dh.deserialize(m_strw()))
    {
        return buf; // nullptr
    }

    buf.reset(new char[dh.getMessageSize()], std::default_delete<char[]>());
    m_strw().read(buf.get(), dh.getMessageSize());
    if (m_strw().fail())
    {
        LOGERROR(logger, "Failed to read data type 0x" << std::hex << dh.getDataType() << std::dec);
        buf.reset();
    }

    return buf;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
