cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
        TARGET IdSequenceTest

        INCLUDES IdSequenceTestSupport.hpp
                 ../common/TestSupport.hpp

        SOURCES  IdSequenceTest.cpp
                 IdSequenceTestSupport.cpp
                 ../common/TestSupport.cpp
)

add_boost_test(
        TARGET IdSequence3500Test

        INCLUDES IdSequence3500TestSupport.hpp
                 ../common/TestSupport.hpp

        SOURCES  IdSequence3500Test.cpp
                 IdSequence3500TestSupport.cpp
                 ../common/TestSupport.cpp
)
