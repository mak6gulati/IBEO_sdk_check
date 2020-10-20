# ==============================================================================
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# ==============================================================================

message(STATUS "**Enter ibeosdk CMakeLists.txt file. ***")

# ==============================================================================

add_library(sdk "")

# ==============================================================================
# function used in subfolders to set public headers for the target ibeosdk
function(setupHeaders)
    cmake_parse_arguments(setupHeaders "" "" "HEADERS;GROUP" ${ARGN})

    if(NOT setupHeaders_HEADERS)
        message(FATAL_ERROR "At least one header file should be provided")
    endif()

    foreach(file ${setupHeaders_HEADERS})
        #list(APPEND headersBuildInterface $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/${file}>)
        #file(RELATIVE_PATH relFile ${CMAKE_SOURCE_DIR}/src/sdk ${CMAKE_CURRENT_LIST_DIR}/${file})
        #list(APPEND headersInstallInterface $<INSTALL_INTERFACE:${relFile}>)
        list(APPEND hds ${CMAKE_CURRENT_LIST_DIR}/${file})
    endforeach()

    set(setupHeaders_GROUP "Header Files\\${setupHeaders_GROUP}")

    source_group(${setupHeaders_GROUP} FILES ${hds})
    target_sources(sdk PRIVATE ${hds})
    #target_sources(sdk PRIVATE ${headersInstallInterface})
endfunction()

# ==============================================================================
# function used in subfolders to set sources for the target ibeosdk
function(setupSources)
    cmake_parse_arguments(setupSources "" "" "SOURCES;GROUP" ${ARGN})

    if(NOT setupSources_SOURCES)
        message(FATAL_ERROR "At least one source file should be provided")
    endif()

    foreach(file ${setupSources_SOURCES})
        list(APPEND src ${CMAKE_CURRENT_LIST_DIR}/${file})
    endforeach()

    set(setupSources_GROUP "Source Files\\${setupSources_GROUP}")

    source_group(${setupSources_GROUP} FILES ${src})
    target_sources(sdk PRIVATE ${src})
endfunction()

# ##############################################################################
# Function to create a version header file from a version.cmake file
# Arguments:
#     VERSIONFILE - absolute path to the version.cmake file
#                   if not specified the function searches in ${CMAKE_CURRENT_LIST_DIR}/resources and
#                   ${CMAKE_CURRENT_LIST_DIR}/../resources for a version.cmake file
#     TARGETFOLDER - target folder where the header file should be created
#     TARGETNAME - filename of the header file
#                  if not specifed version_defines.hpp will be used
#     NAMESPACE  - namespace the should be used in the headerfile, nested namespaces are
#                  separate by ::, e.g. ibeo::common
# ------------------------------------------------------------------------------
function(createVersionHeaderFile)

    set(oneValueArgs VERSIONFILE TARGETFOLDER TARGETNAME NAMESPACE)

    cmake_parse_arguments(VERSIONHEADER "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (VERSIONHEADER_VERSIONFILE)
        set(versionCMakeFile ${VERSIONHEADER_VERSIONFILE})
    else()
        # search for file
        if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/resources/version.cmake")
            set(versionCMakeFile "${CMAKE_CURRENT_LIST_DIR}/resources/version.cmake")
        elseif (EXISTS "${CMAKE_CURRENT_LIST_DIR}/../resources/version.cmake")
            set(versionCMakeFile "${CMAKE_CURRENT_LIST_DIR}/../resources/version.cmake")
        else()
            message(SEND_ERROR, "VERSIONFILE not set and file version.cmake can't be found in default locations")
        endif()
    endif()

    if (NOT VERSIONHEADER_TARGETFOLDER)
        message(SEND_ERROR, "TARGETFOLDER is missing")
    else()
        set(targetDir ${VERSIONHEADER_TARGETFOLDER})
    endif()

    if (NOT VERSIONHEADER_TARGETNAME)
        # use default file name
        set(versionFile "${targetDir}/version_defines.hpp")
    else()
        set(versionFile "${targetDir}/${VERSIONHEADER_TARGETNAME}")
    endif()

    set(NAMESPACE_BEGIN "")
    set(NAMESPACE_END "")
    if (VERSIONHEADER_NAMESPACE)
        string(REPLACE "::" ";" namespaceList ${VERSIONHEADER_NAMESPACE})
        foreach(namespace IN LISTS namespaceList)
            set(NAMESPACE_BEGIN "${NAMESPACE_BEGIN}\nnamespace ${namespace} {")
            set(NAMESPACE_END "\n} // namespace ${namespace}${NAMESPACE_END}")
        endforeach()
    endif()

    include(${versionCMakeFile})

    string(TOLOWER "${PROJECT_VERSION_IS_SNAPSHOT}" PROJECT_VERSION_IS_SNAPSHOT)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version_defines.hpp.in ${versionFile})

    set(version_file_name ${version_file} PARENT_SCOPE)
endfunction()

createVersionHeaderFile(TARGETFOLDER "${CMAKE_CURRENT_BINARY_DIR}" NAMESPACE "ibeo::common::sdk")

# ==============================================================================

include(include/ibeo/common/sdk/CMakeLists.txt)
include(src/CMakeLists.txt)

# ==============================================================================

set(OUTPUTPREFIX "")

# ==============================================================================

if (WIN32)
    # this is very important for buildings dll libraries on windows
    target_compile_definitions(sdk PUBLIC -D_WIN32_WINNT=0x0601 -DWIN32_LEAN_AND_MEAN)

    if(BUILD_SHARED_LIBS)
        target_compile_definitions(sdk PUBLIC -DIBEOSDKLIBDLL_SHARED)
        target_compile_definitions(sdk PRIVATE -DIBEOSDKLIBDLL_EXPORTS)
    else()
        set(OUTPUTPREFIX lib)
    endif()
endif()

# ==============================================================================

if (BUILD_SHARED_LIBS)
    target_compile_definitions(sdk PUBLIC -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK)
else()
    target_compile_definitions(sdk PUBLIC -DBOOST_ALL_NO_LIB)
endif()

target_compile_options(sdk PRIVATE ${CXXCOMPILEOPTIONS})

set_target_properties(sdk PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        WINDOWS_EXPORT_ALL_SYMBOLS ON
        OUTPUT_NAME ${OUTPUTPREFIX}ibeo-common-sdk
        DEBUG_POSTFIX _d
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        )

target_include_directories(
    sdk
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(
    sdk
    PUBLIC
        Boost::thread
        Boost::system
        Boost::program_options
        Boost::date_time
        Boost::filesystem
        JPEG::JPEG
        ibeo-common-logging::logging
)

add_library(${EXPORT_NAMESPACE}sdk ALIAS sdk)

# ==============================================================================

# export ibeo-common-sdk to the target set "ibeo-common-sdkTargets"
install(TARGETS sdk EXPORT ibeo-common-sdkTargets
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT sdk)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT headers)

# install .pdb files on windows in debug
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    install(
        FILES
        $<TARGET_PDB_FILE:sdk>
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        OPTIONAL
    )
endif()

# ==============================================================================
