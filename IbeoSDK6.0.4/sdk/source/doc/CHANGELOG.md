# Ibeo SDK Version History {#changelog}

[TOC]

## Version 6.0.4

- Bugfix: Previous Doxygen documentations were exported incompletly
- Change: Updated User Guides for Doxygen - "Getting Started" - Guide
- Bugfix: Removed "warning C4309: 'static_cast': truncation of constant value" in ObjectAssociationList4001 on Windows
- Bugfix: Fixed build.bat not working with paths containing spaces
- Change: Added user feedback and dependency checks for build.bat
- Bugfix: DataloggerDemo - custom device-port was being ignored (using default port was supported only)
- Change: Suppress Visual Studio compiler warning C4307 in sdk
- Change: Added Guard for gcc pragmas
- Bugfix: Added missing function readLE / writeLE for Mountingposition
- Bugfix: Wrong mapping between RawObjectClass and ObjectClass in ObjectBasic
- Change: Added new ObjectClass-Type SmallObstacle = 18 (ObjectClass and ObjectClassRaw)
- Change: ScannerType::Next to ScannerType::NextA0 (as this is a a0 sample)
- Fix: EcuLiveDemo connection setting filter command.
- Change: Removed third party scanner support

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 6.0.3

- Bugfix: Fixed some demos which were using old (broken) way to fetch data from idc-files

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 6.0.2

- Bugfix: No longer crashing when opening corrupt idc files with invalid format
- Bugfix: Fixed compiler warnings reg. return-types
- Bugfix: Preserve original header device ID in sendStreamData (IbeoTcpIpAcceptorBase)
- Bugfix: Ecu main thread blocked by filter command sending
- Bugfix: Fixed install dir for cmake config files
- Bugfix: IbeoDataHeader operator!=
- Bugfix: Corrected rotation order mask
- Change: Removed some unnecessary forward declarations
- Change: (re)moved Scan2202 timecheck warning
- Feature: Added simple CSV data export example.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 6.0.1
- Change: Increased MsgBuffer default size for large Scans.
  - Put missing 2d matrix transformation operations back in place.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 6.0.0

- Change: GeneralFileDemo adapted to new GeneralDataContainerListener class
- Feature: new class GeneralDataContainerListener&lt;DataContainerImpl>
- Feature: Reconnect mode for Ibeo TCP devices implemented
  - Possible modes: InitialConnect, WaitForRemoteDevice, AutoReconnect
  - isConnected() in IbeoBaseDevice now only checks if connection established
  - isRunning() checks if thread handling the connection is running
  - getConnected() renamed to connect()
- Change: User defined struct for adaptive APD voltage table added to DeviceStatus6303
- Change: Reformats matching style guide.
- Change: Replaced typedefs with usings.
- Bugfix: Fixed endianess of deserialization of ObjectList2221 into general object list.
- Change: getClassIdHashStatic is now constexpr (C++11)
- Feature: Scan2202 to general Scan data container importer
- Change: sdk/jpegsupport: Remove IbeoAPI related stuff.
- Change: ScannerType is a separate class now
- Change: Matrix for coordinate system transformation is now retrieved from ScannerInfo and cached during import.
- Bugfix: ScanPoint with a scanner ID not part of the scanner infos will now be ignored.
- Change: ScannerType is a separate class now
- Feature: Added mounting rotation order for scanImporter2205 and scanImporter2209 (all coordinates within the general scan container are in vehicle-coordinates)
- Change: Boost pointers to std c++ pointers (C++11)
- Change: Added general data container, serialization and tests for
  - Point cloud
  - TrafficLight
  - IdSequence
  - CarriageWayList (incl. subtypes)
  - CanMessage
  - PositionWgs84Sequence
  - LogPolygonList2dFloat6817
  - DeviceStatus
  - Odometry
  - OGpsImuMessage
  - GpsImu
  - Contentseparator
- Change: All Enums now scoped
- Change: Snippets added, refactored
  - CarriageWay
  - Point cloud
  - MetaInformationList/MetaInformationEcuIdIn7110
  - Polygon2d

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 6.0.0_pre20181210

- Change: Changed Scannertype Ids for ThirdPartyVLidar devices in ScannerInfo
- Change: Vehiclestate* fixed typo in method and member naming
          (vehiclestate*::*minTurningCycle -> vehiclestate*::*minTurningCircle)
- Change: Added SDC
  - MissionHandlingStatus3530 (with tests)
- Change: Added De-/Serialization for SDC
  - MissionHandlingStatus3530Importer3530
  - MissionHandlingStatus3530Exporter3530
- Bugfix: fixed isOpen()-indicator in IdcOStream

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 6.0.0_pre20181203

- Bugfix: Removed gcc compiler warnings
- Change: Using std::array instead of c-arrays
- Bugfix: Fixed logging compilation errors on Windows
- Bugfix: Corrected method naming for gpsImu9001
- Change: Adapted sdk-demos to latest changes in ibeologging
- Feature: Add point-type PointTypeWithEpwFlagsAndColor (PointBase/PointCloudBase)
- Bugfix: Corrected version info within demos
- Bugfix: ContainerBufferAndImporterProviderGlobal template-specializations are not being exported between multiple
          libraries under windows (.dll)

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 6.0.0_pre20181116

- Change: Renamed data types to general naming scheme with appended type-id (old class-naming marked as deprecated)
  - ScanLux to Scan2202
  - ScanEcu to Scan2205
  - CanMessage to CanMessage1002
  - FrameEndSeparator to FrameEndSeparator1100
  - ObjectListLux to ObjectList2221
  - ObjectListEcu to ObjectList2225
  - ObjectListScala to ObjectList2270
  - ObjectListScala2271 to ObjectList2271
  - ObjectListEcuEt to ObjectList2280
  - ObjectListEcuEtDyn to ObjectList2281
  - RefObjectListEcuEt to ObjectList2290
  - RefObjectListEcuEtDyn to ObjectList2291
  - Image to Image2403
  - OGpsImuMessage to OGpsImuMessage2610
  - OGpsImuStatus to OGpsImuStatus2611
  - VehicleStateBasicLux to VehicleStateBasic2805
  - VehicleStateBasicEcu2806 to VehicleStateBasic2806
  - VehicleStateBasicEcu to VehicleStateBasic2807
  - VehicleStateBasicEcu2808 to VehicleStateBasic2808
  - IdcTrailer to IdcTrailer6120
  - FrameIndex to FrameIndex6130
  - DeviceStatus to DeviceStatus6301
  - LogPolygonList2dFloat to LogPolygonList2dFloat6817
  - EventTag to EventTag7000
  - ScalaFpgaRawData to ScalaFpgaRawData2310
