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
//!\date Feb 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/BufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/CommandEcuSetFilter2010Importer2010.hpp>

//==============================================================================
namespace {
//==============================================================================
using C  = ibeo::common::sdk::Command2010;
using S  = ibeo::common::sdk::CommandEcuSetFilterC;
using R  = ibeo::common::sdk::SpecialRegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Command2010, S>;
using Id = ibeo::common::sdk::SpecialImporterBase<S::CommonBase>::ImporterRegisterId;
using KT = S::CommonBase::KeyType;
//==============================================================================
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
// Specializations for RegisteredImporter
//==============================================================================

//generate link between data-type-id/importer and importer create function <dtid, ImpHash> ==> Imp::create

template<>
const Id R::registeredImporterInitial(std::make_pair(KT{S::key}, S::getClassIdHashStatic()), R::create);

//registering ... (create map)
//

//register listener types
template<>
const Id R::registeredImporter
    = BufferAndImporterProviderGlobal<S::CommonBase>::getInstance().registerImporter(registeredImporterInitial);

//==============================================================================
//==============================================================================
//==============================================================================

std::streamsize SpecialImporter<C, DataTypeId::DataType_Command2010, S>::getSerializedSize(const CommandCBase& s) const
{
    const S* specialType{nullptr};
    try
    {
        specialType = &dynamic_cast<const S&>(s);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return static_cast<std::streamsize>(commandBaseSize + specialType->getNbOfRanges() * 2U * sizeof(uint16_t));
}

//==============================================================================

bool SpecialImporter<C, DataTypeId::DataType_Command2010, S>::deserialize(std::istream& is,
                                                                          CommandCBase& s,
                                                                          const IbeoDataHeader& dh) const
{
    S* specialType{nullptr};

    try
    {
        specialType = &dynamic_cast<S&>(s);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, specialType->m_commandId);
    if (S::key != specialType->m_commandId)
    {
        return false;
    }

    uint16_t nbOfDataTypeEntries;
    readBE(is, nbOfDataTypeEntries);

    if ((nbOfDataTypeEntries & 0x0001) == 0x0001)
    {
        // nbOfDataTypeEntries has to be even
        return false;
    }

    const uint16_t nbOfRanges = static_cast<uint16_t>(nbOfDataTypeEntries >> 1);
    specialType->m_ranges.resize(nbOfRanges);

    for (auto& r : specialType->m_ranges)
    {
        r.first.readBE(is);
        r.second.readBE(is);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(*specialType))
           && this->getSerializedSize(*specialType) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
