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
//! \date Mar 14, 2014
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/MeasurementList.hpp>
#include <ibeo/common/sdk/io.hpp>

#include <boost/bind.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

MeasurementList::MeasurementList() : m_measurements() {}

//==============================================================================

std::streamsize MeasurementList::getSerializedSize() const
{
    std::streamsize result                         = std::streamsize(sizeof(uint16_t));
    std::vector<Measurement>::const_iterator mIter = m_measurements.begin();
    for (; mIter != m_measurements.end(); ++mIter)
    {
        result += mIter->getSerializedSize();
    }
    return result;
}

//==============================================================================

bool MeasurementList::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint16_t size;
    readBE(is, size);
    m_measurements.resize(size);

    std::vector<Measurement>::iterator mIter = m_measurements.begin();
    for (; mIter != m_measurements.end(); ++mIter)
    {
        if (!mIter->deserialize(is))
            return false;
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool MeasurementList::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, uint16_t(m_measurements.size()));
    std::vector<Measurement>::const_iterator mIter = m_measurements.begin();
    for (; mIter != m_measurements.end(); ++mIter)
    {
        if (!mIter->serialize(os))
            return false;
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}
//==============================================================================

MeasurementList::MeasurementVector::iterator MeasurementList::getMeasurement(const MeasurementKey key)
{
    return std::find_if(m_measurements.begin(), m_measurements.end(), boost::bind(&MeasurementKey::compare, _1, key));
}

//==============================================================================

MeasurementList::MeasurementVector::const_iterator MeasurementList::getMeasurement(const MeasurementKey key) const
{
    return std::find_if(m_measurements.begin(), m_measurements.end(), boost::bind(&MeasurementKey::compare, _1, key));
}

//==============================================================================

bool MeasurementList::contains(const MeasurementKey key) const { return getMeasurement(key) != m_measurements.end(); }

//==============================================================================

bool operator==(const MeasurementList& lhs, const MeasurementList& rhs)
{
    return lhs.getMeasurements() == rhs.getMeasurements();
}

//==============================================================================

bool operator!=(const MeasurementList& lhs, const MeasurementList& rhs)
{
    return lhs.getMeasurements() != rhs.getMeasurements();
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
