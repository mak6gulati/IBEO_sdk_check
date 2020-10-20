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

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationKeywordsIn7110.hpp>

#include <ibeo/common/sdk/io.hpp>

#include <algorithm>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

void MetaInformationKeywordsIn7110::addKeyword(const std::string& keyword) { m_keywords.insert(keyword); }

//==============================================================================

bool MetaInformationKeywordsIn7110::containsKeyword(const std::string& keyword)
{
    return m_keywords.find(keyword) != m_keywords.end();
}

//==============================================================================

void MetaInformationKeywordsIn7110::deleteKeyword(const std::string& keyword) { m_keywords.erase(keyword); }

//==============================================================================

MetaInformationKeywordsIn7110::StringVector MetaInformationKeywordsIn7110::getKeywordsAsVector() const
{
    std::vector<std::string> ret;
    ret.reserve(m_keywords.size());
    for (const std::string& s : m_keywords)
    {
        ret.push_back(s);
    }

    return ret;
}

//==============================================================================

uint32_t MetaInformationKeywordsIn7110::getSerializedPayloadSize() const
{
    uint32_t sz = 0;

    if (!m_keywords.empty())
    {
        for (const std::string& keyword : m_keywords)
        {
            sz += static_cast<uint32_t>(keyword.size());
        }
        sz += static_cast<uint32_t>(m_keywords.size() - 1); // for ; between the keywords

        if (sz > maxStringLength) // truncation to be applied
        {
            sz = maxStringLength;
        }
    }

    sz += static_cast<uint32_t>(sizeof(uint16_t));

    return sz;
}

//==============================================================================

bool MetaInformationKeywordsIn7110::deserializePayload(std::istream& is, const uint32_t payloadSize)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    m_keywords.clear();

    uint16_t len = 0;
    readBE(is, len);

    // Check that all keywords are deserialized! Especially the last one after the last ';'!
    if (len > 0)
    {
        std::string allKeywords;
        allKeywords.resize(len);
        is.read(&allKeywords[0], len);

        std::istringstream sstream(allKeywords);
        std::string keyword;
        while (getline(sstream, keyword, ';'))
        {
            addKeyword(keyword);
        }
    }

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos) == payloadSize && payloadSize == getSerializedPayloadSize());
}

//==============================================================================

bool MetaInformationKeywordsIn7110::serializePayload(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    if (m_keywords.empty())
    {
        writeBE(os, static_cast<uint16_t>(0));
    }
    else
    {
        // Gather all keywords together into one string separated by a ";".
        StringSet::const_iterator kwIter = m_keywords.begin();
        // First keyword.
        std::string allKeywords(*kwIter);
        ++kwIter;

        // All other keywords with a prepending ";".
        for (; kwIter != m_keywords.end(); ++kwIter)
        {
            allKeywords.append(";");
            allKeywords.append(*kwIter);
        }

        // Truncation needed?
        if (allKeywords.size() > maxStringLength)
        {
            allKeywords.resize(maxStringLength);
        }

        writeBE(os, static_cast<uint16_t>(allKeywords.size()));
        os.write(&allKeywords[0], std::streamsize(allKeywords.size()));
    } // m_keywords is not empty

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool MetaInformationKeywordsIn7110::isEqual(const MetaInformationBaseIn7110& otherBase) const
{
    // Can compare same types only.
    const MetaInformationKeywordsIn7110* other = dynamic_cast<const MetaInformationKeywordsIn7110*>(&otherBase);
    assert(other != nullptr);

    return MetaInformationBaseIn7110::isEqual(otherBase) && (this->getKeywords() == other->getKeywords());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
