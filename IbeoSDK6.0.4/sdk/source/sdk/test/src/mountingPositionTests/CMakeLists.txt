cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
               TARGET MountingPositionTests
               		
               INCLUDES MountingPositionTestSupport.hpp
                        ../common/TestSupport.hpp
                        ../common/VectorTestSupport.hpp
                        
               SOURCES  MountingPositionTests.cpp
                        ../common/TestSupport.cpp
              )