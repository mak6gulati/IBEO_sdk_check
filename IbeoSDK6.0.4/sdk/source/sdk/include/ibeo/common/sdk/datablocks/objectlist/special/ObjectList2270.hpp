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
//!\date Jan 17, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2270.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief List of objects with extended tracking information in the format of the LUX4/Scala145 firmware
//!
//! General data type: \ref ibeo::common::sdk::ObjectList
class ObjectList2270 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using ObjectVector = std::vector<ObjectIn2270>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.objectlist2270"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    ObjectList2270();
    ObjectList2270(const NTPTime scanStartTimeStamp);
    virtual ~ObjectList2270();

public:
    const ObjectIn2270* findObject(const uint16_t id) const;
    void addObject(const ObjectIn2270& newObj);

public: // getter
    NTPTime getScanStartTimestamp() const { return m_scanStartTimestamp; }
    uint16_t getScanNumber() const { return m_scanNumber; }
    uint16_t getNbOfObjects() const { return static_cast<uint16_t>(m_objects.size()); }
    const ObjectVector& getObjects() const { return m_objects; }
    ObjectVector& getObjects() { return m_objects; }

public: // setter
    void setScanStartTimeStamp(const NTPTime newScanStartTimeStamp) { m_scanStartTimestamp = newScanStartTimeStamp; }
    void setScanNumber(const uint16_t newScanNumber) { m_scanNumber = newScanNumber; }

protected:
    NTPTime m_scanStartTimestamp;
    uint16_t m_scanNumber{0};
    ObjectVector m_objects{};
}; // ObjectList2270

//==============================================================================

//==============================================================================

bool operator==(const ObjectList2270& lhs, const ObjectList2270& rhs);
bool operator!=(const ObjectList2270& lhs, const ObjectList2270& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
