cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# General container tests

add_boost_test(
        TARGET GpsImuTest

        INCLUDES GpsImuTestSupport.hpp
                 GpsImu9001TestSupport.hpp
                 ../common/TestSupport.hpp

        SOURCES GpsImuTests.cpp
                GpsImuTestSupport.cpp
                GpsImu9001TestSupport.cpp
                ../common/TestSupport.cpp
)

# GpsImu Type 9001 Tests

add_boost_test(
               TARGET GpsImu9001Test
               		
               INCLUDES GpsImu9001TestSupport.hpp
                        ../common/TestSupport.hpp
                        
               SOURCES  GpsImu9001Test.cpp
                        GpsImu9001TestSupport.cpp
                        GpsImuTestSupport.cpp
                        ../common/TestSupport.cpp
              )