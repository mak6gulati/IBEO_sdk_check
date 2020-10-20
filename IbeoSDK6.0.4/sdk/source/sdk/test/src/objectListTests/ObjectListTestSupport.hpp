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
//!\date Apr 25, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <common/TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/ObjectList.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2221.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2280.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2281.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2290.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2291.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class ObjectListTestSupport : public TestSupport
{
public:
    ObjectListTestSupport()          = default;
    virtual ~ObjectListTestSupport() = default;

public:
    template<typename T>
    T createObjectList();

public:
    template<typename T>
    static void fillRandomly(T& objList);

    static luxObjectClass::LuxObjectClass getValidRandLuxObjectClass();

protected:
    static const int32_t nbOfRepeats = 100;
}; // ObjectListTestSupport

//==============================================================================

template<typename T>
T ObjectListTestSupport::createObjectList()
{
    T objList;
    fillRandomly(objList);
    return objList;
}

template<>
void ObjectListTestSupport::fillRandomly(ObjectList& objList);

template<>
void ObjectListTestSupport::fillRandomly(Object& obj);

template<>
void ObjectListTestSupport::fillRandomly(ContourPoint& cp);

template<>
void ObjectListTestSupport::fillRandomly(Measurement& meas);

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2221& objList);

template<>
void ObjectListTestSupport::fillRandomly(ObjectIn2221& obj);

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2271& objList);

template<>
void ObjectListTestSupport::fillRandomly(ObjectIn2271& obj);

template<>
void ObjectListTestSupport::fillRandomly(UnfilteredObjectDataIn2271& unfilteredObjectData);

template<>
void ObjectListTestSupport::fillRandomly(FilteredObjectDataIn2271& filteredObjectData);

template<>
void ObjectListTestSupport::fillRandomly(ContourPointIn2271& cp);

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2280& objList);

template<>
void ObjectListTestSupport::fillRandomly(ObjectIn2280& obj);

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2281& objList);

template<>
void ObjectListTestSupport::fillRandomly(ObjectIn2281& obj);

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
