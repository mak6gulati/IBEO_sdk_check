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
//! \date Feb 11, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/commands/Command2010.hpp>
#include <ibeo/common/sdk/BufferAndImporterProvider.hpp>

#include <ibeo/common/logging/logging.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Importer<Command2010, DataTypeId::DataType_Command2010>
  : public RegisteredImporter<Command2010, DataTypeId::DataType_Command2010>
{
public:
    Importer();
    Importer(const Importer&) = delete;
    Importer& operator=(const Importer&) = delete;

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

    //========================================
    //!\brief convert data from source to target type (deserialization)
    //!\param[in, out] is      Input data stream
    //!\param[out]     c       Output container.
    //!\param[in]      header  Ibeo DataHeader
    //!\return \c true if serialization succeed, else: false
    //!\note This method is to be called from outside for deserialization.
    //----------------------------------------
    virtual bool deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& dh) const override;

public: // RegisteredImporter
    virtual bool callListener(DataContainerListenerBase* l, const DataContainerBase* const c) const override;

    const BufferAndImporterProvider<CommandCBase>& getBufferAndImporterProvider() const { return m_baip; }
    BufferAndImporterProvider<CommandCBase>& getBufferAndImporterProvider() { return m_baip; }

private:
    bool deserializeSpecial(Command2010* container, const IbeoDataHeader& dh) const;

    bool callListener(DataContainerListenerBase* l, const CommandCBase* const specialCommand) const;
    CommandId readCommandId(const char* const buffer) const;

private:
    static constexpr const char* loggerId = "ibeo::common::sdk::Command2010Importer2010";
    static ibeo::common::logging::LoggerSPtr logger;

private:
    mutable BufferAndImporterProvider<CommandCBase> m_baip;
}; // Command2010Importer2010

//==============================================================================

using Command2010Importer2010 = Importer<ibeo::common::sdk::Command2010, DataTypeId::DataType_Command2010>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
