cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# General container tests

add_boost_test(
        TARGET ContentSeparatorTest

        INCLUDES ContentSeparatorTestSupport.hpp
        ContentSeparator7100TestSupport.hpp
        ../common/TestSupport.hpp

        SOURCES ContentSeparatorTests.cpp
        ContentSeparatorTestSupport.cpp
        ContentSeparator7100TestSupport.cpp
        ../common/TestSupport.cpp
)

# ContentSeparator Type 7100 Tests

add_boost_test(
               TARGET ContentSeparator7100Test

               INCLUDES ContentSeparator7100TestSupport.hpp
                        ContentSeparatorTestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES ContentSeparator7100Test.cpp
                       ContentSeparator7100TestSupport.cpp
                       ContentSeparatorTestSupport.cpp
                       ../common/TestSupport.cpp
              )