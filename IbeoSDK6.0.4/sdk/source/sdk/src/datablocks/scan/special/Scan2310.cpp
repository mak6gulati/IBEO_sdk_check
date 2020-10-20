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
//!\date Jan 11, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/scan/special/Scan2310.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

constexpr uint32_t Scan2310::magicWord;
constexpr uint16_t Scan2310::internalDataTypeId;

//==============================================================================

Scan2310::Scan2310() : SpecializedDataContainer() {}

//==============================================================================

Scan2310::~Scan2310() {}

//==============================================================================

bool operator==(const Scan2310& lhs, const Scan2310& rhs)
{
    return lhs.getMagicWord() == rhs.getMagicWord() && lhs.getInternalDataTypeId() == rhs.getInternalDataTypeId()
           && lhs.getReserved00() == rhs.getReserved00() && lhs.getPayLoadSize() == rhs.getPayLoadSize()
           && lhs.getUtcSeconds() == rhs.getUtcSeconds() && lhs.getFlexrayMeasTime() == rhs.getFlexrayMeasTime()
           && lhs.getReserved01() == rhs.getReserved01() && lhs.getReserved02() == rhs.getReserved02()
           && lhs.getFlexrayMasterClock() == rhs.getFlexrayMasterClock() && lhs.getReserved03() == rhs.getReserved03()
           && lhs.getVersionInfo0() == rhs.getVersionInfo0() && lhs.getVersionInfo1() == rhs.getVersionInfo1()
           && lhs.getScanStartTime() == rhs.getScanStartTime() && lhs.getScanEndTime() == rhs.getScanEndTime()
           && lhs.getScanMidTime() == rhs.getScanMidTime() && lhs.getReserved04() == rhs.getReserved04()
           && lhs.getHeader() == rhs.getHeader() && lhs.getInfo() == rhs.getInfo() && lhs.getPoints() == rhs.getPoints()
           && lhs.getSegInfos() == rhs.getSegInfos() && lhs.getDiagPulses() == rhs.getDiagPulses()
           && lhs.getRefScans() == rhs.getRefScans() && lhs.getTrailer() == rhs.getTrailer()
           && lhs.getCrc32() == rhs.getCrc32();
}

//==============================================================================

bool operator!=(const Scan2310& lhs, const Scan2310& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
