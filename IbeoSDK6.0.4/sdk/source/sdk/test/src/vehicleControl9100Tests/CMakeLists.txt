cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
               TARGET VehicleControl9100Test
               		
               INCLUDES VehicleControl9100TestSupport.hpp
                        ../common/TestSupport.hpp
                        
               SOURCES  VehicleControl9100Test.cpp
                        VehicleControl9100TestSupport.cpp
                        ../common/TestSupport.cpp
              )