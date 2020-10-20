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
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoTcpDevice.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
//!\brief Class to connect to a LuxHr sensor.
//!\date Jul 30, 2015
//------------------------------------------------------------------------------
class IbeoLuxHr : public IbeoTcpDevice<IbeoLuxHr>
{
public:
    //========================================
    //!\brief Create an IbeoLuxHr (connection class).
    //!
    //! This constructor will create an IbeoLuxHr class object
    //! which will try to connect to a LuxHr sensor,
    //! using the given IP address and port number.
    //!
    //! \param[in] ip    IP address of the scanner
    //!                  to be connected with.
    //! \param[in] port  Port number for the connection
    //!                  with the scanner.
    ///---------------------------------------
    IbeoLuxHr(const std::string& ip, const unsigned short port = 12008);

    //========================================
    //!\brief Destructor.
    //!
    //! Will disconnect before destruction.
    ///---------------------------------------
    virtual ~IbeoLuxHr();

}; // IbeoLuxHr

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoLuxHr>& getImporterCreatorMap<IbeoLuxHr>();

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
