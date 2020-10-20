cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
               TARGET TimeRecord9000Test
               		
               INCLUDES TimeRecord9000TestSupport.hpp
                        ../common/TestSupport.hpp
                        
               SOURCES  TimeRecord9000Tests.cpp
                        TimeRecord9000TestSupport.cpp
                        ../common/TestSupport.cpp
              )