cmake_minimum_required(VERSION 3.5 FATAL_ERROR)


add_boost_test(
                TARGET   Position84Wgs2604Tests

                INCLUDES PositionWgs84_2604TestSupport.hpp
                         ../common/TestSupport.hpp

                SOURCES  PositionWgs84_2604Tests.cpp
                         PositionWgs84_2604TestSupport.cpp
                         ../common/TestSupport.cpp
              )

add_boost_test(
                TARGET   Position84WgsSequence3510Tests

                INCLUDES Position84WgsSequence3510TestSupport.hpp
                         ../common/TestSupport.hpp

                SOURCES  Position84WgsSequence3510Tests.cpp
                         Position84WgsSequence3510TestSupport.cpp
                         ../common/TestSupport.cpp
              )

add_boost_test(
                TARGET   Position84WgsSequenceTests

                INCLUDES PositionWgs84SequenceTestSupport.hpp
                         ../common/TestSupport.hpp

                SOURCES  PositionWgs84SequenceTests.cpp
                         PositionWgs84SequenceTestSupport.cpp
                         ../common/TestSupport.cpp
              )