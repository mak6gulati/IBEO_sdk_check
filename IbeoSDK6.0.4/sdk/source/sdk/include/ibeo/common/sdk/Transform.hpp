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
//! \date Jan 01, 2016
//! \brief Transformation helper class
//------------------------------------------------------------------------------

#ifndef TRANSFORM_HPP
#    define TRANSFORM_HPP

//==============================================================================

#    include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#    include <ibeo/common/sdk/TransformationMatrix2d.hpp>
#    include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2281.hpp>
#    include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2807.hpp>
#    include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2808.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class Transform
{
public:
    static TransformationMatrix2d<float> getTransformationSystem(const ObjectIn2281& object);
    static TransformationMatrix2d<float> getTransformationSystem(const VehicleState2807& vs);
    static TransformationMatrix2d<float> getTransformationSystem(const VehicleState2808& vs);

    static TransformationMatrix2d<float> transformToGlobal(const TransformationMatrix2d<float>& ref2Global,
                                                           const TransformationMatrix2d<float>& rel2ref);
}; // Transform

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

#endif // TRANSFORM_HPP

//==============================================================================
