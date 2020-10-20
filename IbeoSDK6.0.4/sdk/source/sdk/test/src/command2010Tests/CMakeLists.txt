cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
               TARGET Command2010Test

               INCLUDES Command2010TestSupport.hpp
                        SpecialCommand2010TestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES Command2010TestSupport.cpp
                       SpecialCommand2010TestSupport.cpp
                       Command2010Tests.cpp
                       ../common/TestSupport.cpp
              )