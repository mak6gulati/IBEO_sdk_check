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

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationList7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationFactory.hpp>
#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>
#include <ibeo/common/sdk/io.hpp>

#include <boost/bind.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//==============================================================================
//==============================================================================

void MetaInformationList7110::addMetaInformation(const MetaInformationBaseIn7110SPtr info)
{
    if (!info)
        return;

    MetaInformationBaseIn7110::MetaInformationType type = info->getType();
    if (m_metaInformations.find(type) == m_metaInformations.end())
    {
        m_metaInformations[type] = MetaInformationSPtrVector();
    }

    m_metaInformations[type].push_back(info);
}

//==============================================================================

uint32_t MetaInformationList7110::getNumberOfMetaInformationElements() const
{
    MetaInformationMap::size_type size = 0;
    for (const MetaInformationMap::value_type& v : m_metaInformations)
    {
        size += v.second.size();
    }
    return uint32_t(size);
}

//==============================================================================

uint32_t MetaInformationList7110::getNumberOfMetaInformationTypes() const
{
    return uint32_t(m_metaInformations.size());
}

//==============================================================================

void MetaInformationList7110::deleteInformation(const MetaInformationBaseIn7110SPtr& info)
{
    if (!info)
    {
        return;
    }

    if (m_metaInformations.find(info->getType()) == m_metaInformations.end())
    {
        return;
    }

    MetaInformationSPtrVector& vec = m_metaInformations[info->getType()];
    MetaInformationSPtrVector::iterator newAfterEnd
        = std::remove_if(vec.begin(), vec.end(), boost::bind(&MetaInformationList7110::isSame, _1, boost::cref(info)));

    const uint32_t newNbOfElements = uint32_t(newAfterEnd - vec.begin());
    vec.resize(newNbOfElements);
}

//==============================================================================

void MetaInformationList7110::deleteInformationForType(const MetaInformationBaseIn7110::MetaInformationType infoType)
{
    if (m_metaInformations.find(infoType) == m_metaInformations.end())
    {
        return;
    }

    m_metaInformations.erase(infoType);
}

//==============================================================================

void MetaInformationList7110::printStatistic(std::ostream& os) const
{
    for (const MetaInformationMap::value_type& vt : m_metaInformations)
    {
        const MetaInformationSPtrVector& vec = vt.second;

        os << "Key " << std::left << std::setw(30) << vt.first << "  #:" << vec.size() << std::endl;
    } // for each map entry
}

//==============================================================================
//==============================================================================
//==============================================================================

bool MetaInformationList7110::MetaInformationHeader::deserialize(std::istream& is)
{
    uint16_t infoType;
    readBE(is, infoType);
    m_type = static_cast<MetaInformationBaseIn7110::MetaInformationType>(infoType);

    readBE(is, m_timeStamp);
    readBE(is, m_payloadSize);

    return !is.fail();
}

//==============================================================================
//==============================================================================
//==============================================================================

bool operator==(const MetaInformationList7110& lhs, const MetaInformationList7110& rhs)
{
    const MetaInformationList7110::MetaInformationMap& lm = lhs.getMetaInformationMap();
    const MetaInformationList7110::MetaInformationMap& rm = rhs.getMetaInformationMap();

    if (lm.size() != rm.size())
    {
        return false;
    }

    for (const MetaInformationList7110::MetaInformationMap::value_type& lmvt : lm)
    {
        // Search for this type in the other map.
        MetaInformationList7110::MetaInformationMap::const_iterator rmIter = rm.find(lmvt.first);
        if (rmIter == rm.end())
        {
            // Not found -> maps are unequal.
            return false;
        }

        const MetaInformationList7110::MetaInformationSPtrVector& lmipv = lmvt.second;
        const MetaInformationList7110::MetaInformationSPtrVector& rmipv = rmIter->second;

        if (lmipv.size() != rmipv.size())
        {
            // Info vectors of current type have different sizes -> maps are unequal.
            return false;
        }

        // Check if all elements of the left vector are in the right vector.
        for (const MetaInformationBaseIn7110SPtr& li : lmipv)
        {
            bool found = false;
            for (const MetaInformationBaseIn7110SPtr& ri : rmipv)
            {
                if (*li == *ri)
                {
                    found = true;
                    break;
                }
            }

            if (found == false)
            {
                // This info is not in the right vector -> maps are unequal.
                return false;
            }
        }

        // Check if all elements of the right vector are in the left vector.
        for (const MetaInformationBaseIn7110SPtr& ri : rmipv)
        {
            bool found = false;
            for (const MetaInformationBaseIn7110SPtr& li : lmipv)
            {
                if (*li == *ri)
                {
                    found = true;
                    break;
                }
            }

            if (found == false)
            {
                // This info is not in the left vector -> maps are unequal.
                return false;
            }
        }
    }

    // All checks passed -> maps are equal.
    return true;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