- Feature: Introducing General data containers (GDC)
  - ScanContainer
  - VehicleState
  - Command
  - Image
- Change: Introducing specialized datacontainers (SDC) (correspond to old datatypes)
  - FrameEndSeparator1100
  - CanMessage1002
  - ScalaFpgaRawData2310
  - MeasurementList2821
  - Scan2205
  - Scan2208
  - Scan2209
  - PositionWgs84_2604
  - ObjectLabelList6503
  - SystemMonitoringCanStatus6700
  - SystemMonitoringDeviceStatus6701
  - SystemMonitoringSystemStatus6705
  - ContentSeparator7100
  - PointCloudGlobal7500
  - PointCloudPlane7510
  - ObjectList2221
  - ObjectList2271
  - ObjectList2280
  - ObjectList2281
  - ObjectList2290
  - ObjectList2291
  - VehicleState2805
  - VehicleState2806
  - VehicleState2807
  - VehicleState2808
  - DeviceStatus6301
  - DeviceStatus6303
  - OGpsImuMessage2610
  - MetaInformationList7110
  - Contentseparator7100
  - MeasurementList2821
  - CommandLuxGetStatusC
  - CommandLuxResetC
  - CommandLuxResetToDefaultParametersC
  - CommandLuxSaveConfigC
  - CommandLuxSetNtpTimestampSyncC
  - CommandLuxSetParameterC
  - CommandLuxStartMeasureC
  - CommandLuxStopMeasureC
  - several MiniLuxCommand-Containers
  - Command2010
  - CommandLuxGetParameterC
  - CommandLuxSetParameterC
  - CommandLuxSetNtpTimestampSyncC
  - Image2403
  - OGpsImuStatus2611
  - FrameIndex6130
  - IdcTrailer6120
  - LogMessage-64?0
  - StateOfOperation9110
  - Odometry9002
  - ObjectAssociationList4001
  - TimeRecord9000
  - EventTag7000
  - GpsImu9001
  - LogPolygonList2dFloat6817
  - IbeoEvent7001
  - VehicleControl9100
  - CarriageWayList6970
  - CarriageWayList6972
  - TrafficLightStateList3600
  - TimeRelationsList9010
  - TimeRelationsList9011
- Feature: Added new specialized data containers
  - IdSequence3500
  - PositionWgs84Sequence3510
  - Destination3520
  - MissionResponse3540
  - TrafficLightState3600
  - TimeRelationsList9010
  - TimeRelationsList9011
