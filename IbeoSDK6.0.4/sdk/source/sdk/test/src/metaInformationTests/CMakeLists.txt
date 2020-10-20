cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET MetaInformationTest

    INCLUDES
        MetaInformationTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        MetaInformationTest.cpp
        MetaInformationTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
    TARGET MetaInformation7110Test

    INCLUDES
        MetaInformation7110TestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        MetaInformation7110Test.cpp
        MetaInformation7110TestSupport.cpp
        ../common/TestSupport.cpp
)