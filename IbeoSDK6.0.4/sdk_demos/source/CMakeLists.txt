# ==============================================================================
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# ==============================================================================
#set(CMAKE_CXX_STANDARD 11)

# ==============================================================================
# name of the project
project(ibeo-common-sdk_demos LANGUAGES CXX)

# ==============================================================================

option(BUILD_SHARED_LIBS "specifies the type of libraries (SHARED or STATIC) to build" ON)
option (IBEO_COMMON_MASTER_BUILD "Specifies, if the complete ibeo-common project is built within one master CMake-Project" OFF)
mark_as_advanced(IBEO_COMMON_MASTER_BUILD)

# ==============================================================================
# package dependencies

if (BUILD_SHARED_LIBS)
    set(Boost_USE_STATIC_LIBS OFF)
else()
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
endif()

find_package(Boost REQUIRED COMPONENTS system thread program_options filesystem)
find_package(JPEG REQUIRED)

# add ibeoSDK (required)
if (NOT IBEO_COMMON_MASTER_BUILD)
    if (BUILD_SHARED_LIBS)
        find_package(ibeo-common-sdk REQUIRED)
    else()
        find_package(ibeo-common-sdk-static REQUIRED)
    endif()
endif()


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
    set(CXXCOMPILEOPTIONS -Wall -ansi -pedantic -Wextra -Wconversion -Wsign-conversion -Wno-long-long
                          -Wshadow -Wcast-qual -Wcast-align -Wdelete-incomplete
                          -Wlogical-not-parentheses
                          -Wswitch-bool -Wswitch -Wdouble-promotion)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    SET(CXXCOMPILEOPTIONS /W2 /MP)
endif()

# ==============================================================================
# where to install libraries and binaries to (subfolders)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_INSTALL_LIBDIR lib)
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_INCLUDEDIR .)
set(CMAKE_INSTALL_DOCDIR doc)
set(CMAKE_INSTALL_SHAREDIR share)

# ==============================================================================
# adding subfolders which specify the targets

add_subdirectory(sdk_demos)

# ==============================================================================

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

# ==============================================================================