- Change: Separated de-/serialization of datatypes into separate importer-/exporter entities:
          [Naming: ContainerType{Importer/Exporter}DatatypeId_of_serialization]
  - CanMessage1002Importer1002
  - CanMessage1002Exporter1002
  - FrameEndSeparatorImporter1100
  - FrameEndSeparatorExporter1100
  - FrameEndSeparator1100Importer1100
  - FrameEndSeparator1100Exporter1100
  - VehicleStateImporter2805
  - VehicleStateExporter2805
  - CanMessage1002Importer1002
  - CanMessage1002Exporter1002
  - ScalaFpgaRawData2310Importer2310
  - ScalaFpgaRawData2310Exporter2310
  - MeasurementList2821Importer2821
  - MeasurementList2821Exporter2821
  - Scan2205Importer2205
  - Scan2205Exporter2205
  - Scan2208Importer2208
  - Scan2208Exporter2208
  - Scan2209Importer2209
  - Scan2209Exporter2209
  - Scan2208Importer2310
  - Scan2208Exporter2310
  - ScanImporter2205
  - ScanImporter2209
  - MeasurementList2821Importer2821
  - MeasurementList2821Exporter2821
  - PositionWgs84_2604Importer2604
  - PositionWgs84_2604Exporter2604
  - ObjectLabelList6503Importer6503
  - ObjectLabelList6503Exporter6503
  - SystemMonitoringCanStatus6700Importer6700
  - SystemMonitoringCanStatus6700Exporter6700
  - SystemMonitoringDeviceStatus6701Importer6701
  - SystemMonitoringDeviceStatus6701Exporter6701
  - SystemMonitoringSystemStatus6705Importer6705
  - SystemMonitoringSystemStatus6705Exporter6705
  - ContentSeparator7100Importer7100
  - ContentSeparator7100Exporter7100
  - PointCloudGlobal7500Importer7500
  - PointCloudGlobal7500Exporter7500
  - PointCloudPlane7510Importer7510
  - PointCloudPlane7510Exporter7510
  - ObjectList2221Importer2221
  - ObjectList2221Exporter2221
  - ObjectList2225Importer2225
  - ObjectList2225Exporter2225
  - ObjectList2271Importer2271
  - ObjectList2271Exporter2271
  - ObjectList2280Importer2280
  - ObjectList2280Exporter2280
  - ObjectList2281Importer2281
  - ObjectList2281Exporter2281
  - ObjectList2290Importer2290
  - ObjectList2290Exporter2290
  - ObjectList2291Importer2291
  - ObjectList2291Exporter2291
  - ObjectListImporter2280
  - ObjectListImporter2281
  - ObjectListImporter2290
  - ObjectListImporter2291
  - VehicleState2805Importer2805
  - VehicleState2805Exporter2805
  - VehicleState2806Importer2806
  - VehicleState2806Exporter2806
  - VehicleState2807Importer2807
  - VehicleState2807Exporter2807
  - VehicleState2808Importer2808
  - VehicleState2808Exporter2808
  - VehicleStateImporter2805
  - VehicleStateImporter2806
  - VehicleStateImporter2807
  - VehicleStateImporter2808
  - VehicleStateExporter2805
  - VehicleStateExporter2808
  - DeviceStatus6301Importer6301
  - DeviceStatus6301Exporter6301
  - DeviceStatus6303Importer6303
  - DeviceStatus6303Exporter6303
  - OGpsImuMessage2610Importer2610
  - OGpsImuMessage2610Exporter2610
  - MetaInformationList7110Importer7110
  - MetaInformationList7110Exporter7110
  - Command2010Importer2010
  - SpecializedCommand2010Importer2010
  - MeasurementList2821Importer2821
  - MeasurementList2821Exporter2821
  - CommandEcuAppBaseCtrl2010Importer2010
  - CommandLuxGetStatus2010Importer2010
  - CommandLuxGetStatus2010Importer2010
  - CommandLuxReset2010Importer2010
  - CommandLuxResetToDefaultParameters2010Importer2010
  - CommandLuxSaveConfig2010Importer2010
  - CommandLuxSetNtpTimestampSync2010Importer2010
  - CommandLuxSetStatus2010Importer2010
  - CommandLuxStartMeasure2010Importer2010
  - CommandLuxStopMeasure2010Importer2010
  - several MiniLuxCommand - Importers and Exporters
  - CommandEcuAppBaseCtrlC2010Importer2010
  - Command2010Exporter2010
  - CommandEcuAppBaseCtrl2010Exporter2010
  - CommandEcuSetFilter2010Exporter2010
  - CommandLuxGetStatus2010Exporter2010
  - CommandLuxGetParameter2010Exporter2010
  - CommandEcuAppBaseCtrl2010Exporter2010
  - CommandLuxSetParameter2010Exporter2010
  - CommandLuxSetNtpTimestampSync2010Exporter2010
  - Image2403Importer2403
  - Image2403Exporter2403
  - OGpsImuStatus2611Importer2611
  - OGpsImuStatus2611Exporter2611
  - FrameIndex6130Importer6130
  - FrameIndex6130Exporter6130
  - IdcTrailer6120Importer6120
  - IdcTrailer6120Exporter6120
  - LogMessage*64?0 Importer and Exporter
  - StateOfOperation9110Importer9110
  - StateOfOperation9110Exporter9110
  - Odometry9002Importer9002
  - Odometry9002Exporter9002
  - ObjectAssociationList4001Importer4001
  - ObjectAssociationList4001Exporter4001
  - TimeRecord9000Importer9000
  - TimeRecord9000Exporter9000
  - EventTag7000Importer7000
  - EventTag7000Exporter7000
  - GpsImu9001Importer9001
  - GpsImu9001Exporter9001
  - LogPolygonList2dFloat6817Importer6817
  - LogPolygonList2dFloat6817Exporter6817
  - IbeoEvent7001Importer7001
  - IbeoEvent7001Exporter7001
  - VehicleControl9100Importer9100
  - VehicleControl9100Exporter9100
  - CarriageWayList6970Importer6970
  - CarriageWayList6970Exporter6970
  - CarriageWayList6972Importer6972
  - CarriageWayList6972Exporter6972
  - ImageImporter2403
  - ImageExporter2403
  - TrafficLightStateList3600Importer3600
  - TrafficLightStateList3600Exporter3600
  - MissionResponse3540Importer3540
  - MissionResponse3540Exporter3540
  - Destination3520Importer3520
  - Destination3520Exporter3520
  - PositionWgs84Sequence3510Importer3510
  - PositionWgs84Sequence3510Exporter3510
  - IdSequence3500Importer3500
  - IdSequence3500Exporter3500
  - PositionWgs84Sequence3510Importer3510
  - PositionWgs84Sequence3510Exporter3510
  - TimeRelationsList_9010Importer9010
  - TimeRelationsList_9010Exporter9010
  - TimeRelationsList_9011Importer9011
  - TimeRelationsList_9011Exporter9011
- Change: Templatized mutated snippets
  - Vector2
  - Vector3
  - Point2d
  - PointSigma2d
  - Box2d
  - Matrix2d
  - Matrix2x2
  - RotationMatrix2x2
  - TransformationMatrix2x2
  - Matrix3x3
  - RotationMatrix3x3
  - TransformationMatrix3x3
  - Matrix3d
  - MountingPosition
  - MountingPositionRaw
- Feature: Added Unittests for all implemented datatypes (w. (de-/)serialization tests)
- Change: Supporting C++-Standard 11 (C++11) and Visual Studio 2015 SP0
- Change: Changed project structure for ibeoSDK and sub-projects (ibeoSDK-Demos, ibeosdk-Tools, ...)
- Change: Explicitly use override keyword (Methods classified by 'override' no longer have an additional 'virtual' classifier)
- Change: Use nullptr instead of 0 or NULL (MISRA-conformity)
- Change: Removed user-defined typedefs for inttypes ([U]INT[8|16|32|64]) from IbeoSdk
          (use standard type [u]int[8|16|32|64]_t instead)
- Feature: Added new scan data type Scan2209 [0x2209] (extends 0x2205 for supporting more than 65535 scan points)
- Feature: Added support for data type IdSequence3500 (0x3500)
- Feature: Added support for data type PositionWgs84Sequence3510 (0x3510)
- Feature: Added support for data type Destination3520 (0x3520)
- Feature: Added support for data type MissionResponse3540 (0x3540)
- Feature: Added support for data type IbeoEvent7001 (0x7001)
- Feature: Added support for data type StateOfOperation (0x9110)
- Feature: Allow parsing idc files from an user defined starting position (setPos / getPos)
- Feature: Added Bauhaus configuration
- Feature: ObjectEcuEtDyn: added get/set AccelerationCorrCoeff + VelocityCorrCoeff (from/to MeasurementList)
- Feature: Set connection timeout for IbeoEthDevice by hand (methods: setRecvTimeoutSeconds(timeoutInSec) or getConnected(timeoutInSec))
- Bugfix: Fixed crash (segmentation fault) when trying to not existing/connected devices
- Feature: IdcFile supports loading FrameIndex
- Bugfix: TcpReceiveThreadEnsemble::recvThreadMain: Recieve timeouts no longer end the connection per se
- Change: Replaced old logging with new logging framework "ibeologging"
- Change: Introducing Idc-I/O-stream for idc stream handling
- Change: Introduced clang-compiler compatibility
- Bugfix: Fixed several compilation errors under windows
- Change: Adapted ibeosdk package and lib naming -> ibeo-common::sdk
- Feature: Added zip-packaging for build target (cmake)
- Feature: Added new tool IDcListTool (displays overview of idc-file content)
- Bugfix: Re-added ability to build ibeoSDK 6 statically

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.4.2

