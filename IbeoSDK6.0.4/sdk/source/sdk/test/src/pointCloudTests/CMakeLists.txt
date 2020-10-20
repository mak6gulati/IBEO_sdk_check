cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_boost_test(
    TARGET
        PointCloud7500Tests

    INCLUDES
        PointCloudTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        PointCloud7500Tests.cpp
        PointCloudTestSupport.cpp
        ../common/TestSupport.cpp
    )


add_boost_test(
    TARGET
        PointCloud7510Tests

    INCLUDES
        PointCloudTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        PointCloud7510Tests.cpp
        PointCloudTestSupport.cpp
        ../common/TestSupport.cpp
)


add_boost_test(
    TARGET
        PointCloudTests

    INCLUDES
        PointCloudTestSupport.hpp
        ../common/TestSupport.hpp

    SOURCES
        PointCloudTests.cpp
        PointCloudTestSupport.cpp
        ../common/TestSupport.cpp
    )