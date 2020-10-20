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
//! \date Mar 05, 2015
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

void writeLE(uint8_t*& buf, BitNumber& firstBitToWrite, uint8_t val, const int nbOfDataBits)
{
    val = uint8_t(uint8_t(val << (8 - nbOfDataBits)) >> (8 - nbOfDataBits));

    if (firstBitToWrite + nbOfDataBits > 8)
    {
        // the value will be written into two bytes.
        const int nbOfBitsInFirstByte  = 8 - firstBitToWrite;
        const int nbOfBitsInSecondByte = nbOfDataBits - nbOfBitsInFirstByte;
        const uint8_t firstByteBits = uint8_t(uint8_t(val << (8 - nbOfBitsInFirstByte)) >> (8 - nbOfBitsInFirstByte));
        *buf                        = uint8_t(*buf | uint8_t(firstByteBits << firstBitToWrite));
        ++buf;
        const uint8_t secondByteBits = uint8_t(
            (uint8_t(val >> nbOfBitsInFirstByte) << (8 - nbOfBitsInSecondByte) & 0xFF) >> (8 - nbOfBitsInSecondByte));
        *buf |= secondByteBits;
        firstBitToWrite = BitNumber(firstBitToWrite + nbOfDataBits - 8);
    }
    else if (firstBitToWrite + nbOfDataBits == 8)
    {
        // the value fits into the current byte but the byte is
        // completely filled after this write operation.
        *buf = uint8_t(*buf | uint8_t(val << firstBitToWrite));
        ++buf;
        firstBitToWrite = Bit0;
    }
    else
    {
        // the value fits into the current byte and there are still
        // some bits free after this write operation.
        *buf            = uint8_t(*buf | uint8_t(val << firstBitToWrite));
        firstBitToWrite = BitNumber(firstBitToWrite + nbOfDataBits);
    }
}

//==============================================================================

void writeLE(uint8_t*& buf, BitNumber& firstBitToWrite, const uint16_t val, const int nbOfDataBits)
{
    writeLE(buf, firstBitToWrite, uint8_t(val), 8);
    writeLE(buf, firstBitToWrite, uint8_t(val >> 8), nbOfDataBits - 8);
}

//==============================================================================

uint8_t readLE8(const uint8_t*& buf, BitNumber& firstBitToRead, const int nbOfDataBits)
{
    uint8_t val = 0;
    if (firstBitToRead + nbOfDataBits > 8)
    {
        // The bits to be read are distributed to two bytes.
        const int nbOfBitsInFirstByte  = 8 - firstBitToRead;
        const int nbOfBitsInSecondByte = nbOfDataBits - nbOfBitsInFirstByte;
        val                            = uint8_t(((*buf) >> firstBitToRead
                       | (((*(buf + 1)) << (8 - nbOfBitsInSecondByte)) & 0xFF)
                             >> (8 - nbOfBitsInFirstByte - nbOfBitsInSecondByte)));
        ++buf;
        firstBitToRead = BitNumber(firstBitToRead + nbOfDataBits - 8);
    }
    else if (firstBitToRead + nbOfDataBits == 8)
    {
        // The bits to be read are inside the current byte only but
        // afterwards all of the bits of this byte has been read.
        val = uint8_t((*buf) >> firstBitToRead);
        ++buf;
        firstBitToRead = Bit0;
    }
    else
    {
        // The bits to be read are inside the current byte only and
        // not all of the bits has been read.
        val            = uint8_t((((*buf) << (8 - firstBitToRead - nbOfDataBits)) & 0xFF) >> (8 - nbOfDataBits));
        firstBitToRead = BitNumber(firstBitToRead + nbOfDataBits);
    }
    return val;
}

//==============================================================================

uint16_t readLE16(const uint8_t*& buf, BitNumber& firstBitToRead, const int nbOfDataBits)
{
    uint16_t val = readLE8(buf, firstBitToRead, 8);

    const uint8_t valUpperBits = readLE8(buf, firstBitToRead, nbOfDataBits - 8);

    val |= uint16_t(int32_t(valUpperBits) << 8);
    return val;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
