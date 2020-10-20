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
//!\date Mar 9, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/special/FramingPolicyIn6130.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndexEntryIn6130.hpp>
#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <vector>
#include <string>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Ibeo frame index
//!
//! General data type: \ref ibeo::common::sdk::FrameIndex
class FrameIndex6130 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using FrameVector = std::vector<FrameIndexEntryIn6130>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.frameindex6130"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    FrameIndex6130() : SpecializedDataContainer() {}
    virtual ~FrameIndex6130() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    const FramingPolicyIn6130& getFramingPolicy() const { return m_framingPolicy; }

    const FrameVector& getFrameIndices() const { return m_frameIndices; }
    FrameVector getFrameIndices() { return m_frameIndices; }

    uint64_t getTimeOffsetMs() const { return m_timeOffsetMs; }

public:
    void setFramingPolicy(const FramingPolicyIn6130& policy) { m_framingPolicy = policy; }
    void setFrameIndices(const FrameVector& frameIndices) { m_frameIndices = frameIndices; }

public:
    void addFrame(const FrameIndexEntryIn6130& entry)
    {
        m_frameIndices.push_back(entry);
        m_timeOffsetMs = entry.getTimeOffsetMs();
    }

public:
    void clearFrames() { m_frameIndices.clear(); }

public:
    static constexpr uint8_t majorVersion{2};
    static constexpr uint8_t minorVersion{1};
    constexpr static const char* const nameString{"FRAMEINDEX_HEADER"};

protected:
    FramingPolicyIn6130 m_framingPolicy; //!< The FramingPolicy that has been used to generate the FrameIndex6130
    FrameVector m_frameIndices; //!< entries in this FrameIndex6130

protected:
    uint64_t m_timeOffsetMs{0}; //!< time offset of the last frame in milliseconds
}; // FrameIndex6130

//==============================================================================

bool operator==(const FrameIndex6130& lhs, const FrameIndex6130& rhs);
bool operator!=(const FrameIndex6130& lhs, const FrameIndex6130& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
