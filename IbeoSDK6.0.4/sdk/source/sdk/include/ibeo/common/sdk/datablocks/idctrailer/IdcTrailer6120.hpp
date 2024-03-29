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
//!\date Mar 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief IDC Trailer:
//! Data type marking the end of each IDC-file. Does not contain any data.
//!
//! Each IDC-file shall conclude with the IDC-Trailer. The IDC-Trailer does not contain any data,
//! but marks the end of the IDC-File. So it includes simply the header with the data type number.
class IdcTrailer6120 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.idctrailer6120"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    IdcTrailer6120();

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

}; // IdcTrailer6120Container

//==============================================================================

inline bool operator==(const IdcTrailer6120&, const IdcTrailer6120&)
{
    return true;
} // class is empty, i.e. always equal

inline bool operator!=(const IdcTrailer6120&, const IdcTrailer6120&)
{
    return false;
} // class is empty, i.e. never inequal

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
