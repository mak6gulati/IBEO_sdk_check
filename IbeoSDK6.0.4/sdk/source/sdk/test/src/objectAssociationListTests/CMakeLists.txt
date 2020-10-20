cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET
        ObjectAssociationListTest

    INCLUDES
        ObjectAssociationListTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        ObjectAssociationListTest.cpp
        ObjectAssociationListTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
    TARGET
        ObjectAssociationList4001Test

    INCLUDES
        ObjectAssociationList4001TestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        ObjectAssociationList4001Test.cpp
        ObjectAssociationList4001TestSupport.cpp
        ../common/TestSupport.cpp
)