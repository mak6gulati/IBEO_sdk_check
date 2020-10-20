# ==============================================================================
cmake_minimum_required (VERSION 3.5 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)

message (STATUS "*** Entering main CMakeLists.txt file of ibeo-common-logging. ***")


# ==============================================================================
# project
# ==============================================================================

project(ibeo-common-logging LANGUAGES CXX)


# ==============================================================================
# C++ compiler options
# ==============================================================================

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CXXCOMPILEOPTIONS -Wall -ansi -pedantic -Wextra -Wconversion -Wsign-conversion -Wshadow
            #-Wcast-qual -Wcast-align -Wzero-as-null-pointer-constant -Wuseless-cast -Wdelete-incomplete
            #-Wlogical-op -Wlogical-not-parentheses -Wbool-compare -Wsuggest-override -Wsuggest-final-methods -Wsuggest-final-types
            #-Wmaybe-uninitialized -Wswitch-bool -Wswitch-default -Wdouble-promotion
            #-Wenum-compare -Winit-self -Wno-long-long -Wformat
            -std=c++11
            )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CXXCOMPILEOPTIONS -Wall -ansi -pedantic -Wextra -Wconversion -Wsign-conversion -Wno-long-long
            -Wshadow -Wcast-qual -Wcast-align -Wdelete-incomplete
            -Wlogical-not-parentheses
            -Wswitch-bool -Wswitch -Wdouble-promotion)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set (CXXCOMPILEOPTIONS /W2 /MP)
endif ()


# ==============================================================================

option (BUILD_SHARED_LIBS "specifies the type of libraries (SHARED or STATIC) to build" ON)
option (IBEO_COMMON_MASTER_BUILD "Specifies, if the complete ibeo-common project is built within one master CMake-Project" OFF)
mark_as_advanced(IBEO_COMMON_MASTER_BUILD)


# ==============================================================================
# packages
# ==============================================================================

if (BUILD_SHARED_LIBS)
    set(DEPENDENCY_FILE dependencies.cmake)
else()
    set(DEPENDENCY_FILE dependencies-static.cmake)
endif()

include(resources/version.cmake)
include(resources/${DEPENDENCY_FILE})


# ==============================================================================
# cmake install variables
# ==============================================================================

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_INSTALL_LIBDIR lib)
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_INCLUDEDIR .)
set(CMAKE_INSTALL_DOCDIR doc)
set(CMAKE_INSTALL_SHAREDIR share)


# ==============================================================================
# cmake export variables
# ==============================================================================

set (EXPORT_NAMESPACE ibeo-common-logging::)

if (BUILD_SHARED_LIBS)
    set (EXPORT_TARGETS_FILE     ibeo-common-loggingTargets.cmake)
    set (EXPORT_CONFIG_FILE      ibeo-common-loggingConfig.cmake)
    set (EXPORT_CONFIG_SUBFOLDER ibeo-common-logging)
    set (DEPENDENCY_FILE         dependencies.cmake)
else ()
    set (EXPORT_TARGETS_FILE     ibeo-common-logging-staticTargets.cmake)
    set (EXPORT_CONFIG_FILE      ibeo-common-logging-staticConfig.cmake)
    set (EXPORT_CONFIG_SUBFOLDER ibeo-common-logging-static)
    set (DEPENDENCY_FILE         dependencies-static.cmake)
endif ()


# ==============================================================================
# subdirectories
# ==============================================================================

add_subdirectory(logging)


# ==============================================================================
# install
# ==============================================================================

configure_file (${CMAKE_CURRENT_LIST_DIR}/resources/defaultConfig.cmake ${CMAKE_BINARY_DIR}/${EXPORT_CONFIG_FILE} @ONLY)
configure_file (${CMAKE_CURRENT_LIST_DIR}/resources/${DEPENDENCY_FILE} ${CMAKE_BINARY_DIR}/${DEPENDENCY_FILE} COPYONLY)

install (
        EXPORT ibeo-common-loggingTargets
        FILE ${EXPORT_TARGETS_FILE}
        DESTINATION ${CMAKE_INSTALL_SHAREDIR}/${EXPORT_CONFIG_SUBFOLDER}
        NAMESPACE ${EXPORT_NAMESPACE}
)

install (
        FILES
        ${CMAKE_CURRENT_LIST_DIR}/resources/logconfig.xml
        ${CMAKE_CURRENT_LIST_DIR}/resources/${DEPENDENCY_FILE}
        DESTINATION ${CMAKE_INSTALL_SHAREDIR}/${EXPORT_CONFIG_SUBFOLDER}
)

install (
        FILES ${CMAKE_BINARY_DIR}/${EXPORT_CONFIG_FILE}
        DESTINATION ${CMAKE_INSTALL_SHAREDIR}/${EXPORT_CONFIG_SUBFOLDER}
        RENAME ${EXPORT_CONFIG_FILE}
)

# ==============================================================================
# export
# ==============================================================================

# This makes the project importable from the build directory
# never install this file!
export (
        EXPORT ibeo-common-loggingTargets
        FILE   ${EXPORT_TARGETS_FILE}
        NAMESPACE ${EXPORT_NAMESPACE}
)


# ==============================================================================
# unit tests
# ==============================================================================

enable_testing()

# ==============================================================================

message (STATUS "*** Leaving main CMakeLists.txt file of ibeo-common-logging. ***")