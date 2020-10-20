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

#include <logPolygon2dTests/LogPolygonList2dTestSupport.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

void LogPolygonList2dTestSupport::fillRandomly(LogPolygonList2d& lpl)
{
    LogPolygonList2d::LogPolygonListVector lpv;
    lpv.resize(getRandValue<uint16_t>(1000));

    for (auto& lp : lpv)
    {
        fillRandomly(lp);
    }

    lpl.setLogList(lpv);
}

//==============================================================================

void LogPolygonList2dTestSupport::fillRandomly(LogPolygonList2dFloat6817& lpl)
{
    LogPolygonList2dFloat6817::LogPolygonListVector lpv;
    lpv.resize(getRandValue<uint16_t>(1000));

    for (auto& lp : lpv)
    {
        fillRandomly(lp);
    }

    lpl.setLogList(lpv);
}

//==============================================================================

void LogPolygonList2dTestSupport::fillRandomly(LogPolygon2d<float>& lp)
{
    Polygon2d<float> p;
    p.resize(getRandValue<uint16_t>(1000));
    fillVectorRandomlyNonNan<Vector2<float>>(p);
    lp.setPoly(p);
    uint16_t len = getRandValue<uint16_t>(1000);
    lp.setMsg(getRandString(len));
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
