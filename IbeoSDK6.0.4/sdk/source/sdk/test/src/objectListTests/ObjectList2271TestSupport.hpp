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
//!\date Sep 29, 2015
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271.hpp>

//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
class ObjectIn2271;
class UnfilteredObjectDataIn2271;
class FilteredObjectDataIn2271;
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class ObjectListScala2271TestSupport : public TestSupport
{
public:
    ObjectListScala2271TestSupport();
    virtual ~ObjectListScala2271TestSupport();

protected:
    static ibeo::common::sdk::ObjectIn2271 createObj(const bool unfAvailable,
                                                     const bool unfContourAvailable,
                                                     const bool filAvailable,
                                                     const bool filContourAvailable);

    static ibeo::common::sdk::ObjectList2271 createObjList();

private:
    static void fillRandomly(ibeo::common::sdk::ObjectIn2271& obj);

    static void fillRandomly(ibeo::common::sdk::ObjectIn2271& obj,
                             const bool unfAvailable,
                             const bool unfContourAvailable,
                             const bool filAvailable,
                             const bool filContourAvailable);

    static void fillRandomly(ibeo::common::sdk::UnfilteredObjectDataIn2271& unf,
                             const bool isAvailable,
                             const bool contourIsAvailable);

    static void fillRandomly(ibeo::common::sdk::FilteredObjectDataIn2271& fil,
                             const bool isAvailable,
                             const bool contourIsAvailable);
}; // ObjectListScala2271TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
