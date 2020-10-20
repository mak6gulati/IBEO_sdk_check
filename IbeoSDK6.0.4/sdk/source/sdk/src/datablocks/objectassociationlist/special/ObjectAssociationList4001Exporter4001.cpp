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
//!\date Mar 20, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectassociationlist/special/ObjectAssociationList4001Exporter4001.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::ObjectAssociationList4001;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_ObjectAssociationList4001>::getSerializedSize(const DataContainerBase& c) const
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

    return std::streamsize(4 * sizeof(uint8_t)) + std::streamsize(2 * sizeof(uint16_t))
           + std::streamsize(sizeof(uint32_t)) + std::streamsize(C::nbOfReserved)
           + std::streamsize(container->m_objAssocs.size()) * ObjectAssociationIn4001::getSerializedSize_static();
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_ObjectAssociationList4001>::serialize(std::ostream& os,
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

    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, container->m_refObjListId);
    writeBE(os, container->m_refDevType);
    writeBE(os, container->m_refDevInterfaceVersion);
    writeBE(os, container->m_dutObjListId);
    writeBE(os, container->m_dutDevType);
    writeBE(os, container->m_dutDevInterfaceVersion);

    writeBE(os, uint32_t(container->m_objAssocs.size()));

    for (auto reserved : container->m_reserved)
    {
        writeBE(os, reserved);
    }

    bool vectorDeserializationIsOk{true};
    for (auto objAssocEl : container->getObjectAssociations())
    {
        if (!objAssocEl.serialize(os))
        {
            vectorDeserializationIsOk = false;
            break;
        }
    }

    return vectorDeserializationIsOk && !os.fail()
           && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
