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
//! \date Jan 30, 2019
//------------------------------------------------------------------------------

#include "DeviceStatusTestSupport.hpp"
#include "UserDefinedStructDummy1.hpp"
#include "UserDefinedStructDummy2.hpp"
#include "UserDefinedStructDummy3.hpp"
#include "UserDefinedStructDummy4.hpp"

//==============================================================================
namespace {
//==============================================================================

//==============================================================================
//!\brief Fills the given buffer \a buf by randomly initialized instances of type \a T.
//!
//! Depending on the type this function will calculate the number of bytes that
//! can be used. \a nbOfBytes is the upper limit. In case the size of type \a T
//! is larger than 1, the number of bytes that can be filled in the buffer by
//! instance of type \a T can be actually smaller.
//!
//! The number of elements is calculated by the \a nbOfBytes which are available
//! and the size of type \a T. The number of actual used bytes is number of elements
//! multiplied by size of type \a T. It yields that actualNbOfBytes <= nbOfBytes.
//!
//! The alignment of type \a T is calculated as its size.
//!
//!\param[in, out] buf        Buffer to be filled with random values.
//!\param[in]      nbOfBytes  Number of bytes that can be filled.
//!\tparam T one out of (u)int8_t, (u)int16_t, (u)int32_t, float
//!\return pair of the actual number of used bytes and the needed alignment for
//!        this type.
//------------------------------------------------------------------------------
template<typename T>
std::pair<uint8_t, uint8_t> setBuf(T* buf, const uint8_t nbOfBytes)
{
    const uint8_t nbOfElements    = uint8_t(nbOfBytes / sizeof(T));
    const uint8_t actualNbOfBytes = uint8_t(nbOfElements * sizeof(T));
    for (uint8_t i = 0; i < actualNbOfBytes; ++i)
    {
        buf[i] = (T)ibeo::common::sdk::unittests::TestSupport::getRandValue<uint32_t>();
    }
    const uint8_t alignment = uint8_t(sizeof(T));
    return std::make_pair(actualNbOfBytes, alignment);
}

//==============================================================================
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

void DeviceStatusTestSupport::fillRandomly(DeviceStatus& ds)
{
    // Temperatures [Kelvin] might be converted to [degree Celsius]
    // -> limit the range of random values so that a float-compare is possible.
    // Scan frequency [Hz] might be converted to scan period [us] as uint32_t
    // -> limit the range of random values so that a float-compare is possible.
    // Noise measurement threshold [V] might be converted to [mV] as uint32_t
    // -> limit the range of random values so that a float-compare is possible.
    ds.setSerialNumberOfScanner(createSerialNumber());
    ds.setScannerType(static_cast<ScannerType>(getRandValue<uint8_t>()));
    ds.setDeviceId(getRandValue<uint8_t>());
    ds.setFpgaVersion(createVersion448());
    ds.setDspVersion(createVersion448());
    ds.setHostVersion(createVersion448());
    ds.setFpgaOperationRegister(getRandValue<uint16_t>());
    ds.setFpgaStatusRegister(getRandValue<uint16_t>());
    ds.setSensorTemperatureApd0(getRandValue<float>(0.0F, 1000.0F));
    ds.setSensorTemperatureApd1(getRandValue<float>(0.0F, 1000.0F));
    ds.setScanFrequency(getRandValue<float>(1.0F, 100.0F));
    ds.setApdTableBiasVoltage(getRandValue<float>());
    ds.setMinApdVoltageOffset(getRandValue<float>());
    ds.setMaxApdVoltageOffset(getRandValue<float>());
    ds.setNoiseMeasurementThreshold(getRandValue<float>(0.0F, 100.0F));
    ds.setReferenceNoise(getRandValue<uint16_t>());

    DeviceStatus::AdaptiveApdVoltageArray adpVoltageArray;
    DeviceStatus::ActualNoiseArray noiseArray;
    for (uint32_t idx = 0; idx < DeviceStatus::nbOfApdSectors; ++idx)
    {
        adpVoltageArray.at(idx) = getRandValue<float>();
        noiseArray.at(idx)      = getRandValue<uint16_t>();
    }
    ds.setAdaptiveApdVoltageArray(adpVoltageArray);
    ds.setActualNoiseArray(noiseArray);
}

//==============================================================================

void DeviceStatusTestSupport::fillRandomly(DeviceStatus6301& ds)
{
    // Temperature [degree Celsius] might be converted to [Kelvin]
    // -> limit the range of random values so that a float-compare is possible.
    // Scan frequency [Hz] might be converted to scan period [us] as uint32_t
    // -> limit the range of random values so that a float-compare is possible.
    // Noise measurement threshold [V] might be converted to [mV] as uint32_t
    // -> limit the range of random values so that a float-compare is possible.
    ds.setScannerType(static_cast<ScannerType>(getRandValue<uint8_t>()));
    //	ds.setReserved0(const uint8_t newReserved0) { m_reserved0 = newReserved0; }
    ds.setFpgaModusRegister(getRandValue<uint16_t>());
    //	ds.setReserved1(getRandValue<uint16_t>());
    ds.setSensorTemperature(getRandValue<float>(0.0F, 1000.0F));
    ds.setFrequency(
        getRandValue<float>(1.0F, 100.0F)); // max. 100Hz as it might be converted to a period in us as uint32_t.
    ds.setApdTableVoltage(getRandValue<float>());
    ds.setMinApdVoltageOffset(getRandValue<float>());
    ds.setMaxApdVoltageOffset(getRandValue<float>());
    //	ds.setReserved2(getRandValue<uint16_t>());
    //	ds.setReserved3(getRandValue<uint16_t>());
    ds.setNoiseMeasurementThreshold(getRandValue<float>(0.0F, 100.0F));
    ds.setReferenceNoise(getRandValue<uint16_t>());
    //	ds.setReservedA(const int idx, const uint16_t newReserved) { m_reservedA[idx] = newReserved; }

    for (uint32_t idx = 0; idx < DeviceStatus6301::nbOfApdSectors; ++idx)
    {
        ds.setAdaptiveApdVoltage(idx, getRandValue<float>());
        ds.setActualNoise(idx, getRandValue<uint16_t>());
    }
}

//==============================================================================

void DeviceStatusTestSupport::fillRandomly(DeviceStatus6303& ds, const bool allowReordering)
{
    // Temperatures [degree Celsius] might be converted to [Kelvin]
    // -> limit the range of random values so that a float-compare is possible.
    // Scan period [us] might be converted to scan frequency [Hz] as float
    // -> limit the range of random values so that a float-compare is possible.
    // Noise measurement threshold [mV] might be converted to [V] as float
    // -> limit the range of random values so that a float-compare is possible.
    ds.setSerialNumber(createSerialNumber());
    ds.setScannerType(getRandValue<uint8_t>());
    ds.setDeviceId(getRandValue<uint8_t>());
    ds.setFpgaVersion(createVersion448());
    ds.setHostVersion(createVersion448());
    ds.setScanPeriod(getRandValue<uint32_t>(1, 1E6));
    ds.setSensorTemperatureApd0(getRandValue<float>(0.0F, 1000.0F));
    ds.setSensorTemperatureApd1(getRandValue<float>(0.0F, 1000.0F));
    ds.setMinApdVoltageOffset(getNonNanRandValue<float>());
    ds.setMaxApdVoltageOffset(getNonNanRandValue<float>());
    ds.setNoiseMeasurementThreshold(getRandValue<uint32_t>(0, 100000));
    ds.setReferenceNoise(getRandValue<uint16_t>());

    constexpr std::size_t bufSize = 1024;
    char buf[bufSize];
    std::size_t freeBuf = bufSize;

    const uint8_t nbOfCont = getRandValue<uint8_t>(20);

    const uint8_t worstCasePadding{allowReordering ? uint8_t{3} : uint8_t{0}};

    for (uint8_t c = 0; c < nbOfCont && freeBuf > worstCasePadding; ++c)
    {
        const DeviceStatus6303::ContentId cId = random6303ContentType();
        if (cId >= DeviceStatus6303::ContentId::Dummy1)
        {
            create6303UserDefinedContentEntry(ds, cId, freeBuf);
        }
        else
        {
            create6303ContentEntry(ds, cId, freeBuf, worstCasePadding, buf);
        } // else
    } // for c

    //	std::cerr << "Remaining free bytes: " << freeBuf+nbOfProphilacticPaddingBytes
    //			<< " (padding: " << nbOfProphilacticPaddingBytes << ")" << std::endl;
}

//==============================================================================

SerialNumber DeviceStatusTestSupport::createSerialNumber()
{
    SerialNumber sn;
    fillRandomly(sn);
    return sn;
}

//==============================================================================

void DeviceStatusTestSupport::fillRandomly(SerialNumber& sn)
{
    sn.setMonth(getRandValue<uint8_t>(12));
    sn.setYear(getRandValue<uint8_t>());
    sn.setCnt0(getRandValue<uint8_t>());
    sn.setCnt1(getRandValue<uint8_t>());
    sn.setNull(getRandValue<uint16_t>());
}

//==============================================================================

Version448 DeviceStatusTestSupport::createVersion448()
{
    Version448 v;
    fillRandomly(v);
    return v;
}

//==============================================================================

void DeviceStatusTestSupport::fillRandomly(Version448& v)
{
    v.setVersion(getRandValue<uint16_t>());
    v.setYear(getRandValue<uint16_t>());
    v.setMonth(getRandValue<uint8_t>());
    v.setDay(getRandValue<uint8_t>());
    v.setHour(getRandValue<uint8_t>());
    v.setMinute(getRandValue<uint8_t>());
}

//==============================================================================

bool DeviceStatusTestSupport::create6303UserDefinedContentEntry(DeviceStatus6303& ds,
                                                                const DeviceStatus6303::ContentId cId,
                                                                std::size_t& freeBuf)
{
    if (cId < DeviceStatus6303::ContentId::Dummy1)
    {
        return false;
    }

    using Dummy1 = UserDefinedStructDummy1;
    using Dummy2 = UserDefinedStructDummy2;
    using Dummy3 = UserDefinedStructDummy3;
    using Dummy4 = UserDefinedStructDummy4;

    bool added{false};

    std::unique_ptr<DeviceStatus6303::UserDefinedStructBase> d{nullptr};

    switch (cId)
    {
    default: // no break
    case DeviceStatus6303::ContentId::Dummy1:
        d.reset(new Dummy1);
        break;
    case DeviceStatus6303::ContentId::Dummy2:
        d.reset(new Dummy2);
        break;
    case DeviceStatus6303::ContentId::Dummy3:
        d.reset(new Dummy3);
        break;
    case DeviceStatus6303::ContentId::Dummy4:
        d.reset(new Dummy4);
        break;
    }

    const uint8_t structSize{d->getSerializedSize()};
    if (freeBuf >= structSize)
    {
        added = ds.addContent(*d);

        if (added)
        {
            //			std::cerr << "   Before: " << freeBuf << " After: " << freeBuf - structSize << std::endl;
            freeBuf -= structSize;
        }
    }

    return added;
}

//==============================================================================

bool DeviceStatusTestSupport::create6303ContentEntry(DeviceStatus6303& ds,
                                                     const DeviceStatus6303::ContentId cId,
                                                     std::size_t& freeBuf,
                                                     const uint8_t worstCasePadding,
                                                     char* const buf)
{
    const DeviceStatus6303::ElementType et{DeviceStatus6303::ElementType(getRandValue<uint8_t>(7) + 1)};

    // choose the number of bytes used for this content array.
    uint8_t n = getRandValue<uint8_t>(
        static_cast<uint8_t>((freeBuf - worstCasePadding < 255) ? freeBuf - worstCasePadding : 255));

    bool added{false};
    std::pair<uint8_t, uint8_t> aa; // actual number of bytes (first) and alignment (second)

    switch (et)
    {
    case DeviceStatus6303::ElementType::UINT8:
        aa = setBuf(reinterpret_cast<uint8_t*>(buf), n);
        break;
    case DeviceStatus6303::ElementType::INT8:
        aa = setBuf(reinterpret_cast<int8_t*>(buf), n);
        break;
    case DeviceStatus6303::ElementType::UINT16:
        aa = setBuf(reinterpret_cast<uint16_t*>(buf), n);
        break;
    case DeviceStatus6303::ElementType::INT16:
        aa = setBuf(reinterpret_cast<int16_t*>(buf), n);
        break;
    case DeviceStatus6303::ElementType::UINT32:
        aa = setBuf(reinterpret_cast<uint32_t*>(buf), n);
        break;
    case DeviceStatus6303::ElementType::INT32:
        aa = setBuf(reinterpret_cast<int32_t*>(buf), n);
        break;
    case DeviceStatus6303::ElementType::FLOAT32:
        aa = setBuf(reinterpret_cast<float*>(buf), n);
        break;
    default:
        break;
    } // switch et

    const uint8_t nbOfBytes = aa.first;
    const uint8_t alignment = aa.second;
    added                   = ds.addContent(cId, et, nbOfBytes, alignment, buf);

    if (added)
    {
        freeBuf -= static_cast<uint16_t>(n + worstCasePadding);
    }

    return added;
}

//==============================================================================

DeviceStatus6303::ContentId DeviceStatusTestSupport::random6303ContentType()
{
    const int r = getRandValue<uint8_t>(12);
    switch (r)
    {
    case 0:
        return DeviceStatus6303::ContentId::Illegal;
    case 1:
        return DeviceStatus6303::ContentId::ApdVoltageTable;
    case 2:
        return DeviceStatus6303::ContentId::NoiseTable;
    case 3:
        return DeviceStatus6303::ContentId::ScalaARMVersion;
    case 4:
        return DeviceStatus6303::ContentId::ErrorScalaFPGA;
    case 5:
        return DeviceStatus6303::ContentId::YawOffsetConf;
    case 6:
        return DeviceStatus6303::ContentId::YawOffsetCalc;
    case 7:
        return DeviceStatus6303::ContentId::VelFactorConf;
    case 8:
        return DeviceStatus6303::ContentId::VelFactorCalc;
    case 9:
        return DeviceStatus6303::ContentId::Dummy1;
    case 10:
        return DeviceStatus6303::ContentId::Dummy2;
    case 11:
        return DeviceStatus6303::ContentId::Dummy3;
    case 12:
        return DeviceStatus6303::ContentId::Dummy4;
    default: // ContentTypes between 1 and 0xffff.
        return DeviceStatus6303::ContentId::Illegal;
    }
}

//==============================================================================

void DeviceStatusTestSupport::fillRandomly(AdaptiveApdVoltageAndNoiseInfoIn6303& avt)
{
    avt.setProcUnitAndVersion(getRandValue<uint32_t>());
    avt.setScanNumber(getRandValue<uint16_t>());

    for (AdaptiveApdVoltageAndNoiseInfoIn6303::ApdSector& sector : avt.getSectors())
    {
        fillRandomly(sector);
    }

    avt.setFlags(getRandValue<uint8_t>());
}

//==============================================================================

void DeviceStatusTestSupport::fillRandomly(AdaptiveApdVoltageAndNoiseInfoIn6303::ApdSector& sector)
{
    sector.setAdaptiveApdVoltage(getRandValue<float>());
    sector.setReducedApdOffset(getRandValue<float>());
    sector.setNoise(getRandValue<uint16_t>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
