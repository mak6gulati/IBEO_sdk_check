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
//!\date Apr 27, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<ObjectList, DataTypeId::DataType_ObjectList2271>
  : public RegisteredImporter<ObjectList, DataTypeId::DataType_ObjectList2271>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;
    virtual bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& header) const override;

private:
    static const uint8_t attributesFlagUnfilteredAttributesContourAvailable{0x01};
    static const uint8_t attributesFlagUnfilteredAttributesAvailable{0x02};
    static const uint8_t attributesFlagFilteredAttributesContourAvailable{0x04};
    static const uint8_t attributesFlagFilteredAttributesAvailable{0x08};

private:
    static constexpr float yawRateScalingFactor{10000.0F};
    static constexpr float objectBoxHeightScalingFactor{3.0F};

    // Deserialize the general object in context of a data container type 0x2271.
    std::streamsize getSerializedSize(const Object& object) const;
    bool deserialize(std::istream& is, Object& object, const NTPTime& containerTimestamp) const;

    std::streamsize getSerializedSize(const UnfilteredObjectData& objectData) const;
    bool deserialize(std::istream& is,
                     UnfilteredObjectData& objectData,
                     const NTPTime& containerTimestamp,
                     const bool hasContourPoints) const;

    static std::streamsize getContourPointSerializedSize();
    bool deserialize(std::istream& is, ContourPoint& cpData) const;

    bool hasFilteredObjectData(const Object& object) const;
    void resetFilteredObjectData(Object& object) const;
}; // ObjectListImporter2271

//==============================================================================

using ObjectListImporter2271 = Importer<ObjectList, DataTypeId::DataType_ObjectList2271>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
