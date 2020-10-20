cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ==============================================================================

# General container tests
add_boost_test(
    TARGET ScanTest

    INCLUDES ScanTestSupport.hpp
             Scan2202TestSupport.hpp
             Scan2209TestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  ScanTests.cpp
             Scan2202TestSupport.cpp
             Scan2205TestSupport.cpp
             Scan2209TestSupport.cpp
             ScanTestSupport.cpp
             ../common/TestSupport.cpp
)

# ==============================================================================

#Scan Type 2202 Tests
add_boost_test(
    TARGET Scan2202Test

    INCLUDES ScanTestSupport.hpp
             Scan2202TestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  Scan2202Tests.cpp
             Scan2202TestSupport.cpp
             ScanTestSupport.cpp
             ../common/TestSupport.cpp
)
# ==============================================================================

#Scan Type 2205 Tests
add_boost_test(
    TARGET Scan2205Test

    INCLUDES ScanTestSupport.hpp
             Scan2205TestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  Scan2205Tests.cpp
             Scan2205TestSupport.cpp
             ScanTestSupport.cpp
             ../common/TestSupport.cpp
)

# ==============================================================================

#Scan Type 2208 Tests
add_boost_test(
    TARGET Scan2208Test

    INCLUDES ScanTestSupport.hpp
             Scan2208TestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  Scan2208Tests.cpp
             Scan2208TestSupport.cpp
             ScanTestSupport.cpp
             ../common/TestSupport.cpp
)

# ==============================================================================

# Scan Type 2209 Tests
add_boost_test(
    TARGET Scan2209Test

    INCLUDES ScanTestSupport.hpp
             Scan2209TestSupport.hpp
             ../common/TestSupport.hpp

    SOURCES  Scan2209Tests.cpp
             Scan2209TestSupport.cpp
             ScanTestSupport.cpp
             ../common/TestSupport.cpp
)

# ==============================================================================

# Scan Type 2310 Tests
add_boost_test(
        TARGET Scan2310Test

        INCLUDES Scan2310TestSupport.hpp
        ../common/TestSupport.hpp

        SOURCES Scan2310Tests.cpp
        Scan2310TestSupport.cpp
        ../common/TestSupport.cpp
)

# ==============================================================================
