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
//!\date Jan 25, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <common/TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303.hpp>

#include <boost/iostreams/stream.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class UserDefinedStructDummy4 : public DeviceStatus6303::UserDefinedStructBase
{
public:
    UserDefinedStructDummy4()
      : DeviceStatus6303::UserDefinedStructBase{DeviceStatus6303::ContentId::Dummy4},
        m_u1{TestSupport::getRandValue<uint32_t>()},
        m_u2{TestSupport::getRandValue<uint32_t>()},
        m_u3{TestSupport::getRandValue<uint16_t>()},
        m_u4{TestSupport::getRandValue<uint32_t>()},

        m_f5{TestSupport::getNonNanRandValue<float>()},

        m_i6{TestSupport::getRandValue<int8_t>()},
        m_i7{TestSupport::getRandValue<int16_t>()},
        m_i8{TestSupport::getRandValue<int32_t>()}
    {}

    virtual ~UserDefinedStructDummy4() {}

public:
    //========================================
    virtual bool deserialize(const DeviceStatus6303::ContentDescr& cd)
    {
        if (cd.getContentId() != DeviceStatus6303::ContentId::Dummy4)
        {
            return false;
        }

        boost::iostreams::stream<boost::iostreams::array_source> is(cd.getContentBuffer(), cd.getSerializedSize());
        readBE(is, m_u1);
        readBE(is, m_u2);
        readBE(is, m_u3);
        readBE(is, m_u4);

        readBE(is, m_f5);

        readBE(is, m_i6);
        readBE(is, m_i7);
        readBE(is, m_i8);
        return true;
    }

    //========================================
    virtual bool serialize(char*& buf) const
    {
        boost::iostreams::stream<boost::iostreams::array> strm((char*)(buf), getSerializedSize());
        std::ostream& os = (std::ostream&)strm;

        writeBE(os, m_u1);
        writeBE(os, m_u2);
        writeBE(os, m_u3);
        writeBE(os, m_u4);

        writeBE(os, m_f5);

        writeBE(os, m_i6);
        writeBE(os, m_i7);
        writeBE(os, m_i8);
        buf += getSerializedSize();

        return true;
    }

    //========================================
    virtual uint8_t getSerializedSize() const
    {
        return 3 * sizeof(uint32_t) + sizeof(uint16_t) + sizeof(float) + sizeof(int8_t) + sizeof(int16_t)
               + sizeof(int32_t);
    }

protected:
    uint32_t m_u1;
    uint32_t m_u2;
    uint16_t m_u3;
    uint32_t m_u4;
    float m_f5;
    int8_t m_i6;
    int16_t m_i7;
    int32_t m_i8;
}; // UserDefinedStructDummy4

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
