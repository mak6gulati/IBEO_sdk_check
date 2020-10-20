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
//! \date Mar 14, 2014
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/Measurement.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/Math.hpp>

#include <boost/scoped_array.hpp>

#include <sstream>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ibeo::common::logging::LoggerSPtr Measurement::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

Measurement::Measurement() : m_key(0), m_data(0) {}

//==============================================================================

std::streamsize Measurement::getSerializedSize() const
{
    std::streamsize result = std::streamsize(sizeof(uint16_t)) // m_key
                             + std::streamsize(sizeof(uint8_t)); // m_measurementType

    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        return result;
    case MeasurementType::Float:
        return result + std::streamsize(sizeof(float));
    case MeasurementType::Double:
        return result + std::streamsize(sizeof(double));
    case MeasurementType::INT8:
    case MeasurementType::UINT8:
        return result + std::streamsize(sizeof(uint8_t));
    case MeasurementType::INT16:
    case MeasurementType::UINT16:
        return result + std::streamsize(sizeof(uint16_t));
    case MeasurementType::INT32:
    case MeasurementType::UINT32:
        return result + std::streamsize(sizeof(uint32_t));
    case MeasurementType::INT64:
    case MeasurementType::UINT64:
        return result + std::streamsize(sizeof(uint64_t));
    case MeasurementType::Bool:
        return result + std::streamsize(sizeof(uint8_t));
    case MeasurementType::StdString:
        result += 4; // 4 bytes for the BLOB data length
        result += std::streamsize(boost::any_cast<std::string>(m_data).size()); // and the BLOB data itself
        break;
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
    return result;
}

//==============================================================================

