# ==============================================================================
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# ==============================================================================

if (BUILD_SHARED_LIBS)
    set(Boost_USE_STATIC_LIBS OFF)
else()
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
endif()

find_package(Boost REQUIRED system thread program_options filesystem)
find_package(JPEG REQUIRED)

# add ibeoSDK (required)
if (BUILD_SHARED_LIBS)
    find_package(ibeo-common-sdk REQUIRED)
else()
    find_package(ibeo-common-sdk-static REQUIRED)
endif()

# ==============================================================================
function(setup)
    cmake_parse_arguments(setup "" "TARGET" "SOURCES;LIBRARIES;INCLUDES;GROUP" ${ARGN})

    if(NOT setup_TARGET)
        message(FATAL_ERROR "You must provide a target name")
    endif()

    if(NOT setup_SOURCES)
        message(FATAL_ERROR "You must provide at least one source file")
    endif()

    add_executable(${setup_TARGET} ${setup_SOURCES} ${setup_INCLUDES})

    set_target_properties(${setup_TARGET} PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            INSTALL_RPATH_USE_LINK_PATH TRUE
            )

    target_compile_options(${setup_TARGET} PRIVATE ${CXXCOMPILEOPTIONS})

    install(TARGETS ${setup_TARGET} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/tools COMPONENT tools)

    target_link_libraries(${setup_TARGET} PRIVATE
            ibeo-common::sdk
        ${setup_LIBRARIES})

    if (WIN32)
        target_compile_definitions(${setup_TARGET} PRIVATE -D_WIN32_WINNT=0x0601 -DWIN32_LEAN_AND_MEAN)

#        foreach(file ${setup_SOURCES})
#            get_filename_component(ext ${file} EXT)
#            if (ext EQUAL ".hpp")
#                list(APPEND hdr ${CMAKE_CURRENT_LIST_DIR}/${file})
#            else()
#                list(APPEND src ${CMAKE_CURRENT_LIST_DIR}/${file})
#            endif()
#        endforeach()
    endif()

#    set(hdrGroup "Header Files\\${setup_GROUP}")
#    set(srcGroup "Header Files\\${setup_GROUP}")

#    source_group(${hdrGroup} FILES ${hds})
#    source_group(${srcGroup} FILES ${src})

    if (BUILD_SHARED_LIBS)
        target_compile_definitions(${setup_TARGET} PUBLIC -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK -DBOOST_TEST_DYN_LINK)
    else()
        target_compile_definitions(${setup_TARGET} PUBLIC -DBOOST_ALL_NO_LIB)
    endif()
endfunction()

# ==============================================================================
setup(TARGET "idcCompare"
        SOURCES "src/IdcCompare.cpp"
        LIBRARIES ${Boost_LIBRARIES} ${JPEG_LIBRARIES}
        INCLUDES ${Boost_INCLUDE_DIRS} ${JPEG_INCLUDE_DIR})

# ==============================================================================
setup(TARGET "idcFixSizeOfPrevMsg"
        SOURCES "src/idcFixSizeOfPrevMsg.cpp"
        LIBRARIES ${Boost_LIBRARIES} ${JPEG_LIBRARIES}
        INCLUDES ${Boost_INCLUDE_DIRS} ${JPEG_INCLUDE_DIR})

# ==============================================================================
setup(TARGET "idcMergeTool"
        SOURCES "src/IdcMergerTool.cpp"
        LIBRARIES ${Boost_LIBRARIES} ${JPEG_LIBRARIES}
        INCLUDES ${Boost_INCLUDE_DIRS} ${JPEG_INCLUDE_DIR})

# ==============================================================================
setup(TARGET "idcRepairTool"
        SOURCES "src/IdcRepairTool.cpp"
        LIBRARIES ${Boost_LIBRARIES} ${JPEG_LIBRARIES}
        INCLUDES ${Boost_INCLUDE_DIRS} ${JPEG_INCLUDE_DIR})

# ==============================================================================
setup(TARGET "idcListTool"
        SOURCES "src/IdcListTool.cpp"
        LIBRARIES ${Boost_LIBRARIES} ${JPEG_LIBRARIES}
        INCLUDES ${Boost_INCLUDE_DIRS} ${JPEG_INCLUDE_DIR})
# ==============================================================================
