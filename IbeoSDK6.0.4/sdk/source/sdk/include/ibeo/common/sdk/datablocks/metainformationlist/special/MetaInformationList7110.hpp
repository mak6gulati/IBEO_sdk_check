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
//! \date Feb 02, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationUnsupportedIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationFactory.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <unordered_map>
#include <vector>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \brief Ibeo meta information list
//!
//! The meta information datatype is used to store configurations, version numbers, keywords and other meta information.
//!
//! General data container: \ref ibeo::common::sdk::MetaInformationList
class MetaInformationList7110 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;

    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using MetaInformationSPtrVector = std::vector<MetaInformationBaseIn7110SPtr>;
    using MetaInformationMap
        = std::unordered_map<MetaInformationBaseIn7110::MetaInformationType, MetaInformationSPtrVector, EnumClassHash>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.metainformationlist7110"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    MetaInformationList7110() : SpecializedDataContainer(), m_metaInformations() {}
    virtual ~MetaInformationList7110() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    const MetaInformationMap& getMetaInformationMap() const { return m_metaInformations; }

    void addMetaInformation(const MetaInformationBaseIn7110SPtr info);

    uint32_t getNumberOfMetaInformationElements() const;
    uint32_t getNumberOfMetaInformationTypes() const;

    template<class T>
    std::vector<T> getMetaInformations(const MetaInformationBaseIn7110::MetaInformationType infoType)
    {
        std::vector<T> ret;

        if (m_metaInformations.find(infoType) == m_metaInformations.end())
        {
            return ret;
        }

        for (const MetaInformationBaseIn7110SPtr& info : m_metaInformations[infoType])
        {
            ret.push_back(std::dynamic_pointer_cast<T>(info));
        }
        return ret;
    }

    void deleteInformation(const MetaInformationBaseIn7110SPtr& info);
    void deleteInformationForType(const MetaInformationBaseIn7110::MetaInformationType infoType);

    void printStatistic(std::ostream& os) const;

protected:
    class MetaInformationHeader
    {
    public:
        bool deserialize(std::istream& is);

    public:
        MetaInformationBaseIn7110::MetaInformationType m_type;
        NTPTime m_timeStamp;
        uint32_t m_payloadSize;
    }; // MetaInformationHeader

protected:
    static bool isSame(const MetaInformationBaseIn7110SPtr info1, const MetaInformationBaseIn7110SPtr info2)
    {
        return info1 == info2;
    }

protected:
    MetaInformationMap m_metaInformations;
}; // MetaInformationList

//==============================================================================

bool operator==(const MetaInformationList7110& lhs, const MetaInformationList7110& rhs);
inline bool operator!=(const MetaInformationList7110& lhs, const MetaInformationList7110& rhs) { return !(lhs == rhs); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
