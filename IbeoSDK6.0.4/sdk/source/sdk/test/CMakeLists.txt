# ==============================================================================
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# ==============================================================================

#add build target for all tests (required by cLion)
#note: within cLion, you need to any test als 'Executable' for build target 'test'
ADD_CUSTOM_TARGET(run_AllTests COMMAND ${CMAKE_MAKE_PROGRAM} test)

# ==============================================================================
function(add_boost_test)
    cmake_parse_arguments(setup "" "TARGET" "SOURCES;INCLUDES" ${ARGN}) #LIBRARIES;

    if(NOT setup_TARGET)
        message(FATAL_ERROR "You must provide a target name")
    endif()

    if(NOT setup_SOURCES)
        message(FATAL_ERROR "You must provide at least one source file")
    endif()

        #include common TestSupport stuff
#    set(setup_INCLUDES ${setup_INCLUDES} ../common/TestSupport.hpp)
#    set(setup_SOURCES ${setup_SOURCES} ../common/TestSupport.cpp)

    add_executable(${setup_TARGET} ${setup_SOURCES} ${setup_INCLUDES})

    set_target_properties(${setup_TARGET} PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            )

    target_compile_options(${setup_TARGET} PRIVATE ${CXXCOMPILEOPTIONS})

    target_link_libraries(${setup_TARGET} PRIVATE
            sdk
            Boost::thread
            Boost::system
            Boost::unit_test_framework
            Boost::filesystem
            ${JPEG_LIBRARIES}
            )

    target_include_directories(${setup_TARGET} PRIVATE .. ${Boost_INCLUDE_DIRS} ${JPEG_INCLUDE_DIR})

    add_test(NAME ${setup_TARGET} COMMAND ${setup_TARGET})

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
#
add_subdirectory(src/canMessageTests)
add_subdirectory(src/carriageWayTests)
add_subdirectory(src/command2010Tests)
add_subdirectory(src/contentSeparator7100Tests)
add_subdirectory(src/destinationTests)
add_subdirectory(src/deviceTests)
add_subdirectory(src/eventTagTests)
add_subdirectory(src/frameEndSeparatorTests)
add_subdirectory(src/gpsImuTests)
add_subdirectory(src/ibeoEvent7001Tests)
add_subdirectory(src/idcStreamTests)
add_subdirectory(src/idcTrailer6120Tests)
add_subdirectory(src/idSequenceTests)
add_subdirectory(src/imageTests)
add_subdirectory(src/logPolygon2dTests)
add_subdirectory(src/logMessage64x0Tests)
add_subdirectory(src/measurementListTests)
add_subdirectory(src/missionHandlingTests)
add_subdirectory(src/missionResponseTests)
add_subdirectory(src/mountingPositionTests)
add_subdirectory(src/objectListTests)
add_subdirectory(src/odometryTests)
add_subdirectory(src/pointCloudTests)
add_subdirectory(src/scanTests)
add_subdirectory(src/stateOfOperation9110Tests)
add_subdirectory(src/systemMonitoringTests)
add_subdirectory(src/timeRecordTests)
add_subdirectory(src/timeRelationsListTests)
add_subdirectory(src/trafficLightTests)
add_subdirectory(src/vehicleControl9100Tests)
add_subdirectory(src/vehicleStateTests)
add_subdirectory(src/wgs84Tests)

## ==============================================================================

add_boost_test(TARGET MatrixTests
                SOURCES src/MatrixTests.cpp
                        src/common/TestSupport.cpp
                INCLUDES src/common/MatrixTestSupport.hpp
                        src/common/TestSupport.hpp
        )

# ==============================================================================
add_boost_test(TARGET RectangleTest
                SOURCES src/RectangleTest.cpp
                        src/common/TestSupport.cpp
                INCLUDES src/common/RectangleTestSupport.hpp
                        src/common/TestSupport.hpp
        )

# ==============================================================================
add_boost_test(TARGET VectorTests
                SOURCES src/VectorTests.cpp
                        src/common/TestSupport.cpp
                INCLUDES src/common/VectorTestSupport.hpp
                        src/common/TestSupport.hpp
        )
