# ==============================================================================
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# ==============================================================================

#enable_language(CXX)

# ==============================================================================
# name of the project
project(ibeo-common-sdk LANGUAGES CXX)

message(STATUS "**Enter main CMakeLists.txt file. ***")

# ==============================================================================
option(BUILD_SHARED_LIBS "specifies the type of libraries (SHARED or STATIC) to build" ON)
option (IBEO_COMMON_MASTER_BUILD "Specifies, if the complete ibeo-common project is built within one master CMake-Project" OFF)
mark_as_advanced(IBEO_COMMON_MASTER_BUILD)

if (BUILD_SHARED_LIBS)
    set(DEPENDENCY_FILE dependencies.cmake)
else()
    set(DEPENDENCY_FILE dependencies-static.cmake)
endif()

include(resources/version.cmake)
include(resources/${DEPENDENCY_FILE})

# ==============================================================================
# C++ compiler options
# ==============================================================================

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CXXCOMPILEOPTIONS -Wall -ansi -pedantic -Wextra -Wconversion -Wsign-conversion -Wshadow
                          #-Wcast-qual -Wcast-align -Wzero-as-null-pointer-constant -Wuseless-cast -Wdelete-incomplete
                          #-Wlogical-op -Wlogical-not-parentheses -Wbool-compare -Wsuggest-override -Wsuggest-final-methods -Wsuggest-final-types
                          #-Wmaybe-uninitialized -Wswitch-bool -Wswitch-default -Wdouble-promotion
                          #-Wenum-compare -Winit-self -Wno-long-long -Wformat
                          -std=c++11
            )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CXXCOMPILEOPTIONS -Wall -ansi -pedantic -Wextra
                          -Werror=conversion
                          -Werror=sign-conversion
                          -Wno-long-long
                          -Werror=shadow
                          -Werror=cast-qual
                          -Werror=cast-align
                          -Werror=delete-incomplete
                          -Werror=logical-not-parentheses
                          -Werror=switch-bool
                          -Werror=switch
                          -Werror=double-promotion
                          -Werror=type-safety
                          -Werror=type-limits
                          -Werror=sign-conversion
                          -Werror=sign-compare
                          -Werror=tautological-compare
                          -Werror=tautological-constant-in-range-compare
                          -Werror=tautological-overlap-compare
                          -Werror=tautological-type-limit-compare
                          -Werror=tautological-unsigned-enum-zero-compare
                          -Werror=tautological-unsigned-zero-compare
                          -Werror=thread-safety
                          -Werror=thread-safety-analysis
                          -Werror=thread-safety-attributes)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    SET(CXXCOMPILEOPTIONS
        /W2     # warning level 2
        /wd4307 # disable C4307: integer overflow
        /MP
    )
    #Todo: We need further investigation for additional flags
endif()

# ==============================================================================

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_INSTALL_LIBDIR lib)
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_INCLUDEDIR .)
set(CMAKE_INSTALL_DOCDIR doc)
set(CMAKE_INSTALL_SHAREDIR share)

set(SRC_PREFIX sdk/source/sdk)

# ==============================================================================

if (BUILD_SHARED_LIBS)
    set(EXPORT_TARGETS_FILE     ibeo-common-sdkTargets.cmake)
    set(EXPORT_CONFIG_FILE      ibeo-common-sdkConfig.cmake)
    set(EXPORT_NAMESPACE        ibeo-common::)
    set(EXPORT_CONFIG_SUBFOLDER ibeo-common-sdk)
else ()
    set(EXPORT_TARGETS_FILE     ibeo-common-sdk-staticTargets.cmake)
    set(EXPORT_CONFIG_FILE      ibeo-common-sdk-staticConfig.cmake)
    set(EXPORT_NAMESPACE        ibeo-common::)
    set(EXPORT_CONFIG_SUBFOLDER ibeo-common-sdk-static)
endif ()

add_subdirectory(sdk)

enable_testing()
add_subdirectory(sdk/test)
add_subdirectory(doc)

# ==============================================================================



configure_file(${CMAKE_CURRENT_LIST_DIR}/resources/configTemplate.cmake ${CMAKE_BINARY_DIR}/${EXPORT_CONFIG_FILE} @ONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/resources/${DEPENDENCY_FILE} ${CMAKE_BINARY_DIR}/${DEPENDENCY_FILE} COPYONLY)

install(EXPORT ibeo-common-sdkTargets
        FILE ${EXPORT_TARGETS_FILE}
        DESTINATION ${CMAKE_INSTALL_SHAREDIR}/${EXPORT_CONFIG_SUBFOLDER}
        NAMESPACE ${EXPORT_NAMESPACE})

install(
        FILES
             ${CMAKE_BINARY_DIR}/${EXPORT_CONFIG_FILE}
             ${CMAKE_CURRENT_LIST_DIR}/resources/${DEPENDENCY_FILE}
        DESTINATION
             ${CMAKE_INSTALL_SHAREDIR}/${EXPORT_CONFIG_SUBFOLDER}
)

# This makes the project importable from the build directory
# never install this file!
export(EXPORT ibeo-common-sdkTargets
       FILE   ${EXPORT_TARGETS_FILE}
       NAMESPACE ${EXPORT_NAMESPACE})

# ==============================================================================
