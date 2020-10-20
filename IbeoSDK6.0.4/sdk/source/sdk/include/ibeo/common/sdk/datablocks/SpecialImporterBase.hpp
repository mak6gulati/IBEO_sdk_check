//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Sep 12, 2017
//!
//!Importer Base class
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/misc/SdkExceptions.hpp>
#include <ibeo/common/logging/logging.hpp>

#include <boost/function.hpp>

#include <cstddef> // for std::streamsize

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class DataContainerBase;
class DataContainerListenerBase;

//==============================================================================

template<typename SpecialContainerCommonBase>
class SpecialImporterBase
{
public:
    class ImporterRegisterId;

public:
    SpecialImporterBase() {}
    SpecialImporterBase(const SpecialImporterBase&) = delete;
    SpecialImporterBase& operator=(const SpecialImporterBase&) = delete;

    virtual ~SpecialImporterBase() {}

public:
    //========================================
    //! \brief Get the DataType of exporter/importer.
    //! \return The DataTypeId of the data this exporter/importer
    //!         can handle.
    //-------------------------------------
    virtual DataTypeId getDataType() const = 0;

    //========================================
    //! \brief Get serializable size of data from exporter/importer.
    //! \return Number of Bytes used by data type.
    //-------------------------------------
    virtual std::streamsize getSerializedSize(const SpecialContainerCommonBase& s) const = 0;

    virtual bool deserialize(std::istream& stream, SpecialContainerCommonBase& s, const IbeoDataHeader& d) const = 0;

public:
    virtual SpecialContainerCommonBase* createContainer() const = 0;

public:
    virtual bool callListener(DataContainerListenerBase* l, const SpecialContainerCommonBase& s) const = 0;

protected:
    static constexpr const char* loggerId = "ibeo::common::sdk::SpecialImporterBase";
    ibeo::common::logging::LoggerSPtr m_logger{ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

}; // SpecialImporterBase

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

template<typename SpecialContainerCommonBase>
class SpecialImporterBase<SpecialContainerCommonBase>::ImporterRegisterId
{
public:
    using Key                    = std::pair<typename SpecialContainerCommonBase::KeyType, std::size_t>;
    using ImporterCreateFunction = boost::function<SpecialImporterBase*()>;

public:
    ImporterRegisterId(const Key key, ImporterCreateFunction importerCreate)
      : m_key(key), m_importerCreate(importerCreate)
    {}

public:
    Key getKey() const { return m_key; }
    ImporterCreateFunction getValue() const { return m_importerCreate; }

private:
    Key m_key;
    ImporterCreateFunction m_importerCreate;
}; // ImporterRegisterId

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
