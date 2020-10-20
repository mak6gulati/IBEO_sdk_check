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
//! \date Apr 26, 2012
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class ResolutionInfoIn2205
{
public:
    ResolutionInfoIn2205();
    ResolutionInfoIn2205(const ResolutionInfoIn2205& src);
    virtual ~ResolutionInfoIn2205() = default;

public:
    ResolutionInfoIn2205& operator=(const ResolutionInfoIn2205& src);

public:
    static std::streamsize getSerializedSize_static();

public:
    virtual std::streamsize getSerializedSize() const { return getSerializedSize_static(); }

    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public: // getter
    float getResolutionStartAngle() const { return m_resolutionStartAngle; }
    float getResolution() const { return m_resolution; }

public: // setter
    void setResolutionStartAngle(const float newResolutionStartAngle)
    {
        m_resolutionStartAngle = newResolutionStartAngle;
    }
    void setResolution(const float newResolution) { m_resolution = newResolution; }

public:
    bool operator==(const ResolutionInfoIn2205& other) const;
    bool operator!=(const ResolutionInfoIn2205& other) const { return !((*this) == other); }

protected:
    float m_resolutionStartAngle; // TODO: define FLOAT32
    float m_resolution; // TODO: define FLOAT32    // [rad]
}; // ResolutionInfo

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
