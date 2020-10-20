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
//!\date Aug 29, 2018
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/datablocks/trafficlight/special/TrafficLightStateList3600Importer3600.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================

namespace {
using C  = ibeo::common::sdk::TrafficLightStateList3600;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_TrafficLight3600>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_TrafficLight3600>::getSerializedSize(const DataContainerBase& c) const
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

    return static_cast<std::streamsize>(container->m_trafficLightStates.size())
               * TrafficLightStateIn3600::getSerializedSize_static()
           + 8;
}

bool Importer<C, DataTypeId::DataType_TrafficLight3600>::deserialize(std::istream& is,
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
    uint64_t nbOfTrafficLightStates;
    readBE(is, nbOfTrafficLightStates);

    container->m_trafficLightStates.resize(nbOfTrafficLightStates);

    for (uint64_t i = 0; i < nbOfTrafficLightStates; ++i)
    {
        container->m_trafficLightStates[i].deserialize(is);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
