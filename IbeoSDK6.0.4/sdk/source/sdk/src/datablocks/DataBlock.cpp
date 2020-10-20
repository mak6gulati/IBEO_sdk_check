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
//! \date Apr 25, 2012
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/DataBlock.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

DataBlock::DataBlock() : Concurrency(), m_headerDeviceId(), m_headerNtpTime() {}

//==============================================================================

DataBlock::DataBlock(const DataBlock& other)
  : Concurrency(), m_headerDeviceId(other.m_headerDeviceId), m_headerNtpTime(other.m_headerNtpTime)
{}

//==============================================================================

DataBlock& DataBlock::operator=(const DataBlock& other)
{
    if (this != &other)
    {
        m_headerDeviceId = other.m_headerDeviceId;
        m_headerNtpTime  = other.m_headerNtpTime;
    }
    return *this;
}

//==============================================================================

void DataBlock::setDataHeader(const IbeoDataHeader& dh)
{
    m_headerDeviceId = dh.getDeviceId();
    m_headerNtpTime  = dh.getTimestamp();
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
