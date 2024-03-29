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
//!\date May 11, 2015
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/DataTypeId.hpp>

#include <map>

//==============================================================================

#if defined _WIN32 && defined(IBEOSDKLIBDLL_SHARED)
#    pragma warning(push)
#    pragma warning(disable : 4251)
// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#endif // _WIN32 && IBEOSDKLIBDLL_SHARED

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class IBEOSDK_API FramingPolicyIn6130
{
public:
    using Trigger    = std::pair<ibeo::common::sdk::DataTypeId, uint8_t>;
    using TriggerSet = std::map<ibeo::common::sdk::DataTypeId, uint8_t>;

public:
    static constexpr uint8_t deviceIdAny{255};

public:
    FramingPolicyIn6130() : m_triggerInNewFrame(true), m_triggers() {}
    virtual ~FramingPolicyIn6130() = default;

public:
    //========================================
    //! \brief Get the size of the serialization.
    //! \return Number of bytes used by the serialization
    //!         of this data class.
    //-------------------------------------
    virtual std::streamsize getSerializedSize() const;

    //========================================
    //! \brief Deserialize data from the given stream \a is into
    //!        this class.
    //! \param[in, out] is  Stream that provides the serialized
    //!                     data to fill this class.
    //!                     On exit the \a is get pointer will
    //!                     be behind the read data.
    //! \return Whether the operation was successful.
    //! \retval true Everything is alright, no error occured.
    //! \retval false Reading the data from the stream has failed.
    //-------------------------------------
    virtual bool deserialize(std::istream& is);

    //========================================
    //! \brief Serialize data into the given stream \a os.
    //! \param[out] os  Stream that receive the serialized
    //!                 data from this class.
    //! \return Whether the operation was successful.
    //! \retval true Everything is alright, no error occured.
    //! \retval false Writing the data into the stream has failed.
    //-------------------------------------
    virtual bool serialize(std::ostream& os) const;

public:
    bool getTriggerInNewFrame() const { return m_triggerInNewFrame; }
    const TriggerSet& getTriggers() const { return m_triggers; }
    TriggerSet& getTriggers() { return m_triggers; }

public:
    void setTriggerInNewFrame(const bool triggerInNewFrame) { m_triggerInNewFrame = triggerInNewFrame; }
    void setTriggers(const TriggerSet& triggers) { m_triggers = triggers; }

public:
    //========================================
    //! \brief Returns true if the given dataType and fromDeviceID is the trigger for a new frame
    //-------------------------------------
    bool isTrigger(const ibeo::common::sdk::DataTypeId dataType, const uint8_t fromDeviceID) const;

protected:
    bool m_triggerInNewFrame; ///< states if a trigger message belongs to next or prev frame (true = next)
    TriggerSet m_triggers; ///< contains all trigger datatypes
}; // FramingPolicyIn6130

//==============================================================================

bool operator==(const FramingPolicyIn6130& lhs, const FramingPolicyIn6130& rhs);
bool operator!=(const FramingPolicyIn6130& lhs, const FramingPolicyIn6130& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

#if defined _WIN32 && defined(IBEOSDKLIBDLL_SHARED)
#    pragma warning(pop)
#endif // _WIN32 && IBEOSDKLIBDLL_SHARED
