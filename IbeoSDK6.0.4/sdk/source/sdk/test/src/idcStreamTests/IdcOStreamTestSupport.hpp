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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/sdk/devices/IdcOStream.hpp>

#include "common/TestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class IdcOStreamTestSupport : public TestSupport
{
public:
    using DataBlockInfo = std::pair<IbeoDataHeader, std::shared_ptr<char>>;

public:
    IdcOStreamTestSupport()          = default;
    virtual ~IdcOStreamTestSupport() = default;

    static DataBlockInfo createRandomDatablock();

protected:
    static IbeoDataHeader fillHeaderRandomly(const uint32_t msgSize);

public:
    bool fillStream(IdcOStream& os);

protected:
    uint32_t getStreamSize() const;

protected:
    static const constexpr uint32_t maxDataBlockSize{200000};
    static const constexpr uint32_t memoryLimit{1000000};
    static const constexpr uint32_t maxNbOfDataBlocks = 30;
    static const constexpr int32_t nbOfRepeats        = 20;

protected:
    std::vector<DataBlockInfo> m_blocksInStream;
}; // IdcOStreamTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
