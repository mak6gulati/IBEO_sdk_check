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
//!\date 15.November 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84SequenceImporter2604.hpp>
#include <ibeo/common/sdk/datablocks/PositionWgs84.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::PositionWgs84Sequence;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_PositionWgs84_2604>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

class IdcFile;
class IbeoEcu;

template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial));

//==============================================================================

std::streamsize
Importer<C, DataTypeId::DataType_PositionWgs84_2604>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};

    try
    {
        container = &dynamic_cast<const C&>(c); // ignore the return value
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return container->getPositionSequence().front().getSerializedSize();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_PositionWgs84_2604>::deserialize(std::istream& is,
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

    PositionWgs84 positionWgs84;
    positionWgs84.deserialize(is);
    container->setPositionSequence(std::vector<PositionWgs84>{positionWgs84});

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
