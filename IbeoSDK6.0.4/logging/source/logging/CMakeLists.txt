# ==============================================================================
cmake_minimum_required (VERSION 3.5 FATAL_ERROR)

message (STATUS "*** Entering CMakeLists.txt file of ibeo-common-logging::logging library. ***")

# ==============================================================================

set (TARGET_NAME logging)


# ==============================================================================
# includes
# ==============================================================================

include(GenerateExportHeader)


# ==============================================================================
# variables
# ==============================================================================

set (
    LIB_HEADER_FILES
        include/ibeo/common/logging/backends/AsyncLoggerBackend.hpp
        include/ibeo/common/logging/backends/ConsoleLoggerBackend.hpp
        include/ibeo/common/logging/backends/FileLoggerBackend.hpp
        include/ibeo/common/logging/backends/LoggerBackend.hpp
        include/ibeo/common/logging/backends/LoggerBackendManager.hpp
        include/ibeo/common/logging/backends/LogMessageQueue.hpp
        include/ibeo/common/logging/formatters/DateFormatter.hpp
        include/ibeo/common/logging/formatters/FilePathFormatter.hpp
        include/ibeo/common/logging/formatters/FormatModifier.hpp
        include/ibeo/common/logging/formatters/Formatter.hpp
        include/ibeo/common/logging/formatters/FormatterWithPrecision.hpp
        include/ibeo/common/logging/formatters/FunctionNameFormatter.hpp
        include/ibeo/common/logging/formatters/LineNumberFormatter.hpp
        include/ibeo/common/logging/formatters/LoggerIdFormatter.hpp
        include/ibeo/common/logging/formatters/LogLevelFormatter.hpp
        include/ibeo/common/logging/formatters/MessageFormatter.hpp
        include/ibeo/common/logging/formatters/PlainTextFormatter.hpp
        include/ibeo/common/logging/formatters/SequenceNumberFormatter.hpp
        include/ibeo/common/logging/formatters/ThreadIdFormatter.hpp
        include/ibeo/common/logging/Configuration.hpp
        include/ibeo/common/logging/Format.hpp
        include/ibeo/common/logging/Logger.hpp
        include/ibeo/common/logging/LoggerFactory.hpp
        include/ibeo/common/logging/LogLevel.hpp
        include/ibeo/common/logging/LogManager.hpp
        include/ibeo/common/logging/Message.hpp
        include/ibeo/common/logging/MessageStreamHelper.hpp
        include/ibeo/common/logging/logging.hpp
)

set (
    LIB_SOURCE_FILES
        src/backends/AsyncLoggerBackend.cpp
        src/backends/ConsoleLoggerBackend.cpp
        src/backends/FileLoggerBackend.cpp
        src/backends/LoggerBackend.cpp
        src/backends/LoggerBackendManager.cpp
        src/backends/LogMessageQueue.cpp
        src/formatters/DateFormatter.cpp
        src/formatters/FilePathFormatter.cpp
        src/formatters/FormatModifier.cpp
        src/formatters/FormatterWithPrecision.cpp
        src/formatters/FunctionNameFormatter.cpp
        src/formatters/LineNumberFormatter.cpp
        src/formatters/LoggerIdFormatter.cpp
        src/formatters/LogLevelFormatter.cpp
        src/formatters/MessageFormatter.cpp
        src/formatters/PlainTextFormatter.cpp
        src/formatters/SequenceNumberFormatter.cpp
        src/formatters/ThreadIdFormatter.cpp
        src/Configuration.cpp
        src/Format.cpp
        src/Logger.cpp
        src/LoggerFactory.cpp
        src/LogManager.cpp
        src/Message.cpp
)


# ==============================================================================
# targets
# ==============================================================================

message (STATUS "*** BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}. ***")
if (BUILD_SHARED_LIBS)
    add_library (
            ${TARGET_NAME}
            SHARED
                ${LIB_HEADER_FILES}
                ${LIB_SOURCE_FILES}
    )
else ()
    add_library (
            ${TARGET_NAME}
            STATIC
                ${LIB_HEADER_FILES}
                ${LIB_SOURCE_FILES}
    )
endif ()
add_library(${EXPORT_NAMESPACE}${TARGET_NAME} ALIAS ${TARGET_NAME})


# ==============================================================================
# target properties, defintions, options, includes and libraries
# ==============================================================================

set (LOGGING_EXPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/ibeo/common/logging/LoggingExport.hpp)
generate_export_header(
        ${TARGET_NAME}
        BASE_NAME logging
        EXPORT_FILE_NAME ${LOGGING_EXPORT_FILE}
)

if (BUILD_SHARED_LIBS)

else()
    set_target_properties(
            ${TARGET_NAME}
            PROPERTIES
                COMPILE_FLAGS -DLOGGING_STATIC_DEFINE
    )
endif ()

set(OUTPUTPREFIX "")

if (WIN32)
    # this is very important for buildings dll libraries on windows
    target_compile_definitions(${TARGET_NAME} PUBLIC -D_WIN32_WINNT=0x0601 -DWIN32_LEAN_AND_MEAN)

    if (BUILD_SHARED_LIBS)
        target_compile_definitions(${TARGET_NAME} PUBLIC -DIBEO_COMMON_LOGGING_LIBDLL_SHARED)
        target_compile_definitions(${TARGET_NAME} PRIVATE -DIBEO_COMMON_LOGGING_LIBDLL_EXPORTS)
    else ()
        target_compile_definitions(${TARGET_NAME} PRIVATE -DIBEO_COMMON_LOGGING_LIBDLL_STATIC)
        set(OUTPUTPREFIX lib)
    endif ()
endif ()


set_target_properties(
        ${TARGET_NAME}
        PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            WINDOWS_EXPORT_ALL_SYMBOLS ON
            OUTPUT_NAME ${OUTPUTPREFIX}ibeo-common-logging
            DEBUG_POSTFIX _d
)

target_include_directories(
        ${TARGET_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
)

target_link_libraries (
        ${TARGET_NAME}
        PUBLIC
            tinyxml2
            Threads::Threads
)


# ==============================================================================
# install
# ==============================================================================

install (
        TARGETS ${TARGET_NAME}
        EXPORT ibeo-common-loggingTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ${TARGET_NAME}
)

install (
        DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT headers
)

install (
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT headers
)


# ==============================================================================
# Unittests
# ==============================================================================

enable_testing()

add_subdirectory(test)


# ==============================================================================

message (STATUS "*** Leaving CMakeLists.txt file of ibeo-common-logging::logging library. ***")
