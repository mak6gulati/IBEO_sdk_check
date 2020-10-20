cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ==============================================================================

add_boost_test(
    TARGET TimeRelationsListTests

    INCLUDES TimeRelationsListTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  TimeRelationsListTest.cpp
             TimeRelationsListTestSupport.cpp
             ../common/TestSupport.cpp
)

# ==============================================================================

add_boost_test(
    TARGET TimeRelationsList9010Tests

    INCLUDES TimeRelationsListTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  TimeRelationsList9010Test.cpp
             TimeRelationsListTestSupport.cpp
             ../common/TestSupport.cpp
)

# ==============================================================================

# ==============================================================================

add_boost_test(
    TARGET TimeRelationsList9011Tests

    INCLUDES TimeRelationsListTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  TimeRelationsList9011Test.cpp
             TimeRelationsListTestSupport.cpp
             ../common/TestSupport.cpp
)

# ==============================================================================