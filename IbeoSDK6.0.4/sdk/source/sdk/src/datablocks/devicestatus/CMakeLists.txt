setupSources(SOURCES
        DeviceStatus.cpp
        DeviceStatusExporter6301.cpp
        DeviceStatusExporter6303.cpp
        DeviceStatusImporter6301.cpp
        DeviceStatusImporter6303.cpp
        DeviceStatusSerializedSize6301.cpp
        DeviceStatusSerializedSize6303.cpp
        GROUP datablocks\\devicestatus)

include(${CMAKE_CURRENT_LIST_DIR}/special/CMakeLists.txt)
