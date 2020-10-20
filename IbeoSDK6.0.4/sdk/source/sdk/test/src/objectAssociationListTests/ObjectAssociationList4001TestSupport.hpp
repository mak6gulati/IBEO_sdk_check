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
//!\date Apr 26, 2016
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectassociationlist/special/ObjectAssociationList4001.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class ObjectAssociationList4001TestSupport : public TestSupport
{
public:
    ObjectAssociationList4001TestSupport();
    virtual ~ObjectAssociationList4001TestSupport();

public:
    static ibeo::common::sdk::ObjectAssociationList4001 createAssocList();

    static ibeo::common::sdk::ObjectAssociationIn4001 createAssoc();

private:
    static void fillRandomly(ibeo::common::sdk::ObjectAssociationList4001& oal);

    static void fillRandomly(ibeo::common::sdk::ObjectAssociationIn4001& oa);

protected:
    static const int32_t nbOfRepeats = 100;
}; // ObjectAssociationList4001TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
