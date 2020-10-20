cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

configure_file(${CMAKE_CURRENT_LIST_DIR}/carriageway6970_example.idc ${CMAKE_CURRENT_BINARY_DIR}/carriageway6970_example.idc COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/carriageway6972_example.idc ${CMAKE_CURRENT_BINARY_DIR}/carriageway6972_example.idc COPYONLY)

add_boost_test(
    TARGET CarriageWayList6970Tests

    INCLUDES CarriageWayListTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES CarriageWayList6970Tests.cpp
            CarriageWayListTestSupport.cpp
            ../common/TestSupport.cpp
    )

add_boost_test(
    TARGET CarriageWayList6972Tests

    INCLUDES CarriageWayListTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES CarriageWayList6972Tests.cpp
            CarriageWayListTestSupport.cpp
            ../common/TestSupport.cpp
    )

add_boost_test(
    TARGET CarriageWayListTests

    INCLUDES CarriageWayListTestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES CarriageWayListTests.cpp
            CarriageWayListTestSupport.cpp
            ../common/TestSupport.cpp
)
