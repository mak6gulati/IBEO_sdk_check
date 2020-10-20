cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
               TARGET MissionHandling3530Test

               INCLUDES MissionHandlingStatus3530TestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES  MissionHandling3530Test.cpp
                        MissionHandlingStatus3530TestSupport.cpp
                        ../common/TestSupport.cpp
              )