cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET CanMessageTest

    INCLUDES CanMessageTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  CanMessageTests.cpp
             CanMessageTestSupport.cpp
             ../common/TestSupport.cpp
)

add_boost_test(
    TARGET CanMessage1002Tests

    INCLUDES CanMessageTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  CanMessage1002Tests.cpp
             CanMessage1002TestSupport.cpp
             ../common/TestSupport.cpp
)