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
//!\date Mar 16, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/misc/SdkExceptions.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<class C>
class LogMessage64x0Importer64x0Base
{
public:
    std::streamsize getSerializedSize(const C* container) const;

    //========================================
    //!\brief convert data from source to target type (deserialization)
    //!\param[in, out] is      Input data stream
    //!\param[out]     c       Output container.
    //!\param[in]      header  Ibeo DataHeader
    //!\return \c true if serialization succeed, else: false
    //!\note This method is to be called from outside for deserialization.
    //----------------------------------------
    bool deserialize(std::istream& is, C* container, const IbeoDataHeader& header) const;
}; // LogMessage64x0Importer64x0Base

//==============================================================================

template<class C>
std::streamsize LogMessage64x0Importer64x0Base<C>::getSerializedSize(const C* container) const
{
    return std::streamsize(1 + container->m_message.size());
}

//==============================================================================

template<class C>
bool LogMessage64x0Importer64x0Base<C>::deserialize(std::istream& is, C* container, const IbeoDataHeader& dh) const
{
    container->setDataHeader(dh);

    const int64_t startPos = streamposToInt64(is.tellg());

    // check whether the tracelevel is correct.
    uint8_t tl;
    ibeo::common::sdk::readBE(is, tl);
    if (static_cast<typename C::TraceLevel>(tl) != C::msgTraceLevel)
    {
        return false;
    }

    int nbOfPoppedCharacters = 0;

    if (dh.getMessageSize() == 1)
    {
        // empty string as message
        container->m_message.clear();
        if ((streamposToInt64(is.tellg()) - startPos) != getSerializedSize(container))
        {
            return false;
        }
    }
    else
    {
        // one byte has already been read, the string is the rest.
        const size_t expectedStringLength = dh.getMessageSize() - 1;
        std::vector<char> buf(expectedStringLength);
        is.read(buf.data(), static_cast<std::streamsize>(expectedStringLength));

        if ((streamposToInt64(is.tellg()) - startPos) != dh.getMessageSize())
        {
            return false;
        }

        // remove trailing line breaks and null bytes.
        while (!buf.empty()
               && (buf.back() == std::string::value_type(0) || buf.back() == std::string::value_type('\n')))
        {
            buf.pop_back();
            ++nbOfPoppedCharacters;
        }

        // copy char buffer/vector into string
        container->m_message = C::toASCII(buf);
    }

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos) == (this->getSerializedSize(container) + nbOfPoppedCharacters))
           && ((this->getSerializedSize(container) + nbOfPoppedCharacters) == dh.getMessageSize());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
