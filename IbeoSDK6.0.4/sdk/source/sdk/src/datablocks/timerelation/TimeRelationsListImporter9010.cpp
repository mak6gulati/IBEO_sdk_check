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

#include <ibeo/common/sdk/datablocks/timerelation/TimeRelationsListImporter9010.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9010Importer9010.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::TimeRelationsList;
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

    for (const auto& relation : container->m_timeRelationsMap)
    {
        result += std::streamsize(sizeof(uint32_t)) + relation.first.getSerializedSize();
        for (const auto& entry : relation.second.getEntryList())
        {
            const uint8_t hasData = static_cast<uint8_t>(!std::isnan(entry.m_factor));
            result += std::streamsize(sizeof(NTPTime)) + std::streamsize(sizeof(uint8_t));
            if (hasData)
            {
                result += std::streamsize(sizeof(uint64_t)) + std::streamsize(sizeof(double));
            }
        }
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

    //const int64_t startPos = streamposToInt64(is.tellg());

    TimeRelationsList9010 trl9010;
    TimeRelationsList9010Importer9010 trl9010Importer;
    if (!trl9010Importer.deserialize(is, trl9010, dh))
    {
        return false;
    }
    *container = trl9010;

    return true;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
