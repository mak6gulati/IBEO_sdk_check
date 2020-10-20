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
//!\date Jan 14, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2205Importer2205.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::Scan2205;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Scan2205>;
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

std::streamsize Importer<C, DataTypeId::DataType_Scan2205>::getSerializedSize(const DataContainerBase& c) const
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

    return std::streamsize(sizeof(NTPTime)) + std::streamsize(2 * sizeof(uint32_t))
           + std::streamsize(2 * sizeof(uint16_t)) + std::streamsize(sizeof(uint8_t)) + 3
           + std::streamsize(uint8_t(container->m_scannerInfos.size())) * ScannerInfoIn2205::getSerializedSize_static()
           + std::streamsize(uint32_t(container->m_scanPoints.size()))
                 * ScanPointIn2205::getSerializedSize_static(); //todo ????
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Scan2205>::deserialize(std::istream& is,
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

    ibeo::common::sdk::readBE(is, container->m_scanStartTime);
    ibeo::common::sdk::readBE(is, container->m_endTimeOffset);

    ibeo::common::sdk::readBE(is, container->m_flags);
    ibeo::common::sdk::readBE(is, container->m_scanNumber);

    uint16_t nbScanPts = 0;
    ibeo::common::sdk::readBE(is, nbScanPts);
    container->m_scanPoints.resize(nbScanPts);

    uint8_t nbScanInfos = 0;
    ibeo::common::sdk::readBE(is, nbScanInfos);
    container->m_scannerInfos.resize(nbScanInfos);

    ibeo::common::sdk::readBE(is, container->m_reserved0);
    ibeo::common::sdk::readBE(is, container->m_reserved1);

    for (uint8_t i = 0; i < nbScanInfos; ++i)
    {
        container->m_scannerInfos[i].deserialize(is);
    }

    for (uint16_t i = 0; i < nbScanPts; ++i)
    {
        container->m_scanPoints[i].deserialize(is);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
