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
//!\date Mar 1, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/SpecialExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/commands/Command2010.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<typename SpecialContainerType>
class EmptyCommandExporter : public SpecialExporterBase<CommandCBase>
{
public:
    static constexpr int commandSize{4};

public:
    EmptyCommandExporter() : SpecialExporterBase<CommandCBase>() {}
    virtual ~EmptyCommandExporter() {}

public:
    //========================================
    //!\brief Get the DataType of exporter/importer.
    //!\return The DataTypeId of the data this exporter/importer
    //!        can handle.
    //----------------------------------------
    virtual CommandCBase::KeyType getSpecialType() const override { return SpecialContainerType::key; }

public:
    //========================================
    //!\brief Get serializable size of data from exporter/importer.
    //!\return Number of Bytes used by data type.
    //----------------------------------------
    virtual std::streamsize getSerializedSize(const CommandCBase& c) const override;

    virtual bool serialize(std::ostream& outStream, const CommandCBase& c) const override;
}; // EmptyCommandExporter

//==============================================================================

template<typename SpecialContainerType>
std::streamsize EmptyCommandExporter<SpecialContainerType>::getSerializedSize(const CommandCBase& s) const
{
    try
    {
        (void)dynamic_cast<const SpecialContainerType&>(s);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return static_cast<std::streamsize>(commandSize);
}

//==============================================================================

template<typename SpecialContainerType>
bool EmptyCommandExporter<SpecialContainerType>::serialize(std::ostream& os, const CommandCBase& s) const
{
    const SpecialContainerType* specialType{nullptr};

    try
    {
        specialType = &dynamic_cast<const SpecialContainerType&>(s);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(os.tellp());

    writeLE(os, specialType->m_commandId);
    writeLE(os, specialType->m_reserved);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(*specialType));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
