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
//!\date Jan 29, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/ogpsimumessage/special/OGpsImuMessage2610Importer2610.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/canmessage/CanMessage1002Importer1002.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::OGpsImuMessage2610;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_OGpsImuMessage2610>;
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
Importer<C, DataTypeId::DataType_OGpsImuMessage2610>::getSerializedSize(const DataContainerBase& c) const
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

    return std::streamsize(sizeof(uint32_t) + (sizeof(uint8_t) * container->getData().size()));
}
//==============================================================================

bool Importer<C, DataTypeId::DataType_OGpsImuMessage2610>::deserialize(std::istream& is,
                                                                       DataContainerBase& c,
                                                                       const IbeoDataHeader& dh) const
{
    C* container{nullptr};
    try
    {
        container = &dynamic_cast<C&>(c); // ignore the return value
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    container->setDataHeader(dh);

    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, container->m_ipAddress);

    {
        std::vector<uint8_t>::size_type dataSize = dh.getMessageSize() - sizeof(uint32_t);

        if (container->m_data.size() != dataSize)
            container->m_data.resize(dataSize);
    }

    std::vector<uint8_t>::iterator objIter = container->m_data.begin();
    for (; objIter != container->m_data.end(); ++objIter)
    {
        ibeo::common::sdk::readBE(is, *objIter);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
