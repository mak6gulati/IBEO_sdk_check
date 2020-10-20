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
//!\date Jan 17, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2221.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

const ObjectIn2221* ObjectList2221::findObject(const uint16_t id) const
{
    ObjectVector::const_iterator iter = std::find_if(
        m_objects.begin(), m_objects.end(), [&id](const ObjectIn2221& obj) { return obj.getObjectId() == id; });

    return (iter == m_objects.end()) ? nullptr : &(*iter);
}

//==============================================================================

//std::string getObjectIdsAsString(const ObjectList2221& objList)
//{
//	if (objList.getNumberOfObjects() == 0)
//		return "";
//
//	// at least 1 object is in the list
//	std::stringstream ssList;
//
//	std::vector<ObjectIn2221>::const_iterator dObjIter = objList.getObjects().begin();
//	ssList << dObjIter->getObjectId();
//	++dObjIter;
//	for (; dObjIter != objList.getObjects().end(); ++dObjIter) {
//		ssList << ", " << dObjIter->getObjectId();
//	}
//
//	return ssList.str();
//}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
