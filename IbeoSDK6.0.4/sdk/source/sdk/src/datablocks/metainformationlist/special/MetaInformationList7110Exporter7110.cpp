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
//! \date Feb 02, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationList7110Exporter7110.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::MetaInformationList7110;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_MetaInformationList7110>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c); // ignore the return value
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    std::streamsize sz = std::streamsize(sizeof(uint32_t));

    for (const C::MetaInformationMap::value_type& vt : container->getMetaInformationMap())
    {
        const MetaInformationList7110::MetaInformationSPtrVector& vec = vt.second;
        for (const MetaInformationBaseIn7110SPtr& info : vec)
        {
            sz += info->getSerializedSize();
        } // for each vector entry
    } // for each map entry

    return sz;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_MetaInformationList7110>::serialize(std::ostream& os,
                                                                          const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c); // ignore the return value
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, container->getNumberOfMetaInformationElements());

    for (const C::MetaInformationMap::value_type& vt : container->getMetaInformationMap())
    {
        const MetaInformationList7110::MetaInformationSPtrVector& vec = vt.second;
        if (os.fail())
        {
            break;
        }
        for (const MetaInformationBaseIn7110SPtr& info : vec)
        {
            (&(*info))->serialize(os);
            if (os.fail())
            {
                break;
            }
        } // for each vector entry
        if (os.fail())
        {
            break;
        }
    } // for each map entry

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
