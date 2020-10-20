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
//!\date Jan 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringSystemStatus6705Importer6705.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::SystemMonitoringSystemStatus6705;
using R
    = ibeo::common::sdk::RegisteredImporter<C,
                                            ibeo::common::sdk::DataTypeId::DataType_SystemMonitoringSystemStatus6705>;
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
Importer<C, DataTypeId::DataType_SystemMonitoringSystemStatus6705>::getSerializedSize(const DataContainerBase& c) const
{
    try
    {
        (void)dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return serializedSize;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_SystemMonitoringSystemStatus6705>::deserialize(std::istream& is,
                                                                                     DataContainerBase& c,
                                                                                     const IbeoDataHeader& dh) const
{
    C* container = dynamic_cast<C*>(&c);
    if (!container)
    {
        //casting failed
        assert(container);
        return false;
    }

    container->setDataHeader(dh);

    const int64_t startPos = streamposToInt64(is.tellg());

    const boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
    int64_t buffer;
    ibeo::common::sdk::readBE(is, buffer);
    // convert milliseconds to ptime
    container->m_lastUpdateTimestamp = epoch + boost::posix_time::milliseconds(buffer);

    ibeo::common::sdk::readBE(is, container->m_state);
    ibeo::common::sdk::readBE(is, container->m_stateInformation);
    ibeo::common::sdk::readBE(is, container->m_currentCpuUsage);
    ibeo::common::sdk::readBE(is, container->m_currentRamUsage);
    ibeo::common::sdk::readBE(is, container->m_currentHddUsage);
    ibeo::common::sdk::readBE(is, container->m_hddWarningLevelPercent);
    ibeo::common::sdk::readBE(is, container->m_hddErrorLevelPercent);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
