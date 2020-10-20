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
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2271.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief List of objects for scala. With unfiltered and filtered object information.
//!
//! General data type: \ref ibeo::common::sdk::ObjectList
class ObjectList2271 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using ObjectVector = std::vector<ObjectIn2271>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.objectlist2271"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    ObjectList2271();
    ObjectList2271(const NTPTime scanStartTimeStamp);

    virtual ~ObjectList2271();

public: // getter
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    NTPTime getScanStartTimestamp() const { return m_scanStartTimestamp; }
    uint16_t getScanNumber() const { return m_scanNumber; }
    uint8_t getObjectListId() const { return m_objectListId; }
    uint8_t getDeviceId() const { return m_deviceId; }
    uint16_t getDeviceInterfaceVersion() const { return m_deviceInterfaceVersion; }

    uint32_t getReserved() const { return m_reserved; }

    uint16_t getNbOfObjects() const { return uint16_t(m_objects.size()); }
    const ObjectVector& getObjects() const { return m_objects; }
    ObjectVector& getObjects() { return m_objects; }

public: // setter
    void setScanStartTimestamp(const NTPTime& newNTPTime) { m_scanStartTimestamp = newNTPTime; }
    void setScanNumber(const uint16_t newScanNumber) { m_scanNumber = newScanNumber; }
    void setObjectListId(const uint8_t newObjectListId) { m_objectListId = newObjectListId; }
    void setDeviceId(const uint8_t newDeviceId) { m_deviceId = newDeviceId; }
    //========================================
    //! \brief Set the object list id. (14 bit value).
    //! \attention Only the lower 14 bits are used, i.e. the
    //!            device interface version is between 0 an 16383.
    //-------------------------------------
    void setDeviceInterfaceVersion(const uint16_t newDeviceInterfaceVersion)
    {
        assert((newDeviceInterfaceVersion & 0x3FFF) == newDeviceInterfaceVersion);
        m_deviceInterfaceVersion = (newDeviceInterfaceVersion & 0x3FFF);
    }

    void setReserved(const uint32_t newReserved) { m_reserved = newReserved; }
    void setObjects(const ObjectVector& objects) { m_objects = objects; }

protected:
    NTPTime m_scanStartTimestamp;
    uint16_t m_scanNumber{0};
    uint8_t m_objectListId{0};
    uint8_t m_deviceId{0};
    uint16_t m_deviceInterfaceVersion{0};
    uint32_t m_reserved{0};
    // uint16 number of objects
    ObjectVector m_objects{};
}; // ObjectList2271

//==============================================================================

bool operator==(const ObjectList2271& lhs, const ObjectList2271& rhs);
bool operator!=(const ObjectList2271& lhs, const ObjectList2271& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
