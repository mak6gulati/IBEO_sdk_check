cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET FrameIndexTests

    INCLUDES
        FrameIndexTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        FrameIndexTests.cpp
        FrameIndexTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
    TARGET FrameIndex6130Tests

    INCLUDES
        FrameIndex6130TestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        FrameIndex6130Tests.cpp
        FrameIndex6130TestSupport.cpp
        ../common/TestSupport.cpp
)