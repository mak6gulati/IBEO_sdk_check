cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET
        FormatTest
    SOURCES
        FormatTest.cpp
)

add_boost_test(
    TARGET
        FormatModifierTest
    SOURCES
        FormatModifierTest.cpp
)
