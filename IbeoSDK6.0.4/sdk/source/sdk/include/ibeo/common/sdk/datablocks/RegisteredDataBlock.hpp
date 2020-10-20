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
//! \date Jan 29, 2014
//------------------------------------------------------------------------------
#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/datablocks/DataBlock.hpp>
#include <ibeo/common/sdk/listener/DataListener.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

template<class DataBlockImpl>
class RegisteredDataBlock : public DataBlock
{
public:
    RegisteredDataBlock() : DataBlock() {}

    virtual ~RegisteredDataBlock() {}

public:
    static DataBlockImpl* create() { return new DataBlockImpl; }
    static DataTypeId getDataBlockId() { return dataBlockId; }

public:
    virtual bool callListener(DataListenerBase& l) const override
    {
        if (DataListener<DataBlockImpl>* lImpl = dynamic_cast<DataListener<DataBlockImpl>*>(&l))
        {
            lImpl->onData(dynamic_cast<const DataBlockImpl* const>(this));
            return true;
        }
        return false;
    }

protected:
    static const DataTypeId dataBlockId;

private:
    static const DataBlockRegisterId registerIdInitial;
    static const DataBlockRegisterId registerId;
}; // RegisteredDataBlock

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================
