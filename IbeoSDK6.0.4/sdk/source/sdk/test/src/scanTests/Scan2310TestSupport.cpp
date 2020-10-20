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
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "Scan2310TestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

Scan2310TestSupport::Scan2310TestSupport() : TestSupport() {}

//==============================================================================

Scan2310TestSupport::~Scan2310TestSupport() {}

//==============================================================================

ibeo::common::sdk::Scan2310 Scan2310TestSupport::createScan2310()
{
    ibeo::common::sdk::Scan2310 sfrd;
    fillRandomly(sfrd);
    return sfrd;
}

//==============================================================================

void Scan2310TestSupport::fillRandomly(Scan2310& sfrd)
{
    sfrd.setPayLoadSize(getRandValue<uint32_t>()); // ???

    sfrd.setUtcSeconds(getRandValue<uint32_t>());
    sfrd.setFlexrayMeasTime(getRandValue<uint32_t>());

    sfrd.setFlexrayMasterClock(getRandValue<uint8_t>());
    sfrd.setVersionInfo0(getRandValue<uint16_t>());
    sfrd.setVersionInfo1(getRandValue<uint16_t>());

    sfrd.setScanStartTime(getRandValue<NTPTime>());
    sfrd.setScanEndTime(getRandValue<NTPTime>());
    sfrd.setScanMidTime(getRandValue<NTPTime>());

    ScanHeaderIn2310 hd;
    fillRandomly(hd);
    sfrd.setHeader(hd);

    ScanInfoIn2310 info;
    fillRandomly(info);
    sfrd.setInfo(info);

    fillRandomly(sfrd.getPoints());
    fillRandomly(sfrd.getSegInfos());
    fillRandomly(sfrd.getDiagPulses());
    fillRandomly(sfrd.getRefScans());

    ScanTrailerIn2310 trailer;
    fillRandomly(trailer);
    sfrd.setTrailer(trailer);

    sfrd.setCrc32(getRandValue<uint32_t>());
}

//==============================================================================

void Scan2310TestSupport::fillRandomly(ScanHeaderIn2310& header)
{
    header.setScanCounter(getRandValue<uint16_t>());

    header.setMinApdOffset(getRandValue<uint16_t>());
    header.setMaxApdOffset(getRandValue<uint16_t>());

    header.setFrequencyInteger(getRandValue<uint16_t>());
    header.setFrequencyFractional(getRandValue<uint16_t>());

    header.setDeviceId(getRandValue<uint16_t>());

    // reserved uint16_t
}

//==============================================================================

void Scan2310TestSupport::fillRandomly(ScanInfoIn2310& info)
{
    info.setApdActualValue(getRandValue<uint16_t>());
    info.setApdTableValue(getRandValue<uint16_t>());

    info.setTemperature(getRandValue<uint16_t>());

    info.setReferenceNoise(getRandValue<uint16_t>());
    info.setControlNoise(getRandValue<uint16_t>());
    info.setNoiseMeasurementThreshold(getRandValue<uint16_t>());

    // reserved uint16_t
}

//==============================================================================

void Scan2310TestSupport::fillRandomly(std::vector<ScanPointIn2310>& pointVector)
{
    for (auto& point : pointVector)
    {
        fillRandomly(point);
    }
}

//==============================================================================

void Scan2310TestSupport::fillRandomly(std::vector<ScanSegInfoIn2310>& segInfoVector)
{
    const uint16_t sz{getRandValue<uint16_t>(3000)};
    segInfoVector.resize(sz);

    for (auto& segInfo : segInfoVector)
    {
        segInfo.setSegmentIndex(getRandValue<uint16_t>());
        segInfo.setApdVoltage(getRandValue<uint16_t>());
        segInfo.setNoise(getRandValue<uint16_t>());
        // 4x reserved uint16_t
    }
}

//==============================================================================

void Scan2310TestSupport::fillRandomly(std::vector<ScanPointDiagPulseIn2310>& diagPulseVector)
{
    const uint16_t sz{getRandValue<uint16_t>(3000)};
    diagPulseVector.resize(sz);

    for (auto& segInfo : diagPulseVector)
    {
        fillRandomly(segInfo);
    }
}

//==============================================================================

void Scan2310TestSupport::fillRandomly(std::vector<ScanPointRefScanIn2310>& refScanVector)
{
    const uint16_t sz{getRandValue<uint16_t>(3000)};
    refScanVector.resize(sz);

    for (auto& refPt : refScanVector)
    {
        fillRandomly(refPt);
    }
}

//==============================================================================

void Scan2310TestSupport::fillRandomly(ScanTrailerIn2310& trailer)
{
    trailer.setOperatingRegister(getRandValue<uint16_t>());
    trailer.setWarning(getRandValue<uint16_t>());
    trailer.setError(getRandValue<uint16_t>());
    // reserved uint16_t
    trailer.setScanPointCounter(getRandValue<uint16_t>());
    trailer.setConfigurationRegister(getRandValue<uint16_t>());
    // reserved uint16_t
}

//==============================================================================

void Scan2310TestSupport::fillRandomly(ScanPointBaseIn2310& spb)
{
    spb.setRadialDistance(getRandValue<uint16_t>());
    spb.setEchoPulseWidth(getRandValue<uint16_t>());

    spb.setAngle(getRandValue<int16_t>());

    // reserved uint16_t
    spb.setResolution(getRandValue<uint16_t>());

    spb.setChannelId(getRandValue<uint8_t>());
    spb.setEchoId(getRandValue<uint8_t>());
    spb.setFlagsHigh(getRandValue<uint8_t>());
    spb.setFlagsLow(getRandValue<uint8_t>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
