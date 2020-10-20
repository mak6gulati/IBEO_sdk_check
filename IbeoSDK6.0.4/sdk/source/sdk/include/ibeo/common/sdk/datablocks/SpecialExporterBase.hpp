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
//!\date Feb 28, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>

#include <ibeo/common/sdk/misc/SdkExceptions.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<typename SpecialContainerCommonBase>
class SpecialExporterBase
{
public:
public:
    SpecialExporterBase() {}
    SpecialExporterBase(const SpecialExporterBase&) = delete;
    SpecialExporterBase& operator=(const SpecialExporterBase&) = delete;

    virtual ~SpecialExporterBase() {}

public:
    //========================================
    //!\brief Get the DataType of exporter/importer.
    //!\return The DataTypeId of the data this exporter/importer
    //!        can handle.
    //----------------------------------------
    virtual typename SpecialContainerCommonBase::KeyType getSpecialType() const = 0;

public:
    //========================================
    //!\brief Get serializable size of data from exporter/importer.
    //!\return Number of Bytes used by data type.
    //----------------------------------------
    virtual std::streamsize getSerializedSize(const SpecialContainerCommonBase& c) const = 0;

    virtual bool serialize(std::ostream& outStream, const SpecialContainerCommonBase& c) const = 0;
}; // SpecialExporterBase

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================
//!\brief Template defintion for SpecialExporter specializations.
//!\date Jan 9, 2018
//------------------------------------------------------------------------------

template<typename SpecialContainerType>
class SpecialExporter
{
};

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
