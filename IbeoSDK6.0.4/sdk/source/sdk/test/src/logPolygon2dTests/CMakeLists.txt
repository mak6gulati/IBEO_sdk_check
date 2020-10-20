cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET LogPolygonList2dTests

    INCLUDES
        LogPolygonList2dTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        LogPolygonList2dTests.cpp
        LogPolygonList2dTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
    TARGET LogPolygonList2dFloat6817Tests

    INCLUDES
        LogPolygonList2dTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        LogPolygonList2dFloat6817Tests.cpp
        LogPolygonList2dTestSupport.cpp
        ../common/TestSupport.cpp
)