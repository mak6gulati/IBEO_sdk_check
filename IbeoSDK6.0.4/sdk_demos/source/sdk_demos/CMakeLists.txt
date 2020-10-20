# ==============================================================================
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# ==============================================================================

#enable_language(CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ==============================================================================
# PCAP
find_path(PCAP_ROOT_DIR NAMES include/pcap.h HINTS $ENV{PCAPDIR})
if(PCAP_ROOT_DIR)
    message("PCAP library found at ${PCAP_ROOT_DIR}")
    find_path(PCAP_INCLUDE_DIR NAMES pcap.h HINTS ${PCAP_ROOT_DIR}/include DOC "pcap include directory")
    if (MSVC)
        if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            # Windows 64 bit.
            find_library(PCAP_LIBRARY NAMES wpcap HINTS ${PCAP_ROOT_DIR}/lib/x64 DOC "pcap library")
        else ()
            # Windows 32 bit.
            find_library(PCAP_LIBRARY NAMES wpcap HINTS ${PCAP_ROOT_DIR}/lib DOC "pcap library")
        endif ()
    else (MSVC)
        # Non-Windows.
        find_library(PCAP_LIBRARY NAMES pcap HINTS ${PCAP_ROOT_DIR}/lib DOC "pcap library")
    endif (MSVC)
    mark_as_advanced(PCAP_LIBRARY PCAP_INCLUDE_DIR)
    include_directories (${PCAP_INCLUDE_DIR})
    add_definitions(
            -DPCAP_LIBRARY=${PCAP_LIBRARY}
            -DPCAP_INCLUDE_DIR=${PCAP_INCLUDE_DIR}
    )
else()
    message("PCAP library not found! Please set environment variable PCAPDIR.")
endif ()

# ==============================================================================
function(setup)
    cmake_parse_arguments(setup "" "TARGET" "SOURCES;LIBRARIES;INCLUDE_DIRS" ${ARGN})

    if(NOT setup_TARGET)
        message(FATAL_ERROR "You must provide a target name")
    endif()

    if(NOT setup_SOURCES)
        message(FATAL_ERROR "You must provide at least one source file")
    endif()

    add_executable(${setup_TARGET} ${setup_SOURCES})

    set_target_properties(${setup_TARGET} PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            INSTALL_RPATH_USE_LINK_PATH TRUE
            )

    target_compile_options(${setup_TARGET} PRIVATE ${CXXCOMPILEOPTIONS})

    install(TARGETS ${setup_TARGET} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/demo COMPONENT demo)

    target_link_libraries(${setup_TARGET} PRIVATE
        ibeo-common::sdk
        Boost::system
        Boost::program_options
        Boost::filesystem
        Boost::thread
        ${JPEG_LIBRARIES}
        ${setup_LIBRARIES})

    target_include_directories(${setup_TARGET} PRIVATE "${setup_INCLUDE_DIRS}" ${JPEG_INCLUDE_DIR})

    if (WIN32)
        target_compile_definitions(${setup_TARGET} PRIVATE -D_WIN32_WINNT=0x0601 -DWIN32_LEAN_AND_MEAN)
    endif()

    if (BUILD_SHARED_LIBS)
        target_compile_definitions(${setup_TARGET} PUBLIC -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK)
    else()
        target_compile_definitions(${setup_TARGET} PUBLIC -DBOOST_ALL_NO_LIB)
    endif()

endfunction()

# ==============================================================================
setup(TARGET "carriageWayListDemo"
        SOURCES "src/IbeoSdkCarriageWayListDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
if (NOT WIN32)
    setup(TARGET "dataLoggerDemo"
        SOURCES "src/IbeoSdkDataLoggerDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )
endif()

# ==============================================================================
setup(TARGET "ecuLiveDemo"
        SOURCES "src/IbeoSdkEcuLiveDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "ecuSimDemo"
        SOURCES "src/IbeoSdkEcuSimDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "fileDemo"
        SOURCES "src/IbeoSdkFileDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "generalFileDemo"
        SOURCES "src/IbeoSdkGeneralFileDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "laneEvaluationDemo"
        SOURCES "src/IbeoSdkLaneEvaluationDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "luxHrLiveDemo"
        SOURCES "src/IbeoSdkLuxHrLiveDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "luxLiveDemo"
        SOURCES "src/IbeoSdkLuxLiveDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "metaInformationDemo"
        SOURCES "src/IbeoSdkMetaInformationDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "miniLuxLiveDemo"
        SOURCES "src/IbeoSdkMiniLuxLiveDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "pointCloudPlane7510Demo"
        SOURCES "src/IbeoSdkPointCloud7510Demo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "scalaLiveDemo"
        SOURCES "src/IbeoSdkScalaLiveDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "scalaSimDemo"
        SOURCES "src/IbeoSdkScalaSimDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "trackingBoxLiveDemo"
        SOURCES "src/IbeoSdkTrackingBoxLiveDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "writerDemo"
        SOURCES "src/IbeoSdkWriterDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "scalaUdpLiveDemo"
        SOURCES "src/ScalaUdpLiveDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================
setup(TARGET "scalaUdpSimDemo"
        SOURCES "src/ScalaUdpSimDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================

setup(TARGET "CommaSeparatedValuesWriterDemo"
        SOURCES "src/CommaSeparatedValuesWriterDemo.cpp"
        LIBRARIES
        INCLUDE_DIRS )

# ==============================================================================

