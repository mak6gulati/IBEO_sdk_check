cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET
        ObjectLabelListTest

    INCLUDES
        ObjectLabelListTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        ObjectLabelListTest.cpp
        ObjectLabelListTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
    TARGET
        ObjectLabelList6503Test

    INCLUDES
        ObjectLabelList6503TestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        ObjectLabelList6503Test.cpp
        ObjectLabelList6503TestSupport.cpp
        ../common/TestSupport.cpp
)