- Bugfix: Compiling fails on windows os
- Bugfix: Adapt code for SubScan2208 to match with documentation

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.4.1

- Bugfix: Abnormal program termination if device does not respond during connection phase (IbeoEthDevice)
- Change: Optimized processing of data recieved from sensors (IbeoSutpInterface)
- Change: Renamed snippets/datatypes to general naming scheme with appended type-id (old class-naming marked as deprecated)
  - snippet: TrafficLightState to TrafficLightState3600
  - datatype: TrafficLightStateList to TrafficLightStateList3600

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.4.0

- Feature: Added new Datatype: CarriageWayList6972 (0x6972)
- Feature: Added new Datatype: IdSequence3500 (0x3500)
- Feature: New DataType MissionResponse3540 (0x3540)
- Feature: New DataType MissionHandlingStatus3530 (0x3530)
- Feature: New DataType TrafficLight (0x3600) - List of traffic light states
- Feature: Added new Datatype: Destination3520 (0x3520)
- Bugfix: PositionWgs84 extended SourceType and added Equality-Operator for Datatype
- Feature: New DataType PositionWgs84Sequence3510 (0x3510)
- Bugfix: Added Equality-Operator for Datatype PositionWgs84
- Change: Renamed ClockType::ClockName::Clock_Other to ClockType::ClockName::Clock_User and added ::Clock_Max (Id 15)
- Bugfix: Connection timeout for hardware devices (IbeoEthDevice)
- Feature: Timeout for hardware devices (IbeoEthDevice) can now be set manually
- Bugfix: IbeoSutpInterface crashes with nullptr exception
- Bugfix: idcFile - setPos and getPos return error -1 when eof
- Bugfix: Assertion thrown when deserializating payload of idc-files
- Bugfix: TCP-Recieve thread ended automatically when reciever timed out.
- Feature: IdcRepairTool: Add options keepDataBeforeFistScan and withLuxData.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.3.1

- Feature: Added correlation coefficient for velocity and acceleration in ObjectEcuEtDyn
- Change: Renamed Lane-related datatypes
- Bugfix: Segmentation fault when UDP-Thread is being destroyed
- Feature: IbeoEthDevice: Add attribute recvTimeoutSeconds to set the timeout period of the receive operation.
- Bugfix: IbeoSdkScalaLiveDemo does not exit properly

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.3.0

- Change: Removed user-defined typedefs for inttypes ([U]INT[8|16|32|64]) from IbeoSdk
          (use standard type [u]int[8|16|32|64]_t instead)
- Feature: Added new scan data type Scan2209 [0x2209] (extends 0x2205 for supporting more than 65535 scan points)
- Feature: Allow parsing idc files from an user defined starting position
- Feature: Added support for data type IbeoEvent7001 (0x7001)
- Feature: Added support for data type StateOfOperation (0x9110)
- Change: Renamed data types to general naming scheme with appended type-id (old class-naming marked as deprecated)
  - ScanLux to Scan2202
  - ScanEcu to Scan2205
  - CanMessage to CanMessage1002
  - FrameEndSeparator to FrameEndSeparator1100
  - ObjectListLux to ObjectList2221
  - ObjectListEcu to ObjectList2225
  - ObjectListScala to ObjectList2270
  - ObjectListScala2271 to ObjectList2271
  - ObjectListEcuEt to ObjectList2280
  - ObjectListEcuEtDyn to ObjectList2281
  - RefObjectListEcuEt to ObjectList2290
  - RefObjectListEcuEtDyn to ObjectList2291
  - Image to Image2403
  - OGpsImuMessage to OGpsImuMessage2610
  - OGpsImuStatus to OGpsImuStatus2611
  - VehicleStateBasicLux to VehicleStateBasic2805
  - VehicleStateBasicEcu2806 to VehicleStateBasic2806
  - VehicleStateBasicEcu to VehicleStateBasic2807
  - VehicleStateBasicEcu2808 to VehicleStateBasic2808
  - IdcTrailer to IdcTrailer6120
  - FrameIndex to FrameIndex6130
  - DeviceStatus to DeviceStatus6301
  - LogPolygonList2dFloat to LogPolygonList2dFloat6817
  - EventTag to EventTag7000
- Bugfix: Remove LuxScan from framing policy trigger.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.2.4

- Bugfix: Corrected Odometry9002 serialization
          (added m_wheelBase - new total serialized size: 150 bytes)

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.2.3

- Bugfix: Set library output directory to work also for windows.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.2.2

- Change: Documentation update for IbeoEthDevice
- Change: Removed ifa interface parameter of TCP devices
- Change: Changed parameter class name from EthMulticast to EthUdpMulticast

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.2.1

- Feature: Extended support for udp communication
- Change: IbeoUdpDeviceBase and IbeoTcpIpDevceBase merged to IbeoEthDevice for udp and tcp
- Change: New class IbeoEthType to specify communication type for the IbeoEthDevice
- Change: New class ThreadEnsemble as base class for UdpReceiveThreadEnsembel and TcpIpThreadEnsemble
- Change: Removed obsolete class IbeoUdpScala

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.1.0

- Feature: Add datablocks
  - SystemMonitoringCanStatus6700
  - SystemMonitoringDeviceStatus6701
  - SystemMonitoringSystemStatus6705
  - TimeRecord9000
  - GpsImu9001
  - Odometry9002.
