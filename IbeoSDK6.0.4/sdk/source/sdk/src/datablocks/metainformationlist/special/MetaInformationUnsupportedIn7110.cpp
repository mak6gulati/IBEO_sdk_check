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
//! \date Apr 5, 2016
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationUnsupportedIn7110.hpp>

#include <ibeo/common/sdk/io.hpp>

#include <algorithm>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

bool MetaInformationUnsupportedIn7110::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, m_originalType);
    writeBE(os, m_timeStamp);
    writeBE(os, getSerializedPayloadSize());

    serializePayload(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool MetaInformationUnsupportedIn7110::deserializePayload(std::istream& is, const uint32_t payloadSize)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    m_data.resize(payloadSize);
    if (payloadSize > 0)
    {
        is.read(reinterpret_cast<char*>(&m_data[0]), uint32_t(payloadSize));
    }

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos) == payloadSize && payloadSize == getSerializedPayloadSize());
}

//==============================================================================

bool MetaInformationUnsupportedIn7110::serializePayload(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    os.write(reinterpret_cast<const char*>(&m_data[0]), std::streamsize(m_data.size()));

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedPayloadSize());
}

//==============================================================================

bool MetaInformationUnsupportedIn7110::isEqual(const MetaInformationBaseIn7110& otherBase) const
{
    // Can compare same types only.
    const MetaInformationUnsupportedIn7110* other = dynamic_cast<const MetaInformationUnsupportedIn7110*>(&otherBase);
    assert(other != nullptr);

    return MetaInformationBaseIn7110::isEqual(otherBase) && (this->getOriginalType() == other->getOriginalType())
           && (this->getData() == other->getData());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
