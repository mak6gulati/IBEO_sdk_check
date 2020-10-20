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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/timerecord/TimeRecord9000Importer9000.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::TimeRecord9000;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_TimeRecord9000>;
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

std::streamsize Importer<C, DataTypeId::DataType_TimeRecord9000>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize result = serializedBaseSize;
    result += container->m_externalClockType.getSerializedSize();
    result += container->m_internalClockType.getSerializedSize();
    result += std::streamsize(8 * container->m_externalClockTimes.size());
    result += std::streamsize(8 * container->m_internalClockTimes.size());
    result += std::streamsize(sizeof(uint8_t) * container->m_fixModes.size());
    return result;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_TimeRecord9000>::deserialize(std::istream& is,
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

    if (!container->m_externalClockType.deserialize(is))
    {
        return false;
    }
    if (!container->m_internalClockType.deserialize(is))
    {
        return false;
    }

    uint32_t nbOfEntries = 0;
    ibeo::common::sdk::readBE(is, nbOfEntries);

    container->m_externalClockTimes.resize(nbOfEntries);
    for (auto& ect : container->m_externalClockTimes)
    {
        readBE(is, ect);
    }

    container->m_internalClockTimes.resize(nbOfEntries);
    for (auto& ict : container->m_internalClockTimes)
    {
        readBE(is, ict);
    }

    container->m_fixModes.resize(nbOfEntries);
    for (auto& fm : container->m_fixModes)
    {
        uint8_t fixMode;
        ibeo::common::sdk::readBE(is, fixMode);
        fm = static_cast<C::FixMode>(fixMode);
    }

    for (auto& r : container->m_reserved)
    {
        readBE(is, r);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
