if (DEFINED IBEOSDK_DEPENDENCIES_GUARD)
    return()
endif()

include (CMakeFindDependencyMacro)

# logging
if(NOT IBEO_COMMON_MASTER_BUILD)
    find_dependency(ibeo-common-logging REQUIRED)
endif()

# Boost packages
set(Boost_USE_STATIC_LIBS OFF)
# TODO: find_dependency does not work for cmake version < 3.10. Should be fixed
find_package(Boost REQUIRED COMPONENTS system thread program_options date_time filesystem unit_test_framework)

# jpeg
find_dependency(JPEG REQUIRED)

# since jpeg package does not provide cmake targets, we need to create an
# imported target. But from cmake 3.12 on, the find_package(JPEG) creates an
# imported target called JPEG::JPEG.
# The solution to support older cmake versions is to generate this target as
# well, if it is not present.
if (NOT TARGET JPEG::JPEG)
    set(JPEG_LIBRARIES ${JPEG_LIBRARY})
    set(JPEG_INCLUDE_DIRS "${JPEG_INCLUDE_DIR}")

    add_library(JPEG::JPEG UNKNOWN IMPORTED)

    if(JPEG_INCLUDE_DIRS)
        set_target_properties(JPEG::JPEG PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${JPEG_INCLUDE_DIRS}")
    endif()

    if(EXISTS "${JPEG_LIBRARY}")
        set_target_properties(JPEG::JPEG PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES "C"
                IMPORTED_LOCATION "${JPEG_LIBRARY}")
    endif()

    if(EXISTS "${JPEG_LIBRARY_RELEASE}")
        set_property(TARGET JPEG::JPEG APPEND PROPERTY
                IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(JPEG::JPEG PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
                IMPORTED_LOCATION_RELEASE "${JPEG_LIBRARY_RELEASE}")
    endif()

    if(EXISTS "${JPEG_LIBRARY_DEBUG}")
        set_property(TARGET JPEG::JPEG APPEND PROPERTY
                IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(JPEG::JPEG PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
                IMPORTED_LOCATION_DEBUG "${JPEG_LIBRARY_DEBUG}")
    endif()
endif()

set(IBEOSDK_DEPENDENCIES_GUARD 1)
