cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET LogMessage64x0Tests

    INCLUDES LogMessage64x0TestSupport.hpp
            ../common/TestSupport.hpp

    SOURCES LogMessage64x0Tests.cpp
            LogMessage64x0TestSupport.cpp
           ../common/TestSupport.cpp
    )
