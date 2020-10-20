//==============================================================================
//!\file
//!\brief Include file for using IbeoEcu.
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Sep 30, 2013
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoEcu.hpp>

#include <ibeo/common/sdk/datablocks/canmessage/CanMessage1002.hpp>
#include <ibeo/common/sdk/datablocks/frameendseparator/FrameEndSeparator1100.hpp>

#include <ibeo/common/sdk/datablocks/scan/Scan.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2202.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2205.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2208.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2209.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/ObjectList.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2221.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2225.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2270.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2280.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2281.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2291.hpp>

#include <ibeo/common/sdk/datablocks/image/Image.hpp>
#include <ibeo/common/sdk/datablocks/image/special/Image2403.hpp>

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84_2604.hpp>

#include <ibeo/common/sdk/datablocks/ogpsimumessage/OGpsImuMessage.hpp>
#include <ibeo/common/sdk/datablocks/ogpsimumessage/special/OGpsImuMessage2610.hpp>

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2806.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2807.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2808.hpp>

#include <ibeo/common/sdk/datablocks/measurementlist/MeasurementList2821.hpp>

#include <ibeo/common/sdk/datablocks/objectassociationlist/ObjectAssociationList.hpp>
#include <ibeo/common/sdk/datablocks/objectassociationlist/special/ObjectAssociationList4001.hpp>

#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringCanStatus6700.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringDeviceStatus6701.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringSystemStatus6705.hpp>

#include <ibeo/common/sdk/datablocks/contentseparator/ContentSeparator.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100.hpp>

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatus.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303.hpp>

#include <ibeo/common/sdk/datablocks/logmessages/LogMessageDebug6430.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageError6400.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageNote6420.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageWarning6410.hpp>

#include <ibeo/common/sdk/datablocks/objectlabellist/ObjectLabelList.hpp>
#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelList6503.hpp>

#include <ibeo/common/sdk/datablocks/logpolygonlist2d/LogPolygonList2d.hpp>
#include <ibeo/common/sdk/datablocks/logpolygonlist2d/special/LogPolygonList2dFloat6817.hpp>

#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationList.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationList7110.hpp>

#include <ibeo/common/sdk/datablocks/pointcloud/PointCloud.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7500.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7510.hpp>

#include <ibeo/common/sdk/datablocks/timerecord/TimeRecord9000.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/GpsImu.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001.hpp>
#include <ibeo/common/sdk/datablocks/odometry/Odometry.hpp>
#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002.hpp>

#include <ibeo/common/sdk/listener/DataStreamer.hpp>
#include <ibeo/common/sdk/listener/DataContainerListener.hpp>

#include <ibeo/common/sdk/IbeoSdk.hpp>

#include <ibeo/common/logging/logging.hpp>

//==============================================================================
