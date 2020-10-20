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

#include <ibeo/common/sdk/datablocks/Measurement.hpp>

#include <ibeo/common/sdk/misc/deprecatedwarning.hpp>

#include <vector>
#include <iostream>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class MeasurementList
{
public:
    using MeasurementVector = std::vector<Measurement>;

public:
    MeasurementList();

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    void addMeasurement(const Measurement& meas) { m_measurements.push_back(meas); }

public: // getter
    uint16_t getSize() const { return uint16_t(m_measurements.size()); }

    const MeasurementVector& getMeasurements() const { return m_measurements; }
    MeasurementVector& getMeasurements() { return m_measurements; }

    MeasurementVector::iterator getMeasurement(const MeasurementKey key);
    MeasurementVector::const_iterator getMeasurement(const MeasurementKey key) const;
    bool contains(const MeasurementKey key) const;

public: // setter
    void setMeasurements(const MeasurementVector& measurements) { m_measurements = measurements; }

protected:
    MeasurementVector m_measurements;
}; // MeasurementList

//==============================================================================

bool operator==(const MeasurementList& lhs, const MeasurementList& rhs);
bool operator!=(const MeasurementList& lhs, const MeasurementList& rhs);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
