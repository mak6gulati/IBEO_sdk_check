cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
               TARGET vehicleState2805Test

               INCLUDES VehicleStateTestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES  VehicleState2805Test.cpp
                        VehicleStateTestSupport.cpp
                        ../common/TestSupport.cpp
              )

# ==============================================================================

add_boost_test(
               TARGET vehicleState2806Test

               INCLUDES VehicleStateTestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES  VehicleState2806Test.cpp
                        VehicleStateTestSupport.cpp
                        ../common/TestSupport.cpp
              )

# ==============================================================================

add_boost_test(
               TARGET vehicleState2807Test

               INCLUDES VehicleStateTestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES  VehicleState2807Test.cpp
                        VehicleStateTestSupport.cpp
                        ../common/TestSupport.cpp
              )

# ==============================================================================

add_boost_test(
               TARGET vehicleState2808Test

               INCLUDES VehicleStateTestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES  VehicleState2808Test.cpp
                        VehicleStateTestSupport.cpp
                        ../common/TestSupport.cpp
              )

# ==============================================================================

add_boost_test(
               TARGET vehicleStateTest

               INCLUDES VehicleStateTestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES  VehicleStateTest.cpp
                        VehicleStateTestSupport.cpp
                        ../common/TestSupport.cpp
              )