- Change: call std::isnan instead of isnan to maintain C++11 compatibility
          and newer compiler. Provide a std::isnan function for older VS compiler.
- Bugfix: Avoid crashing in case mutliple theads accessing a custom LogStreamBuf.
- Bugfix: Fix error in tool IdcCompare, only if strncmp had return 1 or 0 in method
          IdcComparator::onData the comparison was correct. The return value
          -1 was treated wrongly.
- Bugfix: Fix error in serialization of LaneSupportPoint. (Call serialize method
          of Point2dFloat to avoid endianess problems).
- Bugfix: Add missing framing policy trigger for LuxScan.
- Bugfix: In IdcRepairTool do not copy old trailer and frame index to new file.
- Bugfix: In IdcRepairTool start copying with a trigger (scan).
- Fix: Add missing boost include for some compilers.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.0.4

- Bugfix: In CMakeLists.txt: Add option to link boost libs statically.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.0.3

- Bugfix: In ScalaFpgaRawData2310::extractScan start end end angle were swapped.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.0.2

- Bugfix: Add missing source files to shipped VS solutions to make them compile.
- Bugfix: VS 2008 and 2010 had only 32 bit streamoff which causes errors when
          dealing with file larger than 2GB.
- Bugfix: Fix error in IdcCompare while comparing datablock body data.
- Bugfix: Fix some exception messages in Measurement.cpp.
- Bugfix: Get rid of some compiler warnings.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 5.0.1

- Feature:
  - Add database access to Ibeo EvS R3 database (read-only).
  - Add new classes with database context to:
    - "ibeosdk/database",
    - "ibeosdk/devices",
    - "ibeosdk/devices/database".
  - Update HOWTO.txt:
    - Add section: "Concept - Database access/Reader/DatabaseReplayer".
    - Add paragraph for building mongo-cxx-driver to section: "Requirements".
    - Add paragraph for building IbeoSDK with database support to section: "To build the IbeoSDK as library".
- Feature: Add database demos
  - IbeoSdkDb2IdcDemo
  - IbeoSdkDbInfoDemo
  - IbeoSdkDbRoadmarkingDemo
  - IbeoSdkDbReplayDemo
- Feature: Add classes
  - TimeInterval
  - CompressedPoint2d
  - Box2d
- Feature: Add template function round int Math.hpp
- Bugfix: Fix (de)serialization of Snippet ObjectLabel6503.
- Change:
  - Rename static method Point2d::getSerializedSize as getSerializedSize_static.
  - Add non-static method Point2d::getSerializedSize.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.7.1

- Feature: Add read-only SUTP ScaLa protocol support. (No device).

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.6.2

- Bugfix: Fix problem in CMake project for Linux. Add linker option --whole-archive
          to prevent removing assumed unused templates (methods).

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.6.1

- Feature: Add copy constructor and assignment operator to class Image.
- Feature: Add 3D transformations
- Feature: Add templatized getAs function for measurement (boost::any) in class Measurement
- Feature: Add operator == and != for classes: ObjectListEcu, ObjectListEcuEt, ObjectListEcuEtDyn,
           ObjectEcu, ObjectEcuEt, ObjectEcuEtDyn, ScanEcu, ResolutionInfo, ScanPointEcu, ScannerInfo,
           Measurementlist2821, VehicleStateBasicEcu,VehicleStateBasicEcu2808, ScanPointEcu
- Feature: Add setter, getter for all members in ObjectListEcu, ObjectListEcuEt,
           ObjectListEcuEtDyn, ObjectEcuEt, ObjectEcuEtDyn, ScanEcu, VehicleStateBasicEcu,
           ScanPointEcu, ScannerInfo, Measurementlist2821,
- Feature: Add demo IbeoSdkEcuSimDemo and IbeoSdkScalaSimDemo.
- Feature: Add class IbeoTcpIpAcceptor which is able to accept TCP/IP connections
           and send data. Adding derivations for ECU acceptor and Scala acceptor.
- Feature: Add DataBlock ObjectAssociationList4001.
- Feature: Add DataBlock ObjectLabelList6503.
- Feature: Add typedefs for vector type in class ObjectListEcuEt and ObjectListEcuEtDyn.
- Feature: Add unittests for class MeasurementList (Snippet).
- Feature: Add method MeasurementList::getMeasurement.
- Feature: Add tool IdcCompare, which compares two idc file but ignoring
           differences in the IbeoDataHeader timestamps.
- Change: Renaming setter ResolutionInfo::getResolution to ResolutionInfo::setResolution
- Change: Box2dF is now a Snippet.
- Change: Introduce functions fuzzyCompareT to replace fuzzyCompare.
- Change: In future releases of Ibeo software RefObjectListEtDyn will be replaced
          by ObjectListEcuEtDyn with the isRefObjList flag set.
          (Apart from the DataTypeId, both class where identically).
- Change: Replace ObjectEcutEtDyn::Flags (enum) by static const uint8_t values.
          Add flag bit isRefObjList.
- Change: Add full 3d WGS transformation.
- Change: Add new object classes ObjectClass_Motorbike,  ObjectClass_Bicycle
- Change: Changing to asynchronously receiving data (MsgBuffer.cpp)
- Bugfix: Correct values for DynamicFlagDynState static attributes.
- Bugfix: Remove attributes ScanEcu::nbOfScanPoints and nbOfScannerInfos to avoid inconsistency
- Bugfix: Fix insufficient checks in unittests.
- Bugfix: Lux/Scala and Ecu have different enums of object classes.
- Bugfix: Fix IbeoDataHeader::operator!=.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.5.2

- Feature: Add demo for MetaInformationList7110.
- Feature: Add ObjectListEcuEtDyn flag ReferenceList.
           (0x2281 is used instead of 0x2291 by EvS R3 with this flag set).

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.5.1

