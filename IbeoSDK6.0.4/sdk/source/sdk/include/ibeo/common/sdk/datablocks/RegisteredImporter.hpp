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
//! \date Sep 8, 2017
///---------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ImporterBase.hpp>

#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/logging/logging.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
//! \brief Template class whose specializations will be derived from
//!        RegisteredImporter.
//------------------------------------------------------------------------------
template<class ContainerType, DataTypeId::DataType id>
class Importer
{
};

//==============================================================================
//! \brief Intermediate class between ImporterBase and Importer which
//!         provides registration to devices.
//------------------------------------------------------------------------------
template<class ContainerType, DataTypeId::DataType dataType>
class RegisteredImporter : public ImporterBase
{
public:
    static ImporterBase* create() { return new Importer<ContainerType, dataType>; }
    static ContainerType* createContainerStatic() { return new ContainerType; }
    static DataTypeId getDataTypeStatic() { return static_cast<DataTypeId>(dataType); }

public:
    RegisteredImporter() : ImporterBase() {}
    RegisteredImporter(const RegisteredImporter&) = delete;
    RegisteredImporter& operator=(const RegisteredImporter&) = delete;

public:
    virtual DataTypeId getDataType() const override final { return getDataTypeStatic(); }

    virtual DataContainerBase* createContainer() const override final { return createContainerStatic(); }

public:
    virtual bool callListener(DataContainerListenerBase* l, const DataContainerBase* const container) const override
    {
        if (DataContainerListener<ContainerType, dataType>* dclImpl
            = dynamic_cast<DataContainerListener<ContainerType, dataType>*>(l))
        {
            dclImpl->onData(dynamic_cast<const ContainerType&>(*container));
            return true;
        }
        else if (GeneralDataContainerListener<ContainerType>* gdclImpl
                 = dynamic_cast<GeneralDataContainerListener<ContainerType>*>(l))
        {
            gdclImpl->onData(dynamic_cast<const ContainerType&>(*container));
            return true;
        }
        else
        {
            LOGTRACE(m_logger, "Dynamic cast failed");
            return false;
        }
    }

private:
    ibeo::common::logging::LoggerSPtr m_logger{
        ibeo::common::logging::LogManager::getInstance().createLogger("ibeo::common::sdk::RegisteredImporter")};
    static const ImporterBase::ImporterRegisterId registeredImporterInitial;
    static const ImporterBase::ImporterRegisterId registeredImporter;
}; // class RegisteredImporter

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
