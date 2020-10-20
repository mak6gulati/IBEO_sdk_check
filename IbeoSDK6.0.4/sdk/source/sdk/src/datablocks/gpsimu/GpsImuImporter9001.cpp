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
//!\date Jan 31, 2019
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/gpsimu/GpsImuImporter9001.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001Importer9001.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/GpsImu.hpp>

//==============================================================================

#include <ibeo/common/sdk/datablocks/eventtag/EventTag7000Importer7000.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::GpsImu;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_GpsImu9001>;
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

std::streamsize Importer<C, DataTypeId::DataType_GpsImu9001>::getSerializedSize(const DataContainerBase& c) const
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

    const GpsImu9001Importer9001 delegate;
    return delegate.getSerializedSize(container->m_delegate);
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_GpsImu9001>::deserialize(std::istream& is,
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

    const GpsImu9001Importer9001 delegate;
    return delegate.deserialize(is, container->m_delegate, dh);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
