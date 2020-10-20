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
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#include "CarriageWayListTestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

//==============================================================================

template<>
lanes::LaneSupportPointIn6970 CarriageListWayTestSupport::getLaneSupportPoint()
{
    PositionWgs84 wgs84;
    wgs84.setLongitudeInDeg(getNonNanRandValue<double>());
    wgs84.setLatitudeInDeg(getNonNanRandValue<double>());
    wgs84.setCourseAngleInDeg(getNonNanRandValue<double>());
    return lanes::LaneSupportPointIn6972(
        wgs84, getNonNanRandValue<Vector2<float>>(), getNonNanRandValue<Vector2<float>>());
}

//CarriageWayList6970 CarriageListWayTestSupport::createCwList()
//{
//
//}
//
////==============================================================================
//
//lanes::CarriageWayIn6970 CarriageListWayTestSupport::createCw()
//{
//
//}
//
////==============================================================================
//
//lanes::CarriageWaySegmentIn6970 CarriageListWayTestSupport::createCwSegment()
//{
//
//}
//
//==============================================================================
template<>
lanes::LaneIn6970::Ptr CarriageListWayTestSupport::createEmptyLane()
{
    using namespace lanes;

    return LaneIn6970::create(getRandValue<uint8_t>(),
                              getRandValue<uint64_t>(),
                              static_cast<LaneType>(getRandValue<uint8_t>()),
                              CarriageWaySegmentIn6970::Ptr{},
                              getRandValue<uint8_t>(),
                              getRandValue<uint8_t>(),
                              getRandValue<uint8_t>(),
                              getRandValue<uint8_t>());
}

//==============================================================================

template<>
lanes::LaneIn6972::Ptr CarriageListWayTestSupport::createEmptyLane()
{
    using namespace lanes;

    return LaneIn6972::create(getRandValue<uint8_t>(),
                              getRandValue<uint64_t>(),
                              static_cast<LaneType>(getRandValue<uint8_t>()),
                              CarriageWaySegmentIn6972::Ptr{},
                              getRandValue<uint8_t>(),
                              getRandValue<uint8_t>(),
                              getRandValue<uint8_t>(),
                              getRandValue<uint8_t>());
}

//==============================================================================

template<>
lanes::LaneIn6970::Ptr CarriageListWayTestSupport::createLane()
{
    using namespace lanes;

    LaneIn6970::Ptr lane = createEmptyLane<lanes::LaneIn6970::Ptr>();

    //TODO: restricting the lower bound for lane segments to 2 fixes the error
    //      "isIoLaneIdentity :: check !areEqualNonRecursive(*lane1, *lane2) failed"
    //      This must be fixed to allow also an empty list or a list with a single lane segment
    const uint32_t nbOfSegments{getRandValue<uint8_t>(2, 0xFF)};
    std::vector<LaneSegmentIn6970::Ptr> laneSegments(static_cast<uint32_t>(nbOfSegments));
    for (uint32_t s = 1; s <= nbOfSegments; ++s)
    {
        const uint32_t lsIdx = static_cast<uint32_t>(s - 1);
        laneSegments[lsIdx]  = createEmptyLaneSegment<lanes::LaneSegmentIn6970::Ptr>();
        //		std::cerr << "Id: " << laneSegments[s-1]->getId();
        laneSegments[lsIdx]->setId(s);
        //		std::cerr << "  --> " << laneSegments[s-1]->getId() << std::endl;;
        lane->insert(laneSegments[lsIdx]);
    }

    //	std::cerr << "============================================" << std::endl;
    //	std::cerr << "Before connecting" << std::endl;
    //	for (auto& lsme : lane->getLaneSegmentsMap()) {
    //		std::cerr << "LaneSegmentIn6970 " << lsme.second->getId()
    //				<< "  Next : " << lsme.second->getNextId() << " (" << ((void*)lsme.second->getNext().get()) << ")"
    //				<< "  Prev : " << lsme.second->getPrevId() << " (" << ((void*)lsme.second->getPrevious().get()) << ")"
    //				<< std::endl;
    //	}

    // connect segments
    if (nbOfSegments >= 2)
    {
        laneSegments[0]->setNext(laneSegments[1]);
        for (uint32_t lsIdx = 1; lsIdx < nbOfSegments - 1; ++lsIdx)
        {
            laneSegments[uint32_t(lsIdx)]->setNext(laneSegments[uint32_t(lsIdx + 1)]);
            laneSegments[uint32_t(lsIdx)]->setPrevious(laneSegments[uint32_t(lsIdx - 1)]);
        }
        laneSegments[uint32_t(nbOfSegments - 1)]->setPrevious(laneSegments[uint32_t(nbOfSegments - 2)]);
    } // nbOfSegments >= 2

    //	std::cerr << "============================================" << std::endl;
    //	std::cerr << "After connecting" << std::endl;
    //	for (auto& lsme : lane->getLaneSegmentsMap()) {
    //		std::cerr << "LaneSegmentIn6970 " << lsme.second->getId()
    //				<< "  Next : " << lsme.second->getNextId() << " (" << ((void*)lsme.second->getNext().get()) << ")"
    //				<< "  Prev : " << lsme.second->getPrevId() << " (" << ((void*)lsme.second->getPrevious().get()) << ")"
    //				<< std::endl;
    //	}

    return lane;
}

