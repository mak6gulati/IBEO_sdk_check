cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
        TARGET   TrafficLightStateListTest

        INCLUDES TrafficLightStateListTestSupport.hpp
                 ../common/TestSupport.hpp

        SOURCES  TrafficLightStateListTests.cpp
                 TrafficLightStateListTestSupport.cpp
                 ../common/TestSupport.cpp
              )

add_boost_test(
        TARGET   TrafficLightStateList3600Test

        INCLUDES TrafficLightStateList3600TestSupport.hpp
                 ../common/TestSupport.hpp

        SOURCES  TrafficLightStateList3600Tests.cpp
                 TrafficLightStateList3600TestSupport.cpp
                 ../common/TestSupport.cpp
              )
