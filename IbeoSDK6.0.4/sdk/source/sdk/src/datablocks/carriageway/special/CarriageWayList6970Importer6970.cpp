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
//!\date Apr 4, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6970Importer6970.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6970SerializedSize6970.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::CarriageWayList6970;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_CarriageWayList6970>;
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

std::streamsize
Importer<C, DataTypeId::DataType_CarriageWayList6970>::getSerializedSize(const DataContainerBase& c) const
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

    return CarriageWayList6970SerializedSize6970::getSerializedSize(*container);
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_CarriageWayList6970>::deserialize(std::istream& is,
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

    uint64_t nbOfWays;
    ibeo::common::sdk::readBE(is, nbOfWays);

    container->m_carriageWays.resize(nbOfWays);
    for (lanes::CarriageWayIn6970::Ptr& way : container->m_carriageWays)
    {
        way = lanes::CarriageWayIn6970::create();

        if (!deserialize(is, *way))
        {
            return false;
        }

        way->resolveConnections(way);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_CarriageWayList6970>::deserialize(std::istream& is, lanes::CarriageWayIn6970& cw)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, cw.m_id);
    readBE(is, cw.m_nationalId);
    uint8_t type;
    readBE(is, type);
    cw.m_type = static_cast<lanes::CarriageWayType>(type);

    uint64_t nbOfCwSegments;
    readBE(is, nbOfCwSegments);

    for (uint64_t i = 0; i < nbOfCwSegments; ++i)
    {
        lanes::CarriageWaySegmentIn6970::Ptr segment = lanes::CarriageWaySegmentIn6970::create();
        deserialize(is, *segment);
        cw.insert(segment);
    }

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos)
               == CarriageWayList6970SerializedSize6970::getSerializedSize(cw));
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_CarriageWayList6970>::deserialize(std::istream& is,
                                                                        lanes::CarriageWaySegmentIn6970& cws)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, cws.m_id);
    uint8_t nbOfLanes{0};
    readBE(is, nbOfLanes);
    readBE(is, cws.m_nextId);
    readBE(is, cws.m_prevId);

    for (uint16_t i = 0; i < nbOfLanes; ++i)
    {
        lanes::LaneIn6970::Ptr lane = lanes::LaneIn6970::create();
        if (!deserialize(is, *lane))
        {
            return false;
        }

        if (!cws.insert(lane))
        {
            // is this test correct here?
            return false;
        }
    } // for

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos)
               == CarriageWayList6970SerializedSize6970::getSerializedSize(cws));
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_CarriageWayList6970>::deserialize(std::istream& is, lanes::LaneIn6970& lane)
{
    lane.m_laneSegmentsMap.clear();

    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, lane.m_id);
    readBE(is, lane.m_laneId);
    {
        uint8_t type;
        readBE(is, type);
        lane.m_type = static_cast<lanes::LaneType>(type);
    }
    readBE(is, lane.m_nextLaneId);
    readBE(is, lane.m_prevLaneId);
    readBE(is, lane.m_leftLaneId);
    readBE(is, lane.m_rightLaneId);
    uint64_t nbOfSegments;
    readBE(is, nbOfSegments);

    // read segments
    for (uint64_t i = 0; i < nbOfSegments; ++i)
    {
        lanes::LaneSegmentIn6970::Ptr seg = lanes::LaneSegmentIn6970::create();
        if (!deserialize(is, *seg))
        {
            return false;
        }

        if (!lane.insert(seg))
        {
            // is the test correct here?
            return false;
        }
    }

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos)
               == CarriageWayList6970SerializedSize6970::getSerializedSize(lane));
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_CarriageWayList6970>::deserialize(std::istream& is,
                                                                        lanes::LaneSegmentIn6970& laneSeg)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, laneSeg.m_id);

    readBE(is, laneSeg.m_nextId);
    readBE(is, laneSeg.m_prevId);
    readBE(is, laneSeg.m_leftId);
    readBE(is, laneSeg.m_rightId);

    uint8_t laneMarkingType;
    readBE(is, laneMarkingType);
    laneSeg.m_markingLeft = static_cast<lanes::LaneMarkingType>(laneMarkingType);
    readBE(is, laneMarkingType);
    laneSeg.m_markingRight = static_cast<lanes::LaneMarkingType>(laneMarkingType);

    uint8_t laneBoundaryType;
    readBE(is, laneBoundaryType);
    laneSeg.m_boundaryLeft = static_cast<lanes::LaneBoundaryType>(laneBoundaryType);
    readBE(is, laneBoundaryType);
    laneSeg.m_boundaryRight = static_cast<lanes::LaneBoundaryType>(laneBoundaryType);

    readBE(is, laneSeg.m_nextInNewSeg);
    readBE(is, laneSeg.m_prevInNewSeg);

    if (!deserialize(is, laneSeg.m_start))
    {
        return false;
    }

    //	std::cerr << "LS: ActSize: " << (streamposToInt64(is.tellg()) - startPos) << std::endl;
    //	std::cerr << "LS: ExtSize: " << this->getSerializedSize() << std::endl;

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos)
               == CarriageWayList6970SerializedSize6970::getSerializedSize(laneSeg));
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_CarriageWayList6970>::deserialize(std::istream& is,
                                                                        lanes::LaneSupportPointIn6970& point)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, point.m_longitudeInDeg);
    readBE(is, point.m_latitudeInDeg);
    readBE(is, point.m_courseAngelInDeg);
    readBE(is, point.m_lineOffsetLeft);
    readBE(is, point.m_lineOffsetRight);

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos)
               == CarriageWayList6970SerializedSize6970::getSerializedSize(point));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
