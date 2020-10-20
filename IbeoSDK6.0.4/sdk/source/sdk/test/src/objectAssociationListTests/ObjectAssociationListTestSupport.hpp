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
//! \date Jan 25, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectassociationlist/ObjectAssociationList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class ObjectAssociationListTestSupport : public TestSupport
{
public:
    ObjectAssociationListTestSupport();
    virtual ~ObjectAssociationListTestSupport();

public:
    static ibeo::common::sdk::ObjectAssociationList createAssocList();

    static ibeo::common::sdk::ObjectAssociation createAssoc();

private:
    static void fillRandomly(ibeo::common::sdk::ObjectAssociationList& oal);

    static void fillRandomly(ibeo::common::sdk::ObjectAssociation& oa);

protected:
    static const int32_t nbOfRepeats = 100;
}; // ObjectAssociationList4001TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
