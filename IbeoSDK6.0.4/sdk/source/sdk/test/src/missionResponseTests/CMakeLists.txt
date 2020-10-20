cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
        TARGET
            MissionResponse3540Tests
        HEADERS
               ../common/TestSupport.hpp
                MissionResponse3540TestSupport.hpp
        SOURCES
               ../common/TestSupport.cpp
                MissionResponse3540TestSupport.cpp
                MissionResponse3540Tests.cpp
        )