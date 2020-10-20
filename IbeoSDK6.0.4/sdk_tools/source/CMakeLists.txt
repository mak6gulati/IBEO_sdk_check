# ==============================================================================
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# ==============================================================================

# ==============================================================================
# name of the project
project(ibeo-common-sdk_tools LANGUAGES CXX)

# ==============================================================================
option(BUILD_SHARED_LIBS "specifies the type of libraries (SHARED or STATIC) to build" ON)

# ==============================================================================
# C++ compiler options
# ==============================================================================

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CXXCOMPILEOPTIONS -Wall -ansi -pedantic -Wextra -Wconversion -Wsign-conversion -Wshadow
                          #-Wcast-qual -Wcast-align -Wzero-as-null-pointer-constant -Wuseless-cast -Wdelete-incomplete
                          #-Wlogical-op -Wlogical-not-parentheses -Wbool-compare -Wsuggest-override -Wsuggest-final-methods -Wsuggest-final-types
                          #-Wmaybe-uninitialized -Wswitch-bool -Wswitch-default -Wdouble-promotion
                          #-Wenum-compare -Winit-self -Wno-long-long -Wformat
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

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_INSTALL_LIBDIR lib)
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_INCLUDEDIR .)
set(CMAKE_INSTALL_DOCDIR doc)
set(CMAKE_INSTALL_SHAREDIR share)

# ==============================================================================

add_subdirectory(sdk_tools)

# ==============================================================================

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

# ==============================================================================
