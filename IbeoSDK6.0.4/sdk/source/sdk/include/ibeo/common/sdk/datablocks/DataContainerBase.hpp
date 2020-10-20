//==============================================================================
//! \file
//!
//!  Base class for all data containers
//!
//!  this includes all general data containers
//!  as well as all "old" type separated containers
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Sep 13, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>

#include <string.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class DataContainerBase
{
public:
    DataContainerBase() : m_importedDataType(DataTypeId::DataType_Unknown) {}
    explicit DataContainerBase(const DataTypeId::DataType srcType) : m_importedDataType(srcType) {}
    virtual ~DataContainerBase() = default;

public:
    //========================================
    //! \brief Set original type of data type of which data was transfered
    //!        into general data
    //! \param[in] dataType  Source-type string (class unique type identifier)
    //! \internal
    //! \warning Is this method needed to be public
    //!          or should only importer be allowed to set
    //!          this value (make Importer<> a friend class?
    //! \endinternal
    //-------------------------------------
    void setImportedDataType(const DataTypeId::DataType importedDataType) { m_importedDataType = importedDataType; }

    //========================================
    //! \brief Return imported type of data type of which data was
    //!        transfered into general data
    //! \return The imported datatype.
    //-------------------------------------
    DataTypeId::DataType getImportedType() const { return m_importedDataType; }

public:
    virtual uint64_t getClassIdHash() const = 0;

protected:
    DataTypeId::DataType m_importedDataType; //!< holds data type of whom the data was imported
}; // DataContainerBase

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

class SpecializedDataContainer : public DataContainerBase
{
public:
    SpecializedDataContainer() : DataContainerBase() {}
    SpecializedDataContainer(const DataTypeId::DataType srcType) : DataContainerBase(srcType) {}
    virtual ~SpecializedDataContainer() {}

public: // getter
    //========================================
    //! \brief Get the header device id.
    //! \return The header device id.
    //-------------------------------------
    virtual uint8_t getHeaderDeviceId() const { return m_headerDeviceId; }

    //========================================
    //! \brief get the header timestamp.
    //! \return The header timestamp.
    //-------------------------------------
    virtual NTPTime getHeaderNtpTime() const { return m_headerNtpTime; }

public:
    //========================================
    //! \brief Set the header data.
    //! \param[in] dh  IbeoDataHeader which contains the
    //!                data to set the m_headerDeviceId
    //!                and m_headerNtpTime of this
    //!                DataBlock.
    //-------------------------------------
    void setDataHeader(const IbeoDataHeader& dh)
    {
        m_headerDeviceId = dh.getDeviceId();
        m_headerNtpTime  = dh.getTimestamp();
    }

protected:
    //========================================
    //! \brief Device id of the header.
    //-------------------------------------
    uint8_t m_headerDeviceId{0};

    //========================================
    //! \brief Timestamp of the header.
    //-------------------------------------
    NTPTime m_headerNtpTime{};
};
//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
