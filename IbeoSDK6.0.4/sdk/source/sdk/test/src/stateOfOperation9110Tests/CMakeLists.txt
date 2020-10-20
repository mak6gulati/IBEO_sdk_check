cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
               TARGET StateOfOperation9110Test
               		
               INCLUDES StateOfOperation9110TestSupport.hpp
                       ../common/TestSupport.hpp
                        
               SOURCES  StateOfOperation9110Test.cpp
                        StateOfOperation9110TestSupport.cpp
                       ../common/TestSupport.cpp
              )