# ==============================================================================

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ==============================================================================

#add build target for all tests (required by cLion)
#note: within cLion, you need to any test als 'Executable' for build target 'test'
ADD_CUSTOM_TARGET(logging_run_AllTests COMMAND ${CMAKE_MAKE_PROGRAM} test)

# ==============================================================================

find_package(Boost REQUIRED COMPONENTS system thread unit_test_framework filesystem)


# ==============================================================================

set(common_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR})
set(common_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/StringEx.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StringEx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSupport.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSupport.cpp
)

# ==============================================================================

function(add_boost_test)
    cmake_parse_arguments(
        setup
        ""
        "TARGET"
        "SOURCES;INCLUDES"
        ${ARGN}
    )

    if(NOT setup_TARGET)
        message(FATAL_ERROR "You must provide a target name")
    endif()

    if(NOT setup_SOURCES)
        message(FATAL_ERROR "You must provide at least one source file")
    endif()

    add_executable(
        ${setup_TARGET}
        ${common_SOURCES}
        ${setup_SOURCES}
        ${setup_INCLUDES}
    )

    set(OUTPUTPREFIX "")

    if (WIN32)
        target_compile_definitions(
            ${setup_TARGET}
            PRIVATE
                -D_WIN32_WINNT=0x0601
                -DWIN32_LEAN_AND_MEAN
        )

        if (NOT BUILD_SHARED_LIBS)
            set(OUTPUTPREFIX lib)
        endif ()
    endif()

    target_compile_options(
        ${setup_TARGET} PRIVATE ${CXXCOMPILEOPTIONS}
    )

    if (BUILD_SHARED_LIBS)
        target_compile_definitions(
            ${setup_TARGET}
            PUBLIC
                -DBOOST_ALL_NO_LIB
                -DBOOST_ALL_DYN_LINK
                -DBOOST_TEST_DYN_LINK
        )
    else()
        target_compile_definitions(
            ${setup_TARGET}
            PUBLIC
                -DBOOST_ALL_NO_LIB
        )
    endif()

    set_target_properties(
        ${setup_TARGET}
        PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            WINDOWS_EXPORT_ALL_SYMBOLS ON
            OUTPUT_NAME ${OUTPUTPREFIX}ibeo-common-logging-${setup_TARGET}
            DEBUG_POSTFIX _d
    )

    target_link_libraries(
        ${setup_TARGET}
        PUBLIC
            logging
            Boost::system
            Boost::thread
            Boost::filesystem
            Boost::unit_test_framework
    )

    target_include_directories(
        ${setup_TARGET}
        PRIVATE
            ${common_INCLUDEDIR}
    )

    add_test(
        NAME ${setup_TARGET}
        COMMAND ${setup_TARGET}
    )
endfunction()

# ==============================================================================

# add_subdirectory(backends/asyncloggerbackend_test)
add_subdirectory(backends/fileloggerbackend_test)
add_subdirectory(backends/loggerbackendfactory_test)
add_subdirectory(configuration_test)
add_subdirectory(format_test)
add_subdirectory(logger_test)
add_subdirectory(loggerfactory_test)
add_subdirectory(logmanager_test)
add_subdirectory(logmsgmacro_test)
add_subdirectory(message_test)
add_subdirectory(speed_test)

# ==============================================================================
