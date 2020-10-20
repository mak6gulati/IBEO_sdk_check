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
//!\date Jan 12, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/canmessage/CanMessage1002Importer1002.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::CanMessage1002;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_CanMessage1002>;
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
class IbeoScala;
class IbeoTrackingBox;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
            ContainerBufferAndImporterProviderGlobal<IbeoTrackingBox>::getInstance().registerImporter(
                registeredImporterInitial))));

//==============================================================================

//==============================================================================

template<>
inline void readBE<C::MsgType>(std::istream& is, C::MsgType& value)
{
    uint8_t tmp;
    readBE(is, tmp);
    value = C::MsgType(tmp);
}
//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_CanMessage1002>::getSerializedSize(const DataContainerBase& c) const
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

    return 1 + container->m_length + 1 + (container->hasExtendedCanId() ? 4 : 2)
           + (container->hasValidTimestamp() ? 12 : 0) + 1;
}
//==============================================================================

bool Importer<C, DataTypeId::DataType_CanMessage1002>::deserialize(std::istream& is,
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

    const unsigned int extTsBitMask = ibeo::common::sdk::CanMessage1002::extTsBitMask;
    const unsigned int stdTsBitMask = ibeo::common::sdk::CanMessage1002::stdTsBitMask;

    const int64_t startPos = streamposToInt64(is.tellg());

    uint8_t lenVer;
    ibeo::common::sdk::readBE(is, lenVer);
    container->m_version = lenVer & 0x0F;
    container->m_length  = (lenVer >> 4) & 0x0F;

    for (uint_fast8_t i = 0; i < container->m_length; ++i)
    {
        ibeo::common::sdk::readBE(is, container->m_data[i]);
    }

    ibeo::common::sdk::readBE(is, container->m_msgType);

    bool hasRecvTimestamp = false;

    if (container->hasExtendedCanId())
    {
        ibeo::common::sdk::readBE(is, container->m_canId);
        hasRecvTimestamp = (container->m_canId & extTsBitMask) == extTsBitMask;
        container->m_canId &= ~extTsBitMask;
    }
    else
    {
        uint16_t canId;
        ibeo::common::sdk::readBE(is, canId);
        container->m_canId = canId;
        hasRecvTimestamp   = (container->m_canId & stdTsBitMask) == stdTsBitMask;
        container->m_canId &= ~stdTsBitMask;
    }

    if (hasRecvTimestamp)
    {
        ibeo::common::sdk::readBE(is, container->m_usSinceStartup);
        ibeo::common::sdk::readBE(is, container->m_timestamp);
    }
    else
    {
        container->m_usSinceStartup = 0;
        container->m_timestamp.setInvalid();
    }

    ibeo::common::sdk::readBE(is, container->m_deviceId);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
