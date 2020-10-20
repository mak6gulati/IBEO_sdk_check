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
//! \date Sep 12, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/misc/SdkExceptions.hpp>

#include <boost/function.hpp>

#include <cstddef> // for std::streamsize

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

class DataContainerBase;
class DataContainerListenerBase;

//==============================================================================

//==============================================================================
//! \brief Base for classes used to import data from an IDC container.
//------------------------------------------------------------------------------
class ImporterBase
{
public:
    class ImporterRegisterId;

public:
    //========================================
    //! \brief Constructor.
    //----------------------------------------
    ImporterBase() = default;

    //========================================
    //! \brief Copy-constructor.
    //!
    //! Copying is not allowed!
    //----------------------------------------
    ImporterBase(const ImporterBase&) = delete;

    //========================================
    //! \brief Assignment operator.
    //!
    //! Assignment is not allowed!
    //----------------------------------------
    ImporterBase& operator=(const ImporterBase&) = delete;

    //========================================
    //! \brief Destructor.
    //----------------------------------------
    virtual ~ImporterBase() = default;

public:
    //========================================
    //! \brief Get the data type to be imported from an IDC container.
    //!
    //! \return the data type this importer can handle.
    //----------------------------------------
    virtual DataTypeId getDataType() const = 0;

    //========================================
    //! \brief Get the size in bytes that the object occupies when being serialized.
    //!
    //! \param c[in]  Object to get the serialized size for.
    //! \return  the number of bytes used for serialization.
    //----------------------------------------
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const = 0;

    //========================================
    //! \brief Read data from the given stream and fill the given data container (deserialization).
    //!
    //! \param[in, out] is      Input data stream
    //! \param[out]     c       Output container defining the target type (might include conversion).
    //! \param[in]      header  Metadata prepended to each Ibeo data block.
    //! \return \c true if deserialization succeeds, \c false otherwise.
    //!
    //! \note This method is to be called from outside for deserialization.
    //----------------------------------------
    virtual bool deserialize(std::istream& stream, DataContainerBase& c, const IbeoDataHeader& d) const = 0;

public:
    //========================================
    //! \brief Create an object of the target type.
    //!
    //! \return Object of the target type.
    //----------------------------------------
    virtual DataContainerBase* createContainer() const = 0;

public:
    //========================================
    //! \brief Notify all registered listeners about the creation of a new object of the target type.
    //----------------------------------------
    virtual bool callListener(DataContainerListenerBase* l, const DataContainerBase* const container) const = 0;
}; // ImporterBase

//==============================================================================

//==============================================================================
//! \brief Key / value pair associating a data type ID with a function to create an importer.
//------------------------------------------------------------------------------
class ImporterBase::ImporterRegisterId
{
public: //type declarations
    using HashId = uint64_t;

public:
    using Key                    = std::pair<DataTypeId, HashId>;
    using ImporterCreateFunction = boost::function<ImporterBase*()>;

public:
    //========================================
    //! \brief Constructor.
    //!
    //! \param dataTypeId[in]      Data type ID to be associated with the create function.
    //! \param importerCreate[in]  Function to create the importer.
    //----------------------------------------
    ImporterRegisterId(const Key dataTypeId, ImporterCreateFunction importerCreate)
      : m_dataTypeId(dataTypeId), m_importerCreate(importerCreate)
    {}

public:
    //========================================
    //! \brief Get the key of this pair which is the data type ID.
    //!
    //! \return the data type ID.
    //----------------------------------------
    Key getKey() const { return m_dataTypeId; }

    //========================================
    //! \brief Get the value of this pair which is the create function.
    //!
    //! \return the function used to create the importer.
    //----------------------------------------
    ImporterCreateFunction getValue() const { return m_importerCreate; }

private:
    Key m_dataTypeId;
    ImporterCreateFunction m_importerCreate;
}; // ImporterRegisterId

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