- Feature: Add support for PointCloud data types 0x7500 (global) and 0x7510 (plane).
- Feature: Add support for DataBlock MetaInformationList
- Feature: Add support for DataBlock ContentSeparator
- Feature: Add classes
  - Matrix3dFloat
  - RotationMatrix3dFloat
  - PointCloudBase
  - PointCloudGlobal7500
  - PointCloudPlane7510
  - GpsPoint
  - GlobalPoint
  - PointBase
  - ReferencePlane
  - PlanePoint
  - Point3dFloat
  - Point3dDouble
  - EcefPoint
  - MetaInformationFactory
- Feature: Add snippets
  - MetaInformation (base class)
  - MetaInformationAppBaseConfig
  - MetaInformationEcuId
  - MetaInformationKeywords
  - MetaInformationUnsupported
  - MetaInformationVersionNumber
- Feature: Add demo IbeoSdkPointCloudPlane7510.
- Bugfix: Correct endianes when writing ObjectClass to big endianess. (Has no effect since only 1 byte is written).
- Bugfix: Correct endianess when writing EventTag::TagClass to big endianess.
- Change: In CMake build now building ibeosdk library static
- Unittests: Add test MetaInformationTest

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.4.1

- Feature: Add math functions floatEqual, floatInequal to take NaN into account.
- Feature: Add getRandValue method for type float
- Feature: Add helper class Tranform.
- Change: CarriageWay now can hold global coordinates. VehicleStateBasicEcu2808 is nessasary.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.3.2

- Bugfix: In ReplyLuxGetParameter and ReplyMiniLuxGetParameter correct (de-)serialization of the command id.
- Bugfix: Fix (16Bit) serialization of RefPointBoxLocation used in (Reference)ObjectEcuEt and (Refernce)ObjectEcuEtDyn.
- Fix: Some issues in ScalaFpgaRawData2310::extractScan, set correct start and end scan angle, mirror tilt, etc.
- Fix: Add missing file ScalaFpgaRawScanPointBase to VS project filter.
- Fix: Some issues with the CLang compiler.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.3.1

- Feature: Add methods to get the object box's center position for classes ObjectEcuEtDyn (used by 0x2281, 0x2291).
- Feature: Add interface to access libjpeg in folder ibeosdk/jpegsupport.
- Feature: Add ScannerType id for Sick LMS100/111, LMS200/291 and LMS500/511.
- Feature: In ObjectClass enum add class Underdriveable.
- Feature: Update the CMakeLists.txt to be used with CMake to create project files.
- Feature: Add unittest support.
- Feature: Add equal and non-equal predicates for classes
  - Point2d
  - PointSigma2d
  - ContourPoint
  - FilteredObjectAttributes
  - UnfilteredObjectAttributes
  - ObjectScala2271
  - ObjectListScala2271
- Feature: Add Support for DataBlock VehicleStateBasicEcu2808 (0x2808).
- Feature: Add device class IbeoTrackingBox.
- Feature: New Demo: IbeoSdkLaneEvaluationDemo.cpp
- Feature: New Demo: IbeoSdkTrackingBoxLiveDemo.cpp
- Bugfix: Fix too small buffer for custom log stream created by CustomLogStreamCreator.
- Bugfix: Fix the serialization of ContourPoint. m_posX was serialized a second time instead of m_posY. Used in FilteredObjectAttributes / UnfilteredObjectAttributes for ObjectScala2271.
- Bugfix: FilteredObjectAttributes / UnfilteredObjectAttributes: add setter for attribute m_possibleNbOfContourPoints.
- Bugfix: In ObjectScala2271: remove redundancies and source of inconsistency by removing class attribute m_attributeFlags. Setter and getter now directly access the FilteredObjectAttributes / UnfilteredObjectAttributes flags.
- Bugfix: Correct ScanPoint2208Flags of class ScanPoint2208.
- Change: In ObjectScala2271: attribute flags are no longer defined in an enum but separatly defined as const static attributes.
- Change: Set MsgBuffer size for TCP/IP devices (derived from IbeoTcpIpDeviceBase) to 4*64K. (Messages larger than this buffer size cannot be deserialized and will be skipped).
- Change: Rename class lanes::mapConstructor as lanes::MapConstructor.
- Change: Classes LogStreamBuf, TimeConversion and IbeoDeviceBase are now derived from boost::noncopyable to avoid coying by accident.
- Internal-Feature: In ObjectScala2271: add getter of attribute ObjectScala2271::m_reserved and ObjectScala2271::m_internal to be used by equal predicate.
- Internal-Feature: IN ObjectListScala2271: add getter of attribute ObjectListScala2271::m_reserved to be used by equal predicate.
- Internal-Feature: Add DataBlock LogPolygonList2dFloat.
- Internal-Feature: Add DataBlock ScalaFpgaRawData2310.
- Internal-Bugfix: Fix deserialization of attribute ObjectEcuEt::m_reserved2.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.2.1

- Feature: Add subfolders unittests and tools.
- Feature: Add boost unit test framework to makefiles and CMakeLists.txt files.
- Feature: Add IdcRepairTool.
- Feature: Add Non-SDK C-tool idcFixSizeOfPrevMsg.c
- Feature: Add VS projects for IdcMergeTool (fka IdcMerger).
- Feature: Add MeasurementKey RearMonitorFlag (705).
- Feature: Add eclipse build targets for tests, tools, docs and cleaning.
- Feature/Change: Simplify the handling of classes derived from more than
           one Listener, e.g. AllListener classes in demos. Only on
           registerListener call is needed to register all types the
           object can listen to.
- Change: Listener header are deprecated and will remain only for
          compatibility.
- Bugfix: Add missing DataTypeid DataType_CarriageWayList.
- Bugfix: Add -lpthread when linking executables. (Issue with newer g++ compiles)
- Bugfix: Remove restriction of ObjectListLux to 63 objects since a Lux8L can
          generate more than 63 objects.
- Bugfix: Add missing getter ScanPointEcu::getSegmentId.
- Internal-Feature: Add writeBE and readBE template functions for enum types.
- Internal-Feature: Add new dynamic flags for ScanPointEcu and ScanEcu::Flags_ObjIdAsSegId.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.1.2

- Bugfix: When writing the first IbeoDataHeader into a file, set the size
          of the previous Datablock to 0 to be compatible with ILV.
