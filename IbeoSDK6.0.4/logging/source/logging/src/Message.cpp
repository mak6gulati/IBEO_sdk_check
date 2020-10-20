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
//! \date Nov 01, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/logging/Message.hpp>

#include <mutex>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

Message::Message(int lineNo, const char* function, const char* file, const std::string& text)
  : m_lineNo{lineNo},
    m_function{function},
    m_file{file},
    m_text{text},
    m_timestamp{std::chrono::system_clock::now()},
    m_sequenceNumber{getNextSequenceNumber()},
    m_threadId{std::this_thread::get_id()}
{}

//==============================================================================

std::string Message::getText() const
{
    std::stringstream stream;
    print(stream);
    return stream.str();
}

//==============================================================================

void Message::print(std::ostream& ostr) const
{
    ostr << m_text;
    for (std::shared_ptr<Message> helper : m_streamHelpers)
    {
        helper->print(ostr);
    }
}

//==============================================================================

uint64_t Message::getNextSequenceNumber()
{
    static uint64_t lastSeqNo{0};
    static std::mutex mutex;

    std::lock_guard<std::mutex> guard(mutex);

    ++lastSeqNo;

    return lastSeqNo;
}

//==============================================================================

void Message::addHelper(std::shared_ptr<Message> helper) { m_streamHelpers.push_back(helper); }

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================
