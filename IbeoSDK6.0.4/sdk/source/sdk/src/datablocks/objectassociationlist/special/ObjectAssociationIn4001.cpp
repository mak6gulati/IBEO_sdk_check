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
//! \date Apr 26, 2016
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectassociationlist/special/ObjectAssociationIn4001.hpp>

#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

bool ObjectAssociationIn4001::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_refObjId);
    ibeo::common::sdk::readBE(is, m_dutObjId);
    ibeo::common::sdk::readBE(is, m_timestampFirst);
    ibeo::common::sdk::readBE(is, m_timestampLast);
    ibeo::common::sdk::readBE(is, m_certainty);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ObjectAssociationIn4001::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_refObjId);
    ibeo::common::sdk::writeBE(os, m_dutObjId);
    ibeo::common::sdk::writeBE(os, m_timestampFirst);
    ibeo::common::sdk::writeBE(os, m_timestampLast);
    ibeo::common::sdk::writeBE(os, m_certainty);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
