cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ==============================================================================

#General Measurement(List) data container tests
add_boost_test(
               TARGET MeasurementListTest

               INCLUDES
                        MeasurementListTestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES
                        MeasurementListTest.cpp
                        MeasurementListTestSupport.cpp
                        ../common/TestSupport.cpp
              )

# ==============================================================================

#MeasurementList2815 Importer/Exporter-tests
add_boost_test(
               TARGET
                        MeasurementList2815Test

               INCLUDES
                        MeasurementListTestSupport.hpp
                        ../common/TestSupport.hpp

               SOURCES
                        MeasurementList2821Test.cpp
                        MeasurementListTestSupport.cpp
                        ../common/TestSupport.cpp
              )