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
//!\date Feb 13, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/SpecialImporterBase.hpp>

#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
//!\brief Template class whose specializations will be derived from
//!       SpecialRegisteredImporter.
//!\date Feb 13, 2018
//------------------------------------------------------------------------------
template<class ContainerType, DataTypeId::DataType id, class SpecialContainer>
class SpecialImporter
{
};

//==============================================================================
//!\brief Intermediate class between SpecialImporterBase and SpecialImporter which
//!       provides registration to devices.
//!\date Jan 9, 2018
//------------------------------------------------------------------------------
template<class ContainerType, DataTypeId::DataType dataType, class SpecialContainer>
class SpecialRegisteredImporter : public SpecialImporterBase<typename SpecialContainer::CommonBase>
{
public:
    static SpecialImporterBase<typename SpecialContainer::CommonBase>* create()
    {
        return new SpecialImporter<ContainerType, dataType, SpecialContainer>;
    }
    static SpecialContainer* createContainerStatic() { return new SpecialContainer; }
    static DataTypeId getDataTypeStatic() { return static_cast<DataTypeId>(dataType); }

public:
    SpecialRegisteredImporter() : SpecialImporterBase<typename SpecialContainer::CommonBase>() {}
    SpecialRegisteredImporter(const SpecialRegisteredImporter&) = delete;
    SpecialRegisteredImporter& operator=(const SpecialRegisteredImporter&) = delete;

    virtual ~SpecialRegisteredImporter(){};

public:
    virtual DataTypeId getDataType() const override final { return getDataTypeStatic(); }

    virtual typename SpecialContainer::CommonBase* createContainer() const override final
    {
        return createContainerStatic();
    }

public:
    virtual bool callListener(DataContainerListenerBase* l,
                              const typename SpecialContainer::CommonBase& s) const override
    {
        if (auto* lImpl = dynamic_cast<DataContainerSpecialListener<ContainerType, dataType, SpecialContainer>*>(l))
        {
            lImpl->onData(dynamic_cast<const SpecialContainer*>(&s));
            return true;
        }
        else
        {
            LOGTRACE(this->m_logger, "Dynamic cast failed");
            return false;
        }
    }

private:
    static const typename SpecialImporterBase<typename SpecialContainer::CommonBase>::ImporterRegisterId
        registeredImporterInitial;
    static const typename SpecialImporterBase<typename SpecialContainer::CommonBase>::ImporterRegisterId
        registeredImporter;
}; // class SpecialRegisteredImporter

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
