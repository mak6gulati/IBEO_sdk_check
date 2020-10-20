cmake_minimum_required(VERSION 3.5 FATAL_ERROR)


add_boost_test(
    TARGET
        Object2271Test

    INCLUDES
        ObjectList2271TestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        Object2271Test.cpp
        ObjectList2271TestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
    TARGET
        ObjectList2221Test

    INCLUDES
        ObjectListTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        ObjectList2221Test.cpp
        ObjectListTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
    TARGET
        ObjectList2271Test

    INCLUDES
        ObjectList2271TestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        ObjectList2271Test.cpp
        ObjectList2271TestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
    TARGET
        ObjectListTest

    INCLUDES
        ObjectListTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        ObjectListTest.cpp
        ObjectListTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
        TARGET
        ObjectList2280Test

        INCLUDES
        ObjectListTestSupport.hpp
        ../common/TestSupport.hpp

        SOURCES
        ObjectList2280Test.cpp
        ObjectListTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
        TARGET
        ObjectList2281Test

        INCLUDES
        ObjectListTestSupport.hpp
        ../common/TestSupport.hpp

        SOURCES
        ObjectList2281Test.cpp
        ObjectListTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
        TARGET
        ObjectList2290Test

        INCLUDES
        ObjectListTestSupport.hpp
        ../common/TestSupport.hpp

        SOURCES
        ObjectList2290Test.cpp
        ObjectListTestSupport.cpp
        ../common/TestSupport.cpp
)

add_boost_test(
        TARGET
        ObjectList2291Test

        INCLUDES
        ObjectListTestSupport.hpp
        ../common/TestSupport.hpp

        SOURCES
        ObjectList2291Test.cpp
        ObjectListTestSupport.cpp
        ../common/TestSupport.cpp
)
