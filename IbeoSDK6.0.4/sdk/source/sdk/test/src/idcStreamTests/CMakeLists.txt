cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET IdcIStreamTests

    INCLUDES IdcIStreamTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES IdcIStreamTests.cpp
            IdcIStreamTestSupport.cpp
            ../common/TestSupport.cpp
    )

add_boost_test(
    TARGET IdcOStreamTests

    INCLUDES IdcOStreamTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES IdcOStreamTests.cpp
            IdcOStreamTestSupport.cpp
            ../common/TestSupport.cpp
    )