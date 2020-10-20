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
//!\date Feb 7, 2014
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/misc/Unconvertable.hpp>
#include <ibeo/common/sdk/misc/ToHex.hpp>

#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/bufferIO.hpp>

#include <boost/functional/hash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class DataTypeId : public ibeo::common::sdk::ComparableUnconvertable<uint16_t>
{
public:
    //======================================================================
    //! \brief Ids of some DataTypes. For convenience.
    //----------------------------------------
    enum DataType : uint16_t
    {
        DataType_Unknown               = 0x0000,
        DataType_CanMessage1002        = 0x1002, //!< A single can message that has been received via Ethernet.
        DataType_FrameEndSeparator1100 = 0x1100,
        DataType_Command2010           = 0x2010,
        DataType_Reply2020             = 0x2020,
        DataType_Notification2030
        = 0x2030, //!< Not implemented in SDK. error and warning messages sent by ibeo LUX/Scala family sensors
        DataType_Scan2202                  = 0x2202, //!< scan data sent by Ibeo LUX/Scala (before B2) family sensors
        DataType_Scan2205                  = 0x2205, //!< scan data sent by Ibeo ECU devices
        DataType_Scan2208                  = 0x2208, //!< Scan data sent by Ibeo Scala B2 and Ibeo MiniLux sensors
        DataType_Scan2209                  = 0x2209, //!< Identical to 2205 except it can hold more than 65535 points
        DataType_ObjectList2221            = 0x2221, //!< objects sent by Ibeo LUX family sensors
        DataType_ObjectList2225            = 0x2225, //!< objects sent by Ibeo ECU devices
        DataType_ObjectList2270            = 0x2270, //!< send by Scala family sensors (starting with B2)
        DataType_ObjectList2271            = 0x2271, //!< send by Scala family sensors (starting with B2)
        DataType_ObjectList2280            = 0x2280, //!< send by ECU devices
        DataType_ObjectList2281            = 0x2281, //!< send by ECU devices
        DataType_ObjectList2290            = 0x2290, //!< generate by the Evaluation Suite
        DataType_ObjectList2291            = 0x2291, //!< generate by the Evaluation Suite
        DataType_Scan2310                  = 0x2310, //! Uninterpreted Scala raw data from the FPGA
        DataType_Image2403                 = 0x2403, //!< An image
        DataType_PositionWgs84_2604        = 0x2604, //!< GPS position
        DataType_OGpsImuMessage2610        = 0x2610, //!<
        DataType_OGpsImuStatus2611         = 0x2611, //!<
        DataType_MeasurementList2821       = 0x2821, //!< Data type that contains a single measurement list.
        DataType_VehicleStateBasic2805     = 0x2805, //!< send by LUX/Scala
        DataType_VehicleStateBasic2806     = 0x2806, //!< send by ECU
        DataType_VehicleStateBasic2807     = 0x2807, //!< send by ECU
        DataType_VehicleStateBasic2808     = 0x2808, //!< send by ECU
        DataType_ObjectAssociationList4001 = 0x4001,
        DataType_IdcTrailer6120            = 0x6120, //!< Trailer Message in an IDC file
        DataType_IdSequence3500            = 0x3500,
        DataType_PositionWgs84Sequence3510 = 0x3510,
        DataType_Destination3520           = 0x3520,
        DataType_MissionHandlingStatus3530 = 0x3530, ///< Information about the state of mission handling module
        DataType_MissionResponse3540       = 0x3540,
        DataType_TrafficLight3600          = 0x3600,
        DataType_FrameIndex6130            = 0x6130, //!< Index over IDC file
        DataType_DeviceStatus6301          = 0x6301,
        DataType_DeviceStatus6303          = 0x6303,
        DataType_SyncBoxStatus6320         = 0x6320, //!< State for ibeo SyncBox
        DataType_LogError6400              = 0x6400,
        DataType_LogWarning6410            = 0x6410,
        DataType_LogNote6420               = 0x6420,
        DataType_LogDebug6430              = 0x6430,
        DataType_ObjectLabel6503           = 0x6503,
        DataType_SystemMonitoringCanStatus6700    = 0x6700,
        DataType_SystemMonitoringDeviceStatus6701 = 0x6701,
        DataType_SystemMonitoringSystemStatus6705 = 0x6705,
        DataType_LogPolygonList2dFloat6817        = 0x6817, //!< List of informational polygons with text label
        DataType_CarriageWayList6970              = 0x6970, //!< Basic CarriageWayList
        DataType_CarriageWayList6972     = 0x6972, //!< CarriageWayList with additional LaneSegment marking properties
        DataType_EventTag7000            = 0x7000,
        DataType_IbeoEvent7001           = 0x7001,
        DataType_ContentSeparator7100    = 0x7100,
        DataType_MetaInformationList7110 = 0x7110,
        DataType_PointCloud7500          = 0x7500, //!< PointCloudGlobal
        DataType_PointCloud7510          = 0x7510, //!< PointCloudPlane
        DataType_TimeRecord9000          = 0x9000,
        DataType_GpsImu9001              = 0x9001,
        DataType_Odometry9002            = 0x9002,
        DataType_TimeRelationsList9010   = 0x9010, //!< Time Relations
        DataType_TimeRelationsList9011   = 0x9011, //!< Time Relations9011
        DataType_VehicleControl9100      = 0x9100,
        DataType_StateOfOperation9110    = 0x9110,
        DataType_LastId                  = 0xFFFF
    }; // DataType

public:
    //========================================
    //! \brief Constructor of DataTypeId.
    //!
    //! \param dtId  DataType Id as integer.
    //----------------------------------------
    explicit DataTypeId(const uint16_t dtId) : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(dtId) {}
    DataTypeId(const DataType dt) : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(uint16_t(dt)) {}
    DataTypeId() : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(uint16_t(DataType_Unknown)) {}

public:
    bool isSet() const { return (this->m_data != DataType_Unknown); }
    void unSet() { this->m_data = uint16_t(DataType_Unknown); }

public:
    static std::streamsize getSerializedSize() { return sizeof(uint16_t); }

public:
    std::istream& readBE(std::istream& is)
    {
        ibeo::common::sdk::readBE(is, this->m_data);
        return is;
    }

    std::ostream& writeBE(std::ostream& os) const
    {
        ibeo::common::sdk::writeBE(os, this->m_data);
        return os;
    }

    void readBE(const char*& target) { ibeo::common::sdk::readBE(target, this->m_data); }

    void writeBE(char*& target) const { ibeo::common::sdk::writeBE(target, this->m_data); }
}; // DataTypeId

//==============================================================================

template<>
inline std::string toHex<DataTypeId>(const DataTypeId t)
{
    return toHex(uint16_t(t));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

//==============================================================================
namespace boost {
//==============================================================================

template<>
struct hash<ibeo::common::sdk::DataTypeId>
{
    std::size_t operator()(ibeo::common::sdk::DataTypeId const& dtId) const
    {
        hash<uint16_t> h;
        return h(dtId);
    }
}; // :hash<DataTypeId>

//==============================================================================
} // namespace boost
//==============================================================================
