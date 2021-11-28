# Set cpp and cmake versions
set(CMAKE_CXX_STANDARD 17)
project(ada-portfolio2 CXX)
cmake_minimum_required(VERSION 3.10.2)
message(STATUS "Configuring C++17 project ${PROJECT_NAME} ${CMAKE_BUILD_TYPE} build .. ")

# Check if ccache is installed
find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
	message(STATUS "Found ccache, using it as the CXX laucher .. ")
	set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif(CCACHE_FOUND)

# Project files
set(PROJECT_MAIN
	${CMAKE_SOURCE_DIR}/src/main.cpp
)
set(PROJECT_SOURCES
	${CMAKE_SOURCE_DIR}/src/chess-search.hpp
)

# Includes
include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/src
)

# Output executables
add_executable(ada-portfolio2 ${PROJECT_MAIN} ${PROJECT_SOURCES})

# Test things
if(BUILD_TESTS)
# Test files
	set(TEST_MAIN
		${CMAKE_SOURCE_DIR}/test/test-main.cpp
	)
	set(CATCH2_INCLUDE
		${CMAKE_SOURCE_DIR}/include/catch.hpp
	)
# Test executable
	add_executable(test-ada-portfolio2 ${TEST_MAIN} ${PROJECT_SOURCES} ${CATCH2_INCLUDE})

#	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#		set_target_properties(test-ada-portfolio2 PROPERTIES DEBUG 1)
#	endif()
endif()