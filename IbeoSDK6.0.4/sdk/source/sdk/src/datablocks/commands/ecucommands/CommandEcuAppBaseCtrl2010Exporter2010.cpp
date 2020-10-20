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

//==============================================================================

#include <ibeo/common/sdk/datablocks/commands/ecucommands/CommandEcuAppBaseCtrl2010Exporter2010.hpp>

//==============================================================================
namespace {
//==============================================================================
using S  = ibeo::common::sdk::CommandEcuAppBaseCtrlC;
using B  = S::CommonBase;
using KT = B::KeyType;
//==============================================================================
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

static void writeBE(std::ostream& os, const S::AppBaseCtrlId& ctrId) { writeBE(os, static_cast<uint16_t>(ctrId)); }

//==============================================================================

std::streamsize SpecialExporter<S>::getSerializedSize(const B& s) const
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

    return static_cast<std::streamsize>(commandBaseSize + specialType->getData().size());
}

//==============================================================================

bool SpecialExporter<S>::serialize(std::ostream& os, const B& s) const
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

    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, specialType->m_commandId);
    writeBE(os, specialType->m_ctrlId);

    std::ostreambuf_iterator<char> strOut(os);
    copy(specialType->m_data.begin(), specialType->m_data.end(), strOut);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(*specialType));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
