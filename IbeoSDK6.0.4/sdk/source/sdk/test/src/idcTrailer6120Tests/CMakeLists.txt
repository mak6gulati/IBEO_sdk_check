cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET IdcTrailer6120Tests

    INCLUDES IdcTrailer6120TestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES IdcTrailer6120Tests.cpp
            IdcTrailer6120TestSupport.cpp
            ../common/TestSupport.cpp
    )