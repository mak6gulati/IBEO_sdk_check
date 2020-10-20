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
//! \date Aug 10, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/misc/SdkExceptions.hpp>

#include <cstddef> // for std::streamsize

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
//! \brief Base for classes used to export data into an IDC container.
//------------------------------------------------------------------------------
class ExporterBase
{
public:
    //========================================
    //! \brief Constructor.
    //----------------------------------------
    ExporterBase() = default;

    //========================================
    //! \brief Copy-constructor.
    //!
    //! Copying is not allowed!
    //----------------------------------------
    ExporterBase(const ExporterBase&) = delete;

    //========================================
    //! \brief Assignment operator.
    //!
    //! Assignment is not allowed!
    //----------------------------------------
    ExporterBase& operator=(const ExporterBase&) = delete;

    //========================================
    //! \brief Destructor.
    //----------------------------------------
    virtual ~ExporterBase() = default;

public:
    //========================================
    //! \brief Get the data type to be exported into an IDC container.
    //!
    //! \return the data type this exporter can handle.
    //----------------------------------------
    virtual DataTypeId getDataType() const = 0;

    //========================================
    //! \brief Get the size in bytes that the object occupies when being serialized.
    //!
    //! \param c[in]  Object to get the serialized size for.
    //! \return  the number of bytes used for serialization.
    //----------------------------------------
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const = 0;

public:
    //========================================
    //! \brief Convert the data container to a serializable format and write it to the given stream (serialization).
    //!
    //! \param[in, out] os      Output data stream
    //! \param[in]      c       Data container to be serialized.
    //! \return \c true if serialization succeeds, \c false otherwise.
    //!
    //! \note This method is to be called from outside for deserialization.
    //----------------------------------------
    virtual bool serialize(std::ostream& outStream, const DataContainerBase& c) const = 0;
}; // ExporterBase

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================
//! \brief Template base class for all exporter specializations.
//------------------------------------------------------------------------------
template<class ClassContainerType, ibeo::common::sdk::DataTypeId::DataType id>
class TypedExporter : public ExporterBase
{
public:
    //========================================
    //! \brief Get the data type ID of this specialized exporter.
    //!
    //! \return the data type ID.
    //----------------------------------------
    DataTypeId getDataType() const final { return id; }
}; // TypedExporter<>

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================
//! \brief Template defintion for Exporter specializations.
//------------------------------------------------------------------------------
template<class ClassContainerType, ibeo::common::sdk::DataTypeId::DataType id>
class Exporter
{
};

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
