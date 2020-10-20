cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET FrameEndSeparator1100Tests

    INCLUDES FrameEndSeparator1100TestSupport.hpp
            ../common/TestSupport.hpp

    SOURCES FrameEndSeparator1100Tests.cpp
            FrameEndSeparator1100TestSupport.cpp
           ../common/TestSupport.cpp
    )