- Bugfix: Prevent crashing of FrameIndex::serialize if there is no entry
          in the index at all.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.1.1

- Interface-Change: Signature of IdcFile::write has changed. It now takes an IbeoDataHeader and the
                    buffer with the body data. Attributes m_strm and m_dh has become private.
- Feature: Add command support for IbeoMiniLUX.
- Feature: add command CommandMiniLuxGetParameter
- Feature: add command CommandMiniLuxGetStatus
- Feature: add command CommandMiniLuxReset
- Feature: add command CommandMiniLuxResetToDefaultParameters
- Feature: add command CommandMiniLuxSaveConfig
- Feature: add command CommandMiniLuxSetNtpTimestampSync
- Feature: add command CommandMiniLuxSetParameter
- Feature: add command CommandMiniLuxStartMeasure
- Feature: add command CommandMiniLuxStopMeasure
- Feature: Add DataBlock IdcTrailer.
- Feature: Add DataBlock FrameIndex.
- Feature: IdcFile now adds a FrameIndex when closing an output IDC file.
- Feature: IdcFile now adds a IdcTrailer when closing an output IDC file.
- Feature: Define some MeasurementKeys used for XSensIMU data.
- Feature: Add unregisterListener and unregisterStreamer to class IdcFile.
- Bugfix: Correct the type of VehicleStateBasicLux::m_currentYawRate from uint16_T to int16_t.
- Bugfix: Add missing initialization of output value in LogFile::getLogFile.
- Bugfix: Clear the variable contents of DataBlock DeviceStatus6303 before deserialization.
          Necessary when reusing the container.
- Bugfix: Avoid some compiler warnings by explicit casting.
- Bugfix: Avoid some compiler warnings by adding virtual destructor to All*Listener classes in demos.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 4.0.1

- Change: Introduce class IbeoDeviceBase as parent class of IbeoTcpIpDeviceBase.
- Feature: Add DataBlock EventTag
- Feature: Add class EventMonitor
- Change: Rename class Serializable as Snippet.
- Change: Move all Snippets from folder ibeosdk and ibeosdk/Serializable into ibeosdk/datablocks/snippets.
- Change: Move class Command into ibeosdk/datablocks/commands.
- Feature: Add command support for IbeoLux and IbeoEcu.
- Feature: add command CommandEcuAppBaseCtrl
- Feature: add command CommandEcuAppBaseStatus
- Feature: add command CommandEcuSetFilter
- Feature: add command CommandLuxGetParameter
- Feature: add command CommandLuxGetStatus
- Feature: add command CommandLuxReset
- Feature: add command CommandLuxResetToDefaultParameters
- Feature: add command CommandLuxSaveConfig
- Feature: add command CommandLuxSetNtpTimestampSync
- Feature: add command CommandLuxSetParameter
- Feature: add command CommandLuxStartMeasure
- Feature: add command CommandLuxStopMeasure
- Feature: Add classes ParameterIndex and ParameterData for the set/getParameter
- Bugfix: Avoid compiler warning in Point2dFloat::rotated.
- Feature: Introduce global enum statuscodes::Codes

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 3.0.3

- Change: moved CarriageWayList6970 Measurement keys to class MeasurementKey

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 3.0.2

- Feature: Added support for new Datablock CarriageWayList6970.
- Feature: Added demo file \ref addon_cw6970_demo_page "CarriageWayList6970Demo.cpp"
- Feature: Added class lanes::LaneHandler
- Feature: Added class lanes::CarriageWay
- Feature: Added class lanes::CarriageWayList
- Feature: Added class lanes::CarriageWaySegment
- Feature: Added class lanes::Lane
- Feature: Added class lanes::LaneSegment
- Feature: Added class lanes::LaneSupportPoint

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 3.0.1

- Interface-Change: Namespace ibeo has been renamed as ibeosdk.
- Interface-Change: In class ScannerInfo, getResolutionInfo now returns a references instead of a pointer.
- Interface-Change: In class ObjectEcuEtDyn getMesurementList now return a const reference.
- Feature: Introduce datablock RefObjectLisEcuEt (0x2290).
- Feature: Introduce datablock RefObjectListEcuEtDyn (0x2291).
- Feature: Introduce datablock PositionWgs84_2604. PositionWgs84 is not a datablock any longer but a serializable attribute of PositionWgs84_2604.
- Feature: Added class Line2dFloat
- Feature: Added class Matrix2dFloat
- Feature: Added class RotationMatrix2dFloat
- Feature: Added class TransformationMatrix2dFloat
- Feature: Added additional functions to Point2dFloat
- Feature: Added additional functions to PositionWgs84
- Feature: Add function to read/write bitwise from/into a char buffer.
- Feature: Add ScanPointEcu flags ESPF_RoadMarking, ESPF_Curbstone and ESPF_Guardrail.
- Feature: Add setter to class ScanPointEcu.
- Feature: Add setter methods to class ResolutionInfo
- Bugfix: In class ScannerInfo use automatic assignment operator. The old implementation was incomplete.
- Bugfix: Linux: In makefiles use § instead of _ as delimiter for the sed command calls.
- Change: For TCP/IP connections set the socket option "no_delay".
- Change: Add and clarify some error messages.
- Change: Definition of PositionWgs84 functions added.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.11.1

- Feature: Introduce datablock MeasurementList2281
- Bugfix: Add missing getter for the variable content of datablock DeviceStatus6303.
- Bugfix: Rename ObjectScala::m_objectBoxSigma as m_objectBoxSizeSigma.
- Bugfix: Correct endianess in serialization of OGpsImuStatus.
- Bugfix: Correct endianess in serialization of OGpsImuMessage.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.10.1

