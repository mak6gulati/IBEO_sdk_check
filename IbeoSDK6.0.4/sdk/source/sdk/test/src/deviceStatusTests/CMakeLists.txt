cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
        TARGET DeviceStatusTests

        INCLUDES
        DeviceStatusTestSupport.hpp
        UserDefinedStructDummy1.hpp
        UserDefinedStructDummy2.hpp
        UserDefinedStructDummy3.hpp
        UserDefinedStructDummy4.hpp
        ../common/TestSupport.hpp

        SOURCES
        DeviceStatusTests.cpp
        DeviceStatusTestSupport.cpp
        ../common/TestSupport.cpp

)

add_boost_test(
        TARGET DeviceStatus6301Tests

        INCLUDES
        DeviceStatusTestSupport.hpp
        UserDefinedStructDummy1.hpp
        UserDefinedStructDummy2.hpp
        UserDefinedStructDummy3.hpp
        UserDefinedStructDummy4.hpp
        ../common/TestSupport.hpp

        SOURCES
        DeviceStatus6301Tests.cpp
        DeviceStatusTestSupport.cpp
        ../common/TestSupport.cpp

)

add_boost_test(
    TARGET DeviceStatus6303Tests

    INCLUDES
        DeviceStatusTestSupport.hpp
        UserDefinedStructDummy1.hpp
        UserDefinedStructDummy2.hpp
        UserDefinedStructDummy3.hpp
        UserDefinedStructDummy4.hpp
        ../common/TestSupport.hpp

    SOURCES
        DeviceStatus6303Tests.cpp
        DeviceStatusTestSupport.cpp
        ../common/TestSupport.cpp

)
