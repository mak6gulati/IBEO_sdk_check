cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(TARGET Destination3520Test

               HEADERS
                    ../common/TestSupport.hpp
                    Destination3520TestSupport.hpp
                    Wgs84TestSupport.hpp

               SOURCES
                    ../common/TestSupport.cpp
                    Destination3520TestSupport.cpp
                    Destination3520Tests.cpp
                    ../wgs84Tests/PositionWgs84_2604TestSupport.cpp
                )