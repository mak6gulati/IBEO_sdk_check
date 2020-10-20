if (DEFINED IBEOLOGGING_DEPENDENCIES_GUARD)
	return()
endif()

include(CMakeFindDependencyMacro)

set(Boost_USE_STATIC_LIBS OFF)

find_dependency(tinyxml2 REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(IBEOLOGGING_DEPENDENCIES_GUARD 1)