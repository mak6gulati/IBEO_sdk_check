cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# General container tests

add_boost_test(
        TARGET OdometryTest

        INCLUDES OdometryTestSupport.hpp
                 Odometry9002TestSupport.hpp
                 ../common/TestSupport.hpp

        SOURCES  OdometryTests.cpp
                 OdometryTestSupport.cpp
                 Odometry9002TestSupport.cpp
                 ../common/TestSupport.cpp
       )

# Odometry Type 9002 Tests

add_boost_test(
               TARGET Odometry9002Test
               		
               INCLUDES Odometry9002TestSupport.hpp
                        OdometryTestSupport.hpp
                        ../common/TestSupport.hpp
                        
               SOURCES  Odometry9002Test.cpp
                        Odometry9002TestSupport.cpp
                        OdometryTestSupport.cpp
                        ../common/TestSupport.cpp
              )