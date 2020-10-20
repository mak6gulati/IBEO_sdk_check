cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
               TARGET SystemMonitoringTest
               		
               INCLUDES SystemMonitoringTestSupport.hpp
                        ../common/TestSupport.hpp
                        
               SOURCES  SystemMonitoringTest.cpp
                        SystemMonitoringTestSupport.cpp
                        ../common/TestSupport.cpp
              )