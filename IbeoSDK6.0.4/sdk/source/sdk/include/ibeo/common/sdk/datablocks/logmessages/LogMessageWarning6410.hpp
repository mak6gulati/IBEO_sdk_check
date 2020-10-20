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
//!\date Mar 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessage64x0Base.hpp>
#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Ibeo FUSION SYSTEM/ECU Trace Messages
//!
//! Software modules that are deploying the Ibeo FUSION SYSTEM for communication can sent trace messages
//! consisting of a character string. Trace Messages are distributed with four different data types dependent
//! on their priority
class LogMessageWarning6410 : public LogMessage64x0Base, public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;
    template<class ContainerType>
    friend class LogMessage64x0Exporter64x0Base;
    template<class ContainerType>
    friend class LogMessage64x0Importer64x0Base;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.logmessagewarning6410"};
    constexpr static const TraceLevel msgTraceLevel{TraceLevel::Warning};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    LogMessageWarning6410();

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    virtual TraceLevel getTraceLevel() const override { return msgTraceLevel; }
}; // LogMessageWarning6410

//==============================================================================

bool operator==(const LogMessageWarning6410& lhs, const LogMessageWarning6410& rhs);
bool operator!=(const LogMessageWarning6410& lhs, const LogMessageWarning6410& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
