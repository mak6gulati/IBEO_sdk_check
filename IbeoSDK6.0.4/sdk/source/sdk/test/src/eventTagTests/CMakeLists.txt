cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET EventTag7000Tests

    INCLUDES EventTag7000TestSupport.hpp
             ../wgs84Tests/PositionWgs84_2604TestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  EventTag7000Tests.cpp
             EventTag7000TestSupport.cpp
             ../wgs84Tests/PositionWgs84_2604TestSupport.cpp
             ../common/TestSupport.cpp
               )