//==============================================================================

template<>
lanes::LaneIn6972::Ptr CarriageListWayTestSupport::createLane()
{
    using namespace lanes;

    LaneIn6972::Ptr lane = createEmptyLane<lanes::LaneIn6972::Ptr>();

    //TODO: restricting the lower bound for lane segments to 2 fixes the error
    //      "isIoLaneIdentity :: check !areEqualNonRecursive(*lane1, *lane2) failed"
    //      This must be fixed to allow also an empty list or a list with a single lane segment
    const uint32_t nbOfSegments{getRandValue<uint8_t>(2, 0xFF)};
    std::vector<LaneSegmentIn6972::Ptr> laneSegments(static_cast<uint32_t>(nbOfSegments));
    for (uint32_t s = 1; s <= nbOfSegments; ++s)
    {
        const uint32_t lsIdx = static_cast<uint32_t>(s - 1);
        laneSegments[lsIdx]  = createEmptyLaneSegment<lanes::LaneSegmentIn6972::Ptr>();
        //		std::cerr << "Id: " << laneSegments[s-1]->getId();
        laneSegments[lsIdx]->setId(s);
        //		std::cerr << "  --> " << laneSegments[s-1]->getId() << std::endl;;
        lane->insert(laneSegments[lsIdx]);
    }

    //	std::cerr << "============================================" << std::endl;
    //	std::cerr << "Before connecting" << std::endl;
    //	for (auto& lsme : lane->getLaneSegmentsMap()) {
    //		std::cerr << "LaneSegmentIn6972 " << lsme.second->getId()
    //				<< "  Next : " << lsme.second->getNextId() << " (" << ((void*)lsme.second->getNext().get()) << ")"
    //				<< "  Prev : " << lsme.second->getPrevId() << " (" << ((void*)lsme.second->getPrevious().get()) << ")"
    //				<< std::endl;
    //	}

    // connect segments
    if (nbOfSegments >= 2)
    {
        laneSegments[0]->setNext(laneSegments[1]);
        for (uint32_t lsIdx = 1; lsIdx < nbOfSegments - 1; ++lsIdx)
        {
            laneSegments[uint32_t(lsIdx)]->setNext(laneSegments[uint32_t(lsIdx + 1)]);
            laneSegments[uint32_t(lsIdx)]->setPrevious(laneSegments[uint32_t(lsIdx - 1)]);
        }
        laneSegments[uint32_t(nbOfSegments - 1)]->setPrevious(laneSegments[uint32_t(nbOfSegments - 2)]);
    } // nbOfSegments >= 2

    //	std::cerr << "============================================" << std::endl;
    //	std::cerr << "After connecting" << std::endl;
    //	for (auto& lsme : lane->getLaneSegmentsMap()) {
    //		std::cerr << "LaneSegmentIn6972 " << lsme.second->getId()
    //				<< "  Next : " << lsme.second->getNextId() << " (" << ((void*)lsme.second->getNext().get()) << ")"
    //				<< "  Prev : " << lsme.second->getPrevId() << " (" << ((void*)lsme.second->getPrevious().get()) << ")"
    //				<< std::endl;
    //	}

    return lane;
}

