setupSources(
    SOURCES
        TrafficLightStateList.cpp
        TrafficLightStateListExporter3600.cpp
        TrafficLightStateListImporter3600.cpp
    GROUP datablocks\\trafficlight
)

include(${CMAKE_CURRENT_LIST_DIR}/special/CMakeLists.txt)
