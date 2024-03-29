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
//! \date Apr 10, 2015
//------------------------------------------------------------------------------
#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/commands/luxcommands/LuxCommand.hpp>
#include <ibeo/common/sdk/datablocks/DataBlock.hpp>
#include <ibeo/common/sdk/misc/ParameterIndex.hpp>
#include <ibeo/common/sdk/misc/ParameterData.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//! \class ReplyLuxGetParameter
//! \brief
//! \date Apr 10, 2015
//------------------------------------------------------------------------------
class ReplyLuxGetParameter : public ibeo::common::sdk::LuxCommandReply<CommandId::Id::CmdLuxGetParameter>,
                             public ibeo::common::sdk::DataBlock
{
public:
    //========================================
    //! \brief Length of the CommandManagerAppBaseStatus command.
    //-------------------------------------
    static const int replySize = 8;

public:
    ReplyLuxGetParameter();

    //========================================
    //! \brief Get the DataType of this DataBlock.
    //! \return Always DataType#DataType_Command.
    //-------------------------------------
    virtual DataTypeId getDataType() const { return dataType; }

    //========================================
    //! \brief Get the size of the serialization.
    //! \return Number of bytes used by the serialization
    //!         of this Command.
    //-------------------------------------
    virtual std::streamsize getSerializedSize() const { return std::streamsize(replySize); }

    //========================================
    //! \brief Deserialize data from the given stream \a is into
    //!        this CommandManagerAppBaseStatusReply.
    //! \param[in, out] is  Stream that provides the serialized
    //!                     data to fill this CommandManagerAppBaseStatusReply.
    //!                     On exit the \a is get pointer will
    //!                     be behind the read data.
    //! \param[in]      dh  IbeoDataHeader that has been received
    //!                     together with the serialized data in \a is.
    //! \return Whether the operation was successful.
    //! \retval true Everything is alright, no error occured.
    //! \retval false Reading the data from the stream has failed.
    //-------------------------------------
    virtual bool deserialize(std::istream& is, const IbeoDataHeader& dh);

    //========================================
    //! \brief Serialize data into the given stream \a os.
    //! \param[out] os  Stream that receive the serialized
    //!                 data from this CommandManagerAppBaseStatusReply.
    //! \return Whether the operation was successful.
    //! \retval true Everything is alright, no error occured.
    //! \retval false Writing the data into the stream has failed.
    //-------------------------------------
    virtual bool serialize(std::ostream& os) const;

public:
    virtual bool callListener(DataListenerBase&) const { return false; }

public:
    virtual bool deserializeFromStream(std::istream& is, const IbeoDataHeader& dh) { return deserialize(is, dh); }

public:
    ParameterIndex getParameterIndex() const { return m_parameterIndex; }
    ParameterData getParameterData() const { return m_parameterData; }

protected:
    ParameterIndex m_parameterIndex;
    ParameterData m_parameterData;
}; // ReplyLuxGetParameter

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
