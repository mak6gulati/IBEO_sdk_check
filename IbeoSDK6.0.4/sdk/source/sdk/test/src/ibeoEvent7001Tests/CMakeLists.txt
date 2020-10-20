cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
               TARGET IbeoEvent7001Test		
               
               INCLUDES IbeoEvent7001TestSupport.hpp
                        ../common/TestSupport.hpp
                        
               SOURCES  IbeoEvent7001Test.cpp
                        IbeoEvent7001TestSupport.cpp
                        ../common/TestSupport.cpp
              )