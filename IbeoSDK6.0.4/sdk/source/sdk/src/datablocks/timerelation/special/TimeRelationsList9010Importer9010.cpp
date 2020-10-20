//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date March 15, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9010Importer9010.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::TimeRelationsList9010;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_TimeRelationsList9010>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
// Specializations for RegisteredImporter
//==============================================================================

//generate link between data-type-id/importer and importer create function <dtid, ImpHash> ==> Imp::create

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

//registering ... (create map)
//add all device that can receive any datatype that can be imported to GeneralDataTypeContainer
class IdcFile;
class IbeoEcu;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial));

//==============================================================================

//==============================================================================

std::streamsize
Importer<C, DataTypeId::DataType_TimeRelationsList9010>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    std::streamsize result = std::streamsize(sizeof(uint8_t)) + std::streamsize(sizeof(uint32_t));

    for (auto& trme : container->m_timeRelationsMap)
    {
        result += trme.first.getSerializedSize(); // 2
        result += trme.second.getSerializedSize();
    }

    return result;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_TimeRelationsList9010>::deserialize(std::istream& is,
                                                                          DataContainerBase& c,
                                                                          const IbeoDataHeader& dh) const
{
    C* container{nullptr};
    try
    {
        container = &dynamic_cast<C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    container->setDataHeader(dh);

    const int64_t startPos = streamposToInt64(is.tellg());

    uint8_t version;
    ibeo::common::sdk::readBE(is, version);

    uint32_t relationsCount;
    ibeo::common::sdk::readBE(is, relationsCount);

    for (uint32_t i = 0; i < relationsCount; ++i)
    {
        ClockType clockType;
        clockType.deserialize(is);
        if (container->m_timeRelationsMap.count(clockType) == 1)
        {
            // duplicated time relation
            return false;
        }
        TimeRelationIn9010 tr9010;
        tr9010.deserialize(is);
        container->m_timeRelationsMap[clockType] = tr9010;
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
