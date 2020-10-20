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
//! \date Jun 28, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/devices/IdcFileController.hpp>
#include <ibeo/common/sdk/devices/IdcFile.hpp>

#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

int64_t IdcFileController::getPos() const { return m_idcFile.getPos(); }

//==============================================================================

void IdcFileController::setPos(const int64_t position)
{
    if (!m_idcFile.isOpen())
    {
        return;
    }

    std::streampos pos(position);

    m_strm.clear(); //reset stream state error flags
    m_strm.seekg(pos, std::ios::beg);
}

//==============================================================================

int64_t IdcFileController::getFileSize()
{
    if (!m_idcFile.isOpen())
    {
        return -1;
    }

    m_strm.clear();

    const int64_t currPos{getPos()}; // store original position

    m_strm.seekg(0, std::ios::end);
    const int64_t end{getPos()};

    setPos(currPos); // restore original position

    return end - m_idcFile.getStartPos();
}

//==============================================================================

bool IdcFileController::skipDataBlocksForwards(const uint32_t nbOfMessagesToSkip, const bool clearStreamFlags)
{
    if (!m_idcFile.isOpen())
    {
        return false;
    }

    if (clearStreamFlags)
    {
        m_strm.clear(); //reset stream state error flags
    }

    // the current get position ought to be before a a IbeoDataHeader.
    // read the header and skip the body
    for (uint32_t n = 0; n < nbOfMessagesToSkip; ++n)
    {
        if (!m_dh.deserialize(m_strm))
        {
            return false;
        }
        m_strm.seekg(m_dh.getMessageSize(), std::ios::cur);
    }
    return static_cast<bool>(m_strm);
}

//==============================================================================

bool IdcFileController::skipDataBlocksBackwards(const uint32_t nbOfMessagesToSkip, const bool clearStreamFlags)
{
    if (!m_idcFile.isOpen())
    {
        return false;
    }

    if (clearStreamFlags)
    {
        m_strm.clear(); //reset stream state error flags
    }

    if (getPos() == getFileSize())
    {
        m_strm.seekg(-IbeoDataHeader::getHeaderSize(), std::ios::end);
    }
    // the current get position ought to be before a IbeoDataHeader.
    // read the header seek backwards
    //   - the size of the IbeoDataHeader just read
    //   - the size of the previous datablock
    //   - the size of the IbeoDataHeader of the previous datablock.
    for (uint32_t n = 0; n < nbOfMessagesToSkip; ++n)
    {
        if (!m_dh.deserialize(m_strm))
        {
            return false;
        }
        const int64_t offs = m_dh.getPreviousMessageSize() + 2U * IbeoDataHeader::getHeaderSize();
        m_strm.seekg(-offs, std::ios::cur);
    }
    return static_cast<bool>(m_strm);
}

//==============================================================================

bool IdcFileController::setToFirstDataBlock(const bool clearStreamFlags)
{
    if (!m_idcFile.isOpen())
    {
        return false;
    }

    if (clearStreamFlags)
    {
        m_strm.clear(); //reset stream state error flags
    }

    setPos(0);
    if (!m_dh.deserialize(m_strm))
    {
        return false;
    }

    setPos(0);

    return true;
}

//==============================================================================

bool IdcFileController::setToIdcTrailer(const bool clearStreamFlags)
{
    if (!m_idcFile.isOpen())
    {
        return false;
    }

    if (clearStreamFlags)
    {
        m_strm.clear(); //reset stream state error flags
    }

    const uint8_t hdrSz{IbeoDataHeader::getHeaderSize()};
    m_strm.seekg(-hdrSz, std::ios::end);

    if (!m_dh.deserialize(m_strm))
    {
        return false;
    }

    if (m_dh.getDataType() != DataTypeId::DataType_IdcTrailer6120)
    {
        return false;
    }

    m_strm.seekg(-hdrSz, std::ios::end);
    return true;
}

//==============================================================================

bool IdcFileController::getNextHeader(IbeoDataHeader& dh)
{
    // TODO take care of the stream flags
    if (!m_idcFile.isOpen())
    {
        return false; // nullptr
    }

    const int64_t currPos{getPos()};

    const bool succ{dh.deserialize(this->m_strm)};

    setPos(currPos);
    // restore the stream flags to those set before

    return succ;
}

//==============================================================================

bool IdcFileController::getTimeRange(NTPTime& startTime, NTPTime& endTime)
{
    const int64_t currPos{getPos()}; // store original position

    bool isOk{true};
    if (setToFirstDataBlock() && getNextHeader(m_dh))
    {
        startTime = m_dh.getTimestamp();

        if (setToIdcTrailer() && getNextHeader(m_dh))
        {
            endTime = m_dh.getTimestamp();

            if ((m_dh.getDataType() == DataTypeId::DataType_IdcTrailer6120) && skipDataBlocksBackwards(1)
                && getNextHeader(m_dh) && (m_dh.getDataType() == DataTypeId::DataType_FrameIndex6130))
            {
                endTime = m_dh.getTimestamp();
            }
        }
        else
        {
            isOk = false;
        }
    }
    else
    {
        isOk = false;
    }

    setPos(currPos);

    return isOk;
}

//==============================================================================

bool IdcFileController::getTimeRange(boost::posix_time::ptime& startTime, boost::posix_time::ptime& endTime)
{
    NTPTime st;
    NTPTime et;
    const bool ok{getTimeRange(st, et)};
    startTime = st.toPtime();
    endTime   = et.toPtime();
    return ok;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
