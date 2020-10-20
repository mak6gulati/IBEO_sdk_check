cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

#-------------------
# Image2403Tests

add_boost_test(TARGET Image2403Tests
        INCLUDES
                Image2403TestSupport.hpp
                ../common/TestSupport.hpp

        SOURCES
                Image2403Tests.cpp
                Image2403TestSupport.cpp
                ../common/TestSupport.cpp
              )

#-------------------
# ImageTests (GeneralDataContainer)

add_boost_test(TARGET ImageTests
        INCLUDES
                ImageTestSupport.hpp
                Image2403TestSupport.hpp
                ../common/TestSupport.hpp

        SOURCES
                ImageTests.cpp
                ImageTestSupport.cpp
                Image2403TestSupport.cpp
               ../common/TestSupport.cpp
              )
