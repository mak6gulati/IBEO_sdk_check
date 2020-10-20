cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
   TARGET
        OGpsImuMessage

   INCLUDES
        OGpsImuMessageTestSupport.hpp
        ../common/TestSupport.hpp

   SOURCES
        OGpsImuMessageTest.cpp
       OGpsImuMessageTestSupport.cpp
       ../common/TestSupport.cpp
)

add_boost_test(
        TARGET
        OGpsImuMessage2610

        INCLUDES
        OGpsImuMessageTestSupport.hpp
        ../common/TestSupport.hpp

        SOURCES
        OGpsImuMessage2610Test.cpp
        OGpsImuMessageTestSupport.cpp
        ../common/TestSupport.cpp
)