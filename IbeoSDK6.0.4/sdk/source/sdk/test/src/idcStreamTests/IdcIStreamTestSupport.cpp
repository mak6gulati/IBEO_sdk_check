//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#include <idcStreamTests/IdcIStreamTestSupport.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

bool IdcIStreamTestSupport::fillStream(std::ostream& os)
{
    m_blocksInStream.clear();

    const uint8_t upperLimit = (uint8_t)(maxNbOfDataBlocks - 1);
    const uint8_t potentialNbOfDataBlocks{(uint8_t)(getRandValue<uint8_t>(upperLimit) + 1U)};
    for (uint8_t t = 0; t < potentialNbOfDataBlocks; ++t)
    {
        DataBlockInfo newDb = createRandomDatablock();
        const uint32_t sizeAfterAppending{getStreamSize() + newDb.first.getMessageSize()
                                          + IbeoDataHeader::getHeaderSize()};

        if (sizeAfterAppending <= memoryLimit)
        {
            if (!writeDataBlock(os, newDb))
            {
                return false;
            }
            m_blocksInStream.push_back(newDb);
        }
    }

    os.flush();
    return true;
}

//==============================================================================

std::pair<IbeoDataHeader, std::shared_ptr<char>> IdcIStreamTestSupport::createRandomDatablock()
{
    const uint32_t dbSz{getRandValue<uint32_t>(maxDataBlockSize)};
    std::shared_ptr<char> b(new char[dbSz], std::default_delete<char[]>());

    for (auto i = b.get(); i < b.get() + dbSz; ++i)
    {
        *i = getRandValue<char>();
    }

    IbeoDataHeader dh{fillHeaderRandomly(dbSz)};
    return std::make_pair(dh, b);
}

//==============================================================================

bool IdcIStreamTestSupport::writeDataBlock(std::ostream& os, DataBlockInfo& dbi)
{
    const bool hdrSerIsOk{dbi.first.serialize(os)};
    os.write(dbi.second.get(), dbi.first.getMessageSize());
    return hdrSerIsOk && os.good();
}

//==============================================================================

IbeoDataHeader IdcIStreamTestSupport::fillHeaderRandomly(const uint32_t msgSize)
{
    return IbeoDataHeader(static_cast<DataTypeId>(getRandValue<uint16_t>()),
                          getRandValue<uint32_t>(),
                          msgSize,
                          getRandValue<uint8_t>(),
                          getRandValue<NTPTime>());
}

//==============================================================================

uint32_t IdcIStreamTestSupport::getStreamSize() const
{
    auto ss = uint32_t{0};
    for (const auto& dbe : m_blocksInStream)
    {
        ss += dbe.first.getMessageSize() + IbeoDataHeader::getHeaderSize();
    }
    return ss;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