- Feature: Introduce class MeasurementKey.
- Feature: Add VS2010 solution "ibeosdk_VS2010.sln" which supports x64 configuration if WinSDK 7.1 is installed.
- Feature: Add support for data type ObjectListScala2271.
- Bugfix: Correct the serialization of 0x6301 (before BE now LE).
- Bugfix: CanMessageListener was broken and not compilable. Fixed.
- Bugfix: Improve receive thread termination in Ibeo TCP/IP devices.
- Bugfix: Fix a memory hole in Measurement::deserialize when receiving string measurements.
- Bugfix: Correct some boost include path in ibeosdk_VS2008.vcproj and all VS2010 projects.
- Bugfix: Define symbols __LITTLE_ENDIAN and __BIG_ENDIAN for Visual Studio.
- Change: Set the setting in the VS property sheets in such a way, that it is easier to use
  the same boost include files for both, the 32 bit and the 64 bit version.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.9.1

- Feature: Add datablock OGpsImuMessage (0x2610)
- Feature: Add datablock OGpsImuStatus (0x2611)
- Change: In datablock ObjectEcutEtDyn rename attributes
  - m_reserved1 as m_objectBoxHeightOffset
  - m_reserved2 as m_objectBoxHeightOffsetSigma
  - and add getter.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.8.1

- Bugfix: Prevent crash when destructing device object by unregister all listener and streamers in derived classes.
- Bugfix: Add missing files to VS project filters.
- Change: Add attribute m_flags to class ObjectListEcuEtDyn. m_reserved1 now is only 8 bits.dd attribute m_flags
          to class ObjectListEcuEtDyn. m_reserved1 now is only 8 bits.
- Change: Increase the size of the message receive buffer to handle also scans from larger fusion systems.
- Feature: Add troubleshooting section in HOWTO.txt to handle the problem of too small receive buffer if needed.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

##  Version 2.7.1

- Feature: Add support for VS 2008
- Bugfix: Remove the max number of point limitation in class ScanLux to be compatible with early Scala sensors.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.6.1 - 2.6.2

- Feature/Bugfix: Make all DataBlock classes copyable.
- Bugfix: Fix some problems in the message receive function that led
  - Untruely warnings due to skipped bytes that actually have already been processed.
  - Lost messages due to misalignment of the buffer.
- Change: Introduce properties sheets in Visual Studio project to simplify to switch to other boost versions.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.5.1

- Feature: Support of data block DeviceStatus6303.
- Feature: Support of data block ObjectListEcuEtDyn 0x2281.
- Feature: Implement possibility of log stream capturing.
- Change: Add compiler flags -Wsign-conversion and -Wshadow in Linux Makefile.
- Bugfix: Prevent possible deadlock situations in some data blocks deserialize method.
- Bugfix: correct names of object orientation attributes in class ObjectEcu and ObjectEcuEt.
- Bugfix: If there are skipped bytes due to the fact that the receiving MsgBuffer didn't contain any magic word, this will also be reported now.
- Deprecated: ObjectEcu::getYawAngle/setYawAngle, use getObjectBoxOrientation/setObjectBoxOrientation instead.
- Deprecated: ObjectEcu::getYawAngleSigma/setYawAngleSigma, use getObjectBoxOrientationSigma/setObjectBoxOrientationSigma instead.
- Deprecated: ObjectEcuEt::getObjCourseAngle/setObjCourseAngle, use getObjBoxOrientation/setObjBoxOrientation instead.
- Deprecated: ObjectEcuEt::getObjCourseAngleSigma/setObjCourseAngleSigma, use getObjBoxOrientationSigma/setObjBoxOrientationSigma instead.
- Deprecated: ObjectListEcu::getScanStartTimestamp/setScanStartTimestamp, use getTimestamp/setTimestamp instead.
- Deprecated: ObjectListEcuEt::getScanStartTimestamp, use getTimestamp instead.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.4.0 - 2.4.2

- Feature: Add class ScannerProperties to provide information regarding scanners.
- Feature: Add enum for object flags in classes ObjectScala and ObjectEcuEt and
           add getter and setter for these flags.
- Feature: VS2012 solution now also contains a x64 configuration.
- Feature: Streamer and Listener now can be unregistered from Devices.
- Feature: Add streamer support to class IdcFile.
- Feature: In class ObjectEcu rename m_reserved3 as m_yawAngleSigma.
- Update the HOWTO.txt
- Bugfix: Remove angle check during deserialization in class ScanLux, since the angle
          range is not valid for older Scala B2 sensors which are sending also ScanLux
          datablocks.
- Bugfix: Correct many errors in doxygen documentation.
- Bugfix: In enum ScannerType add symbol for MiniLux and remove unsupported AlascaXT.
- Bugfix: Make the ethernet receive thread more robust against erroneous data received.
- Change: DataType now has been renamed as DataTypeId and is now a
          ComparableUnconvertable.
- Change: Small fixes to ensure (yet unsupported) VS2008 compatibility.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.3.0

- Bugfix: Handle not_a_date_time separately in TimeConversion::toString to
          prevent crash due to exception.
- Bugfix:In IbeoSdkWriterDemo allow file splitting also on ScanEcu and Scan2208.
- IbeoSdkFileDemo do now use the notify-listener concept to avoid switch-case
  to select the DataListener.
- Add method setInvalid to class NTPTime.
- Add eclipse target "staticdemos".

- Internal: DataBlocks now automatically register to devices.
- Internal: Enum DataTypes is deprecated and will be removed in future
            releases.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.2.0

- Add Devices
  - IbeoScala
  - IbeoMiniLux
- Add DataBlocks
  - 0x1002: CanMessage
  - 0x1100: FrameEndSeparator
  - 0x2208: Scan2208
  - 0x2270: ScalaObjectList
  - 0x2604: PositionWgs84
  - 0x2806: VehicleStateEcuBasic2806
  - 0x6301: DeviceStatus
- Add VS 2012 support
- Demos
  - IbeoSdkWriterDemo now supports all devices
  - IbeoSdkDataLoggerDemo (Linux only)
    - now supports all devices
    - now uses boost program_options library to parse command line arguments

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.1.0

- Add makefile targets to create shared and static libs
- Fix some issues with template declaration/usage order
  for g++ 4.7+ and --std=c++11
- Fix a C++11 incompatiblity with std::make_pair reported for VS 2012
- Clarify HOWTO, add source link for boost libraries

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Version 2.0.0

- Initial release

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
