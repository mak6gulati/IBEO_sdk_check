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
//!\date Jul 30, 2015
//!
//!
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/devices/IbeoLuxHr.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

IbeoLuxHr::IbeoLuxHr(const std::string& ip, const unsigned short port) : IbeoTcpDevice(ip, port) {}

//==============================================================================

IbeoLuxHr::~IbeoLuxHr() { this->disconnect(); }

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoLuxHr>& getImporterCreatorMap<IbeoLuxHr>()
{
    return ContainerBufferAndImporterProviderGlobal<IbeoLuxHr>::getInstance();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
