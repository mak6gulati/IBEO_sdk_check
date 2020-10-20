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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/MeasurementKey.hpp>

#include <ibeo/common/sdk/misc/deprecatedwarning.hpp>

#include <ibeo/common/logging/logging.hpp>

#include <iostream>
#include <boost/any.hpp>
#include <boost/assert.hpp>

#include <stdexcept>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class Measurement
{
public:
    enum class MeasurementType : uint8_t
    {
        Void      = 0x00U,
        Float     = 0x01U,
        Double    = 0x02U,
        INT8      = 0x03U,
        UINT8     = 0x04U,
        INT16     = 0x05U,
        UINT16    = 0x06U,
        INT32     = 0x07U,
        UINT32    = 0x08U,
        INT64     = 0x09U,
        UINT64    = 0x0AU,
        Bool      = 0x0BU,
        StdString = 0x0CU
    };

public:
    Measurement();
    virtual ~Measurement() = default;

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public: // getter
    MeasurementKey getKey() const { return m_key; }
    MeasurementType getMeasurementType() const { return typeIdToType(getType()); }

    template<typename T>
    T getData() const
    {
        return boost::any_cast<T>(m_data);
    }

public: // setter
    void setKey(const MeasurementKey key) { m_key = key; }
    template<typename T>
    void setData(const T& data)
    {
        m_data = data;
    }

    template<typename T>
    void setValue(const MeasurementKey key, const T& value)
    {
        m_key  = key;
        m_data = value;
    }

    void resetValue() { m_data = boost::any(); }

    //========================================

public:
    template<typename T>
    T getAs() const
    {
        throw std::runtime_error("Only specializations are allowed.");
    }

    bool isEqual(const Measurement& m) const;

    template<typename T>
    bool isOfType() const
    {
        return m_data.type() == typeid(T);
    }

    static MeasurementType typeIdToType(const std::type_info& tinfo);
    const std::type_info& getType() const { return m_data.type(); }

protected:
    static constexpr const char* loggerId = "ibeo::common::sdk::Measurement";
    static ibeo::common::logging::LoggerSPtr logger;

protected:
    MeasurementKey m_key;
    //MeasurementType m_measurementType;
    boost::any m_data;
}; // Measurement

//==============================================================================
template<>
void Measurement::getAs<void>() const;

template<>
float Measurement::getAs<float>() const;

template<>
double Measurement::getAs<double>() const;

template<>
int8_t Measurement::getAs<int8_t>() const;

template<>
uint8_t Measurement::getAs<uint8_t>() const;

template<>
int16_t Measurement::getAs<int16_t>() const;

template<>
uint16_t Measurement::getAs<uint16_t>() const;

template<>
int32_t Measurement::getAs<int32_t>() const;

template<>
uint32_t Measurement::getAs<uint32_t>() const;

template<>
int64_t Measurement::getAs<int64_t>() const;

template<>
uint64_t Measurement::getAs<uint64_t>() const;

template<>
bool Measurement::getAs<bool>() const;

template<>
std::string Measurement::getAs<std::string>() const;
//==============================================================================

bool operator==(const Measurement& lhs, const Measurement& rhs);
bool operator!=(const Measurement& lhs, const Measurement& rhs);

//==============================================================================

std::ostream& operator<<(std::ostream& oss, const Measurement& m);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
