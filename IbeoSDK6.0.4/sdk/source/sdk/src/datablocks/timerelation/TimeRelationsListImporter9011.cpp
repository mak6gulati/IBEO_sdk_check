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

#include <ibeo/common/sdk/datablocks/timerelation/TimeRelationsListImporter9011.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9011Importer9011.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::TimeRelationsList;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_TimeRelationsList9011>;
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
Importer<C, DataTypeId::DataType_TimeRelationsList9011>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize result = container->getRefTimeType().getSerializedSize() + std::streamsize(sizeof(uint8_t));

    TimeRelationsList::TimeRelationsMap relationsMap = container->getTimeRelations();
    for (auto& itr : relationsMap)
    {
        result += std::streamsize(sizeof(uint32_t)) + (itr.first.getSerializedSize());
        result += static_cast<std::streamsize>(
            itr.second.getEntryList().size()
            * ((4 * std::streamsize(sizeof(NTPTime))) + (2 * std::streamsize(sizeof(double)))));
    }

    return result;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_TimeRelationsList9011>::deserialize(std::istream& is,
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

    const int64_t startPos = streamposToInt64(is.tellg());

    TimeRelationsList9011 trl9011;
    TimeRelationsList9011Importer9011 trl9011Importer;
    if (!trl9011Importer.deserialize(is, trl9011, dh))
    {
        return false;
    }
    *container = trl9011;

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