//==============================================================================

template<>
lanes::LaneSegmentIn6970::Ptr CarriageListWayTestSupport::createEmptyLaneSegment()
{
    using namespace lanes;

    return LaneSegmentIn6970::create(getRandValue<uint64_t>(),
                                     static_cast<LaneMarkingType>(getRandValue<uint8_t>()),
                                     static_cast<LaneMarkingType>(getRandValue<uint8_t>()),
                                     static_cast<LaneBoundaryType>(getRandValue<uint8_t>()),
                                     static_cast<LaneBoundaryType>(getRandValue<uint8_t>()),
                                     getLaneSupportPoint<LaneSupportPointIn6970>(),
                                     0U,
                                     0U,
                                     0U,
                                     0U,
                                     false,
                                     false,
                                     LaneIn6970::Ptr{nullptr});
}

//==============================================================================
template<>
lanes::LaneSegmentIn6972::Ptr CarriageListWayTestSupport::createEmptyLaneSegment()
{
    using namespace lanes;

    return LaneSegmentIn6972::create(getRandValue<uint64_t>(),
                                     0U,
                                     0U,
                                     0U,
                                     0U,
                                     static_cast<LaneMarkingType>(getRandValue<uint8_t>()),
                                     static_cast<LaneMarkingType>(getRandValue<uint8_t>()),
                                     static_cast<LaneBoundaryType>(getRandValue<uint8_t>()),
                                     static_cast<LaneBoundaryType>(getRandValue<uint8_t>()),
                                     false,
                                     false,
                                     0.0F,
                                     0.0F,
                                     0.0F,
                                     0.0F,
                                     0.0F,
                                     0.0F,
                                     getLaneSupportPoint<LaneSupportPointIn6972>(),
                                     LaneIn6972::Ptr{nullptr});
}
//==============================================================================

template<>
lanes::LaneSegmentIn6970::Ptr CarriageListWayTestSupport::createLaneSegment()
{
    using namespace lanes;

    return LaneSegmentIn6970::create(getRandValue<uint64_t>(),
                                     static_cast<LaneMarkingType>(getRandValue<uint8_t>()),
                                     static_cast<LaneMarkingType>(getRandValue<uint8_t>()),
                                     static_cast<LaneBoundaryType>(getRandValue<uint8_t>()),
                                     static_cast<LaneBoundaryType>(getRandValue<uint8_t>()),
                                     getLaneSupportPoint<LaneSupportPointIn6972>(),
                                     getRandValue<uint64_t>(),
                                     getRandValue<uint64_t>(),
                                     getRandValue<uint64_t>(),
                                     getRandValue<uint64_t>(),
                                     getRandValue<bool>(),
                                     getRandValue<bool>(),
                                     LaneIn6970::Ptr{nullptr});
}

//==============================================================================

template<>
lanes::LaneSegmentIn6972::Ptr CarriageListWayTestSupport::createLaneSegment()
{
    using namespace lanes;

    return LaneSegmentIn6972::create(getRandValue<uint64_t>(),
                                     getRandValue<uint64_t>(),
                                     getRandValue<uint64_t>(),
                                     getRandValue<uint64_t>(),
                                     getRandValue<uint64_t>(),
                                     static_cast<LaneMarkingType>(getRandValue<uint8_t>()),
                                     static_cast<LaneMarkingType>(getRandValue<uint8_t>()),
                                     static_cast<LaneBoundaryType>(getRandValue<uint8_t>()),
                                     static_cast<LaneBoundaryType>(getRandValue<uint8_t>()),
                                     getRandValue<bool>(),
                                     getRandValue<bool>(),
                                     getRandValue<float>(),
                                     getRandValue<float>(),
                                     getRandValue<float>(),
                                     getRandValue<float>(),
                                     getRandValue<float>(),
                                     getRandValue<float>(),
                                     getLaneSupportPoint<LaneSupportPointIn6972>(),
                                     LaneIn6972::Ptr{nullptr});
}

//==============================================================================

