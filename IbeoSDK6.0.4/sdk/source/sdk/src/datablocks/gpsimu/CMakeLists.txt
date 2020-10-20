setupSources(SOURCES
        GpsImu.cpp
        GpsImuExporter9001.cpp
        GpsImuImporter9001.cpp

        GROUP datablocks\\gpsimu)

include(${CMAKE_CURRENT_LIST_DIR}/special/CMakeLists.txt)