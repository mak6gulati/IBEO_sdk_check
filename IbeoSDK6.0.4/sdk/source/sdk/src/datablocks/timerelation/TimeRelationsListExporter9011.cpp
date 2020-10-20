//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Apr 10, 2018
///-----------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/timerelation/TimeRelationsListExporter9011.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::TimeRelationsList;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_TimeRelationsList9011>::getSerializedSize(const DataContainerBase& c) const
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

    for (const auto& relation : container->getTimeRelations())
    {
        result += std::streamsize(sizeof(uint32_t));
        result += relation.first.getSerializedSize();
        result += (static_cast<int>(relation.second.getEntryList().size())
                   * ((4 * std::streamsize(sizeof(NTPTime))) + (2 * std::streamsize(sizeof(double)))));
    }

    return result;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_TimeRelationsList9011>::serialize(std::ostream& outStream,
                                                                        const DataContainerBase& c) const
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

    const int64_t startPos = streamposToInt64(outStream.tellp());

    // serialize: reference clock
    container->getRefTimeType().serialize(outStream);

    // serialize: number of relations
    const uint8_t relationsCount = static_cast<uint8_t>(container->getTimeRelations().size());
    ibeo::common::sdk::writeBE(outStream, relationsCount);

    for (const auto& relation : container->getTimeRelations())
    {
        relation.first.serialize(outStream);
        ibeo::common::sdk::writeBE(outStream, static_cast<uint32_t>(relation.second.getEntryList().size()));
        for (const auto& entry : relation.second.getEntryList())
        {
            ibeo::common::sdk::writeBE(outStream, NTPTime(entry.m_refTime));
            ibeo::common::sdk::writeBE(
                outStream, NTPTime(boost::posix_time::ptime(boost::gregorian::date(1900, 1, 1)) + entry.m_otherTime));

            if (entry.m_optionalData == nullptr)
            {
                ibeo::common::sdk::writeBE(outStream, NTPTime::getInvalidTime());
                ibeo::common::sdk::writeBE(outStream, NTPTime::getInvalidTime());
                ibeo::common::sdk::writeBE(outStream, entry.m_factor);
                ibeo::common::sdk::writeBE(outStream, ibeo::common::sdk::NaN_double);
            }
            else
            {
                ibeo::common::sdk::writeBE(outStream,
                                           NTPTime(boost::posix_time::ptime(boost::gregorian::date(1900, 1, 1))
                                                   + entry.m_optionalData->m_standardError));
                ibeo::common::sdk::writeBE(outStream,
                                           NTPTime(boost::posix_time::ptime(boost::gregorian::date(1900, 1, 1))
                                                   + entry.m_optionalData->m_maxDeviation));
                ibeo::common::sdk::writeBE(outStream, entry.m_factor);
                ibeo::common::sdk::writeBE(outStream, entry.m_optionalData->m_correlationCoefficient);
            }
        }
    }

    return !outStream.fail() && ((streamposToInt64(outStream.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