bool Measurement::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    union allTypes
    {
        float flt;
        double dbl;
        int8_t int8;
        uint8_t uint8;
        int16_t int16;
        uint16_t uint16;
        int32_t int32;
        uint32_t uint32;
        int64_t int64;
        uint64_t uint64;
        bool boolean;
    };

    allTypes tmp;

    readBE(is, m_key);

    uint8_t type;
    readBE(is, type);

    switch (MeasurementType(type))
    {
    case MeasurementType::Void:
        m_data = boost::any();
        break;
    case MeasurementType::Float:
        readBE(is, tmp.flt);
        m_data = tmp.flt;
        break;
    case MeasurementType::Double:
        readBE(is, tmp.dbl);
        m_data = tmp.dbl;
        break;
    case MeasurementType::INT8:
        readBE(is, tmp.int8);
        m_data = tmp.int8;
        break;
    case MeasurementType::UINT8:
        readBE(is, tmp.uint8);
        m_data = tmp.uint8;
        break;
    case MeasurementType::INT16:
        readBE(is, tmp.int16);
        m_data = tmp.int16;
        break;
    case MeasurementType::UINT16:
        readBE(is, tmp.uint16);
        m_data = tmp.uint16;
        break;
    case MeasurementType::INT32:
        readBE(is, tmp.int32);
        m_data = tmp.int32;
        break;
    case MeasurementType::UINT32:
        readBE(is, tmp.uint32);
        m_data = tmp.uint32;
        break;
    case MeasurementType::INT64:
        readBE(is, tmp.int64);
        m_data = tmp.int64;
        break;
    case MeasurementType::UINT64:
        readBE(is, tmp.uint64);
        m_data = tmp.uint64;
        break;
    case MeasurementType::Bool:
        readBE(is, tmp.boolean);
        m_data = tmp.boolean;
        break;
    case MeasurementType::StdString:
    {
        uint32_t strLen;
        readBE(is, strLen);
        boost::scoped_array<char> strBuf(new char[strLen]);
        is.read(strBuf.get(), strLen);
        m_data = std::string(strBuf.get(), strLen);
    }
    break;
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool Measurement::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, m_key);

    const MeasurementType mt = this->getMeasurementType();
    const uint8_t type       = uint8_t(mt);
    writeBE(os, type);

    switch (mt)
    {
    case MeasurementType::Void:
        break;
    case MeasurementType::Float:
        writeBE(os, boost::any_cast<float>(m_data));
        break;
    case MeasurementType::Double:
        writeBE(os, boost::any_cast<double>(m_data));
        break;
    case MeasurementType::INT8:
        writeBE(os, boost::any_cast<int8_t>(m_data));
        break;
    case MeasurementType::UINT8:
        writeBE(os, boost::any_cast<uint8_t>(m_data));
        break;
    case MeasurementType::INT16:
        writeBE(os, boost::any_cast<int16_t>(m_data));
        break;
    case MeasurementType::UINT16:
        writeBE(os, boost::any_cast<uint16_t>(m_data));
        break;
    case MeasurementType::INT32:
        writeBE(os, boost::any_cast<int32_t>(m_data));
        break;
    case MeasurementType::UINT32:
        writeBE(os, boost::any_cast<uint32_t>(m_data));
        break;
    case MeasurementType::INT64:
        writeBE(os, boost::any_cast<int64_t>(m_data));
        break;
    case MeasurementType::UINT64:
        writeBE(os, boost::any_cast<uint64_t>(m_data));
        break;
    case MeasurementType::Bool:
        writeBE(os, boost::any_cast<bool>(m_data));
        break;
    case MeasurementType::StdString:
        writeBE(os, uint32_t(boost::any_cast<std::string>(m_data).size()));
        os.write(boost::any_cast<std::string>(m_data).c_str(),
                 std::streamsize(boost::any_cast<std::string>(m_data).size()));
        break;
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

template<>
void Measurement::getAs<void>() const
{
    throw std::runtime_error("Not able to convert any type to void");
}

//==============================================================================

template<>
float Measurement::getAs<float>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to float");
    case MeasurementType::Float:
        return getData<float>();
    case MeasurementType::Double:
        return static_cast<float>(getData<double>());
    case MeasurementType::INT8:
        return static_cast<float>(getData<int8_t>());
    case MeasurementType::UINT8:
        return static_cast<float>(getData<uint8_t>());
    case MeasurementType::INT16:
        return static_cast<float>(getData<int16_t>());
    case MeasurementType::UINT16:
        return static_cast<float>(getData<uint16_t>());
    case MeasurementType::INT32:
        return static_cast<float>(getData<int32_t>());
    case MeasurementType::UINT32:
        return static_cast<float>(getData<uint32_t>());
    case MeasurementType::INT64:
        return static_cast<float>(getData<int64_t>());
    case MeasurementType::UINT64:
        return static_cast<float>(getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<float>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to float");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
double Measurement::getAs<double>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to double");
    case MeasurementType::Float:
        return static_cast<double>(getData<float>());
    case MeasurementType::Double:
        return getData<double>();
    case MeasurementType::INT8:
        return static_cast<double>(getData<int8_t>());
    case MeasurementType::UINT8:
        return static_cast<double>(getData<uint8_t>());
    case MeasurementType::INT16:
        return static_cast<double>(getData<int16_t>());
    case MeasurementType::UINT16:
        return static_cast<double>(getData<uint16_t>());
    case MeasurementType::INT32:
        return static_cast<double>(getData<int32_t>());
    case MeasurementType::UINT32:
        return static_cast<double>(getData<uint32_t>());
    case MeasurementType::INT64:
        return static_cast<double>(getData<int64_t>());
    case MeasurementType::UINT64:
        return static_cast<double>(getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<double>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to double");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
int8_t Measurement::getAs<int8_t>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to int8_t");
    case MeasurementType::Float:
        return static_cast<int8_t>(getData<float>());
    case MeasurementType::Double:
        return static_cast<int8_t>(getData<double>());
    case MeasurementType::INT8:
        return (getData<int8_t>());
    case MeasurementType::UINT8:
        return static_cast<int8_t>(getData<uint8_t>());
    case MeasurementType::INT16:
        return static_cast<int8_t>(getData<int16_t>());
    case MeasurementType::UINT16:
        return static_cast<int8_t>(getData<uint16_t>());
    case MeasurementType::INT32:
        return static_cast<int8_t>(getData<int32_t>());
    case MeasurementType::UINT32:
        return static_cast<int8_t>(getData<uint32_t>());
    case MeasurementType::INT64:
        return static_cast<int8_t>(getData<int64_t>());
    case MeasurementType::UINT64:
        return static_cast<int8_t>(getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<int8_t>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to int8_t");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
uint8_t Measurement::getAs<uint8_t>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to uint8_t");
    case MeasurementType::Float:
        return static_cast<uint8_t>(getData<float>());
    case MeasurementType::Double:
        return static_cast<uint8_t>(getData<double>());
    case MeasurementType::INT8:
        return static_cast<uint8_t>(getData<int8_t>());
    case MeasurementType::UINT8:
        return (getData<uint8_t>());
    case MeasurementType::INT16:
        return static_cast<uint8_t>(getData<int16_t>());
    case MeasurementType::UINT16:
        return static_cast<uint8_t>(getData<uint16_t>());
    case MeasurementType::INT32:
        return static_cast<uint8_t>(getData<int32_t>());
    case MeasurementType::UINT32:
        return static_cast<uint8_t>(getData<uint32_t>());
    case MeasurementType::INT64:
        return static_cast<uint8_t>(getData<int64_t>());
    case MeasurementType::UINT64:
        return static_cast<uint8_t>(getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<uint8_t>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to uint8_t");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
int16_t Measurement::getAs<int16_t>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to int16_t");
    case MeasurementType::Float:
        return static_cast<int16_t>(getData<float>());
    case MeasurementType::Double:
        return static_cast<int16_t>(getData<double>());
    case MeasurementType::INT8:
        return static_cast<int16_t>(getData<int8_t>());
    case MeasurementType::UINT8:
        return static_cast<int16_t>(getData<uint8_t>());
    case MeasurementType::INT16:
        return (getData<int16_t>());
    case MeasurementType::UINT16:
        return static_cast<int16_t>(getData<uint16_t>());
    case MeasurementType::INT32:
        return static_cast<int16_t>(getData<int32_t>());
    case MeasurementType::UINT32:
        return static_cast<int16_t>(getData<uint32_t>());
    case MeasurementType::INT64:
        return static_cast<int16_t>(getData<int64_t>());
    case MeasurementType::UINT64:
        return static_cast<int16_t>(getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<int16_t>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to int16_t");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
uint16_t Measurement::getAs<uint16_t>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to uint16_t");
    case MeasurementType::Float:
        return static_cast<uint16_t>(getData<float>());
    case MeasurementType::Double:
        return static_cast<uint16_t>(getData<double>());
    case MeasurementType::INT8:
        return static_cast<uint16_t>(getData<int8_t>());
    case MeasurementType::UINT8:
        return static_cast<uint16_t>(getData<uint8_t>());
    case MeasurementType::INT16:
        return static_cast<uint16_t>(getData<int16_t>());
    case MeasurementType::UINT16:
        return (getData<uint16_t>());
    case MeasurementType::INT32:
        return static_cast<uint16_t>(getData<int32_t>());
    case MeasurementType::UINT32:
        return static_cast<uint16_t>(getData<uint32_t>());
    case MeasurementType::INT64:
        return static_cast<uint16_t>(getData<int64_t>());
    case MeasurementType::UINT64:
        return static_cast<uint16_t>(getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<uint16_t>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to uint16_t");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
int32_t Measurement::getAs<int32_t>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to int32_t");
    case MeasurementType::Float:
        return static_cast<int32_t>(getData<float>());
    case MeasurementType::Double:
        return static_cast<int32_t>(getData<double>());
    case MeasurementType::INT8:
        return static_cast<int32_t>(getData<int8_t>());
    case MeasurementType::UINT8:
        return static_cast<int32_t>(getData<uint8_t>());
    case MeasurementType::INT16:
        return static_cast<int32_t>(getData<int16_t>());
    case MeasurementType::UINT16:
        return static_cast<int32_t>(getData<uint16_t>());
    case MeasurementType::INT32:
        return (getData<int32_t>());
    case MeasurementType::UINT32:
        return static_cast<int32_t>(getData<uint32_t>());
    case MeasurementType::INT64:
        return static_cast<int32_t>(getData<int64_t>());
    case MeasurementType::UINT64:
        return static_cast<int32_t>(getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<int32_t>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to int32_t");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
uint32_t Measurement::getAs<uint32_t>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to uint32_t");
    case MeasurementType::Float:
        return static_cast<uint32_t>(getData<float>());
    case MeasurementType::Double:
        return static_cast<uint32_t>(getData<double>());
    case MeasurementType::INT8:
        return static_cast<uint32_t>(getData<int8_t>());
    case MeasurementType::UINT8:
        return static_cast<uint32_t>(getData<uint8_t>());
    case MeasurementType::INT16:
        return static_cast<uint32_t>(getData<int16_t>());
    case MeasurementType::UINT16:
        return static_cast<uint32_t>(getData<uint16_t>());
    case MeasurementType::INT32:
        return static_cast<uint32_t>(getData<int32_t>());
    case MeasurementType::UINT32:
        return (getData<uint32_t>());
    case MeasurementType::INT64:
        return static_cast<uint32_t>(getData<int64_t>());
    case MeasurementType::UINT64:
        return static_cast<uint32_t>(getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<uint32_t>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to uint32_t");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
int64_t Measurement::getAs<int64_t>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to int64_t");
    case MeasurementType::Float:
        return static_cast<int64_t>(getData<float>());
    case MeasurementType::Double:
        return static_cast<int64_t>(getData<double>());
    case MeasurementType::INT8:
        return static_cast<int64_t>(getData<int8_t>());
    case MeasurementType::UINT8:
        return static_cast<int64_t>(getData<uint8_t>());
    case MeasurementType::INT16:
        return static_cast<int64_t>(getData<int16_t>());
    case MeasurementType::UINT16:
        return static_cast<int64_t>(getData<uint16_t>());
    case MeasurementType::INT32:
        return static_cast<int64_t>(getData<int32_t>());
    case MeasurementType::UINT32:
        return static_cast<int64_t>(getData<uint32_t>());
    case MeasurementType::INT64:
        return (getData<int64_t>());
    case MeasurementType::UINT64:
        return static_cast<int64_t>(getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<int64_t>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to int64_t");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
uint64_t Measurement::getAs<uint64_t>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to uint64_t");
    case MeasurementType::Float:
        return static_cast<uint64_t>(getData<float>());
    case MeasurementType::Double:
        return static_cast<uint64_t>(getData<double>());
    case MeasurementType::INT8:
        return static_cast<uint64_t>(getData<int8_t>());
    case MeasurementType::UINT8:
        return static_cast<uint64_t>(getData<uint8_t>());
    case MeasurementType::INT16:
        return static_cast<uint64_t>(getData<int16_t>());
    case MeasurementType::UINT16:
        return static_cast<uint64_t>(getData<uint16_t>());
    case MeasurementType::INT32:
        return static_cast<uint64_t>(getData<int32_t>());
    case MeasurementType::UINT32:
        return static_cast<uint64_t>(getData<uint32_t>());
    case MeasurementType::INT64:
        return static_cast<uint64_t>(getData<int64_t>());
    case MeasurementType::UINT64:
        return (getData<uint64_t>());
    case MeasurementType::Bool:
        return static_cast<uint64_t>(getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to uint64_t");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
bool Measurement::getAs<bool>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to bool");
    case MeasurementType::Float:
        return (getData<float>() == 0.0f);
    case MeasurementType::Double:
        return (getData<double>() == 0.0);
    case MeasurementType::INT8:
        return (getData<int8_t>() == 0);
    case MeasurementType::UINT8:
        return (getData<uint8_t>() == 0U);
    case MeasurementType::INT16:
        return (getData<int16_t>() == 0);
    case MeasurementType::UINT16:
        return (getData<uint16_t>() == 0U);
    case MeasurementType::INT32:
        return (getData<int32_t>() == 0);
    case MeasurementType::UINT32:
        return (getData<uint32_t>() == 0U);
    case MeasurementType::INT64:
        return (getData<int64_t>() == 0);
    case MeasurementType::UINT64:
        return (getData<uint64_t>() == 0U);
    case MeasurementType::Bool:
        return (getData<bool>());
    case MeasurementType::StdString:
        throw std::runtime_error("Not able to convert from std::str to float");
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

template<>
std::string Measurement::getAs<std::string>() const
{
    switch (this->getMeasurementType())
    {
    case MeasurementType::Void:
        throw std::runtime_error("Not able to convert from void to std::str");
    case MeasurementType::Float:
        throw std::runtime_error("Not able to convert from float to std::str");
    case MeasurementType::Double:
        throw std::runtime_error("Not able to convert from double to std::str");
    case MeasurementType::INT8:
        throw std::runtime_error("Not able to convert from int8_t to std::str");
    case MeasurementType::UINT8:
        throw std::runtime_error("Not able to convert from uint8_t to std::str");
    case MeasurementType::INT16:
        throw std::runtime_error("Not able to convert from int16_t to std::str");
    case MeasurementType::UINT16:
        throw std::runtime_error("Not able to convert from uint16_t to std::str");
    case MeasurementType::INT32:
        throw std::runtime_error("Not able to convert from int32_t to std::str");
    case MeasurementType::UINT32:
        throw std::runtime_error("Not able to convert from uint32_t to std::str");
    case MeasurementType::INT64:
        throw std::runtime_error("Not able to convert from int64_t to std::str");
    case MeasurementType::UINT64:
        throw std::runtime_error("Not able to convert from uint64_t to std::str");
    case MeasurementType::Bool:
        throw std::runtime_error("Not able to convert from bool to std::str");
    case MeasurementType::StdString:
        return (getData<std::string>());
    default:
        throw std::runtime_error("Unknown MeasurementType in Measurement");
    } // switch
}

//==============================================================================

bool Measurement::isEqual(const Measurement& m) const
{
    if ((getKey() != m.getKey()) || (getMeasurementType() != m.getMeasurementType()))
    {
        return false;
    }

    // Same key, same type. Now check the actual value.
    const MeasurementType mtype = typeIdToType(getType());
    switch (mtype)
    {
    case MeasurementType::Void:
        return true;
    case MeasurementType::Float:
        return floatEqual(getData<float>(), m.getData<float>());
    case MeasurementType::Double:
        return doubleEqual(getData<double>(), m.getData<double>());
    case MeasurementType::INT8:
        return getData<int8_t>() == m.getData<int8_t>();
    case MeasurementType::UINT8:
        return getData<uint8_t>() == m.getData<uint8_t>();
    case MeasurementType::INT16:
        return getData<int16_t>() == m.getData<int16_t>();
    case MeasurementType::UINT16:
        return getData<uint16_t>() == m.getData<uint16_t>();
    case MeasurementType::INT32:
        return getData<int32_t>() == m.getData<int32_t>();
    case MeasurementType::UINT32:
        return getData<uint32_t>() == m.getData<uint32_t>();
    case MeasurementType::INT64:
        return getData<int64_t>() == m.getData<int64_t>();
    case MeasurementType::UINT64:
        return getData<uint64_t>() == m.getData<uint64_t>();
    case MeasurementType::Bool:
        return getData<bool>() == m.getData<bool>();
    case MeasurementType::StdString:
        return getData<std::string>() == m.getData<std::string>();
    default:
        throw boost::bad_any_cast();
    }
}

//==============================================================================

Measurement::MeasurementType Measurement::typeIdToType(const std::type_info& tinfo)
{
    if (tinfo == typeid(void))
        return MeasurementType::Void;
    else if (tinfo == typeid(float))
        return MeasurementType::Float;
    else if (tinfo == typeid(double))
        return MeasurementType::Double;
    else if (tinfo == typeid(int8_t))
        return MeasurementType::INT8;
    else if (tinfo == typeid(uint8_t))
        return MeasurementType::UINT8;
    else if (tinfo == typeid(int16_t))
        return MeasurementType::INT16;
    else if (tinfo == typeid(uint16_t))
        return MeasurementType::UINT16;
    else if (tinfo == typeid(int32_t))
        return MeasurementType::INT32;
    else if (tinfo == typeid(uint32_t))
        return MeasurementType::UINT32;
    else if (tinfo == typeid(int64_t))
        return MeasurementType::INT64;
    else if (tinfo == typeid(uint64_t))
        return MeasurementType::UINT64;
    else if (tinfo == typeid(bool))
        return MeasurementType::Bool;
    else if (tinfo == typeid(std::string))
        return MeasurementType::StdString;
    else
    {
        LOGERROR(logger, "Unknown type_info in Measurement: " << tinfo.name());
        throw std::runtime_error("Unknown type_info in Measurement");
        //assert(false);
    }
    //return Float; // To avoid compiler warnings
}

//==============================================================================

bool operator==(const Measurement& lhs, const Measurement& rhs) { return lhs.isEqual(rhs); }

//==============================================================================

bool operator!=(const Measurement& lhs, const Measurement& rhs) { return !lhs.isEqual(rhs); }

//==============================================================================

std::ostream& operator<<(std::ostream& oss, const Measurement& m)
{
    oss << "Key=" << m.getKey() << " type=" << static_cast<uint8_t>(m.getMeasurementType()) << " ";

    switch (m.getMeasurementType())
    {
    case Measurement::MeasurementType::Float:
        oss << "Float(" << m.getData<float>() << ")";
        break;
    case Measurement::MeasurementType::Double:
        oss << "Double(" << m.getData<double>() << ")";
        break;
    case Measurement::MeasurementType::INT8:
        oss << "INT8(" << int(m.getData<int8_t>()) << ")";
        break;
    case Measurement::MeasurementType::UINT8:
        oss << "UINT8(" << int(m.getData<uint8_t>()) << ")";
        break;
    case Measurement::MeasurementType::INT16:
        oss << "INT16(" << m.getData<int16_t>() << ")";
        break;
    case Measurement::MeasurementType::UINT16:
        oss << "UINT16(" << m.getData<uint16_t>() << ")";
        break;
    case Measurement::MeasurementType::INT32:
        oss << "INT32(" << m.getData<int32_t>() << ")";
        break;
    case Measurement::MeasurementType::UINT32:
        oss << "UINT32(" << m.getData<uint32_t>() << ")";
        break;
    case Measurement::MeasurementType::INT64:
        oss << "INT64(" << m.getData<int64_t>() << ")";
        break;
    case Measurement::MeasurementType::UINT64:
        oss << "UINT64(" << m.getData<uint64_t>() << ")";
        break;
    case Measurement::MeasurementType::Bool:
        oss << "Bool(" << m.getData<bool>() << ")";
        break;
    case Measurement::MeasurementType::StdString:
        oss << "StdString(" << m.getData<std::string>() << ")";
        break;
    default:
        oss << "Undefined Type(..) ";
        break;
    }

    return oss;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