template<>
void CarriageListWayTestSupport::connectSegments(lanes::LaneIn6970::Ptr laneIn6970)
{
    using namespace lanes;

    //	std::cerr << "#Segs: " << lane->getLaneSegmentsMap().size() << std::endl;

    for (auto& lsme : laneIn6970->getLaneSegmentsMap())
    {
        LaneSegmentIn6970::Ptr laneSeg = lsme.second;
        if (laneSeg)
        {
            //			std::cerr << "Seg: " << laneSeg->getId() << std::endl;
            //========================================
            // next segment
            if (laneSeg->getNextId() != 0)
            { // link next segment if in same CarriageWaySegmentIn6970
                const auto laneSegIter = laneIn6970->getLaneSegmentsMap().find(laneSeg->getNextId());
                if (laneSegIter != laneIn6970->getLaneSegmentsMap().end())
                {
                    //					std::cerr << "[" << laneSeg->getId() << "] Add Next: " << laneSegIter->second->getId() << std::endl;;
                    laneSeg->setNext(laneSegIter->second);
                }
            } // if

            //========================================
            // previous segment
            if (laneSeg->getPrevId() != 0)
            { // // link previous segment if in same CarriageWaySegmentIn6970
                const auto laneSegIter = laneIn6970->getLaneSegmentsMap().find(laneSeg->getPrevId());
                if (laneSegIter != laneIn6970->getLaneSegmentsMap().end())
                {
                    //					std::cerr << "[" << laneSeg->getId() << "] Add Prev: " << laneSegIter->second->getId() << std::endl;;
                    laneSeg->setPrevious(laneSegIter->second);
                }
            }
        } // if laneSeg
    } // for line segment entries
}

//==============================================================================

template<>
void CarriageListWayTestSupport::connectSegments(lanes::LaneIn6972::Ptr laneIn6972)
{
    using namespace lanes;

    //	std::cerr << "#Segs: " << lane->getLaneSegmentsMap().size() << std::endl;

    for (auto& lsme : laneIn6972->getLaneSegmentsMap())
    {
        LaneSegmentIn6972::Ptr laneSeg = lsme.second;
        if (laneSeg)
        {
            //			std::cerr << "Seg: " << laneSeg->getId() << std::endl;
            //========================================
            // next segment
            if (laneSeg->getNextId() != 0)
            { // link next segment if in same CarriageWaySegmentIn6970
                const auto laneSegIter = laneIn6972->getLaneSegmentsMap().find(laneSeg->getNextId());
                if (laneSegIter != laneIn6972->getLaneSegmentsMap().end())
                {
                    //					std::cerr << "[" << laneSeg->getId() << "] Add Next: " << laneSegIter->second->getId() << std::endl;;
                    laneSeg->setNext(laneSegIter->second);
                }
            } // if

            //========================================
            // previous segment
            if (laneSeg->getPrevId() != 0)
            { // // link previous segment if in same CarriageWaySegmentIn6970
                const auto laneSegIter = laneIn6972->getLaneSegmentsMap().find(laneSeg->getPrevId());
                if (laneSegIter != laneIn6972->getLaneSegmentsMap().end())
                {
                    //					std::cerr << "[" << laneSeg->getId() << "] Add Prev: " << laneSegIter->second->getId() << std::endl;;
                    laneSeg->setPrevious(laneSegIter->second);
                }
            }
        } // if laneSeg
    } // for line segment entries
}

////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(CarriageWayList6970& cwl)
//{
//
//}
//
////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(CarriageWayList6972& cwl)
//{
//
//}
//
////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(lanes::CarriageWayIn6970& cw)
//{
//
//}
//
////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(lanes::CarriageWayIn6972& cw)
//{
//
//}
//
////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(lanes::CarriageWaySegmentIn6970& cws)
//{
//
//}
//
////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(lanes::CarriageWaySegmentIn6972& cws)
//{
//
//}
//
////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(lanes::LaneIn6970& lane)
//{
//
//}
//
////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(lanes::LaneIn6972& lane)
//{
//
//}
//
////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(lanes::LaneSegmentIn6970& ls)
//{
//
//}
//
////==============================================================================
//
//void CarriageListWayTestSupport::fillRandomly(lanes::LaneSegmentIn6972& ls)
//{
//
//}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
