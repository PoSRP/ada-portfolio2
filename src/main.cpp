/**
 * @file main.cpp
 *
 * @brief Main for collinear-search portfolio assignment
 *
 * If wanted, I've included a CMakeLists, build script, and project folder structure below the code.
 * REMEMBER to change the build path if you do use it. It's for Linux.
 *
 * To build unit tests you have to download the Catch2 header, which is available at
 * 		https://github.com/catchorg/Catch2/releases/download/v2.13.7/catch.hpp
 * Tested with v1.12.1 and 1.13.7
 *
 * @ingroup CollinearSearch
 *
 * @author Søren Riisom Pedersen
 * Contact: soepe13@student.sdu.dk
 *
 * Created on: 12-10-2021
 */

/**
 * ADA Portfolio
 *
 * Write a program that reads a list of points in a plane and outputs any group of four or more colinear points
 * (i.e. points on the same line). The algorithm should make use of sorting and have a time complexity of
 * O(n^2 log N). Below is listed several unit-tests, that your function must be able to pass. The ordering of the
 * output is irrelevant.
 * Deadline is October 28th at 23:59, and you may only hand in program files (i.e. .h, .cpp or .java). Comments
 * must be embedded into the program files. The exercise must be completed and handed in individually.
 *
 * TEST 1 - Group of 4 colinear points
 * Input: {{7,1},{12,3},{14,6},{9,4},{1,6},{1,1},{2,2},{3,3},{4,4},{1,2},{2,4},{3,6},{4,7}}
 * Output: {{{1,1},{2,2},{3,3},{4,4}}}
 * TEST 2 - No group of 4 colinear points
 * Input: {{7,1},{12,5},{14,6},{9,4},{1,6},{2,2},{3,3},{4,4},{1,2},{2,4},{3,6},{4,7}}
 * Output: {}
 * TEST 3 - Colinear points on a vertical line
 * Input: {{7,1},{12,3},{14,6},{9,4},{1,6},{2,1},{1,4},{1,5},{4,4},{1,2},{2,5},{3,6},{4,8}}
 * Output: {{{1,2},{1,4},{1,5},{1,6}}}
 * TEST 4 - Multiple groups of colinear points
 * Input: {{2,2},{3,3},{4,4},{7,1},{14,6},{9,4},{1,1},{1,4},{1,5},{4,4},{1,2},{2,4}}
 * Output: {{{1,1},{1,2},{1,4},{1,5}}, {{1,1},{2,2},{3,3},{4,4}}, {{4,4},{9,4},{1,4},{2,4}}}
 */

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <inttypes.h>

#include "collinear-search.hpp"

int main(int argc, char** argv) {
	/**
	 * Retrieve input
	 * Parse string input to vector<point2d>
	 * Feed std::vector<point2d> to algorithm
	 * Parse output vector<vector<point2d>> points to string
	 * Write result to cout
	 */

	// 2*NumPairs + 1 for balanced pairs of X/Y arguments
	if (!argc % 2) {std::cout << "Error: Unbalanced X/Y pairs" << std::endl; return -1;}

	// TODO: Check for bracket balance and type
	if (false) void (0);

	// Input container
	std::vector<point2d> points {};

	// Input parsing
	if (argc > 1) {
		// Expected formatting is {{{x11,y11},{x12,y12}},{{x21,y21},{x22,y22}}}
		int i {1};
		while (i < argc) {
			// Only safe because of 'if (!argc % 2)'
			points.push_back(point2d(atoi(argv[i]), atoi(argv[i+1])));
			i += 2;
		}
	} else {std::cout << "Error: No input given" << std::endl; return -1;}

	// The algorithm
	std::vector<std::vector<point2d>> output{};
	output = collinear_search(points);

	// Parsing to {{{x11,y11},{x12,y12}},{{x21,y21},{x22,y22}}}
	std::stringstream ss;
	ss << "{";
	for (const auto& group : output) {
		ss << "{";
		for (const auto& point : group) {
			ss << point;
			if (&point != &group[group.size()-1]) ss << ",";
		}
		ss << "}";
		if (&group != &output[output.size()-1]) ss << ",";
	}
	ss << "}";

	// Output result
	std::cout << ss.str().c_str() << std::endl;

	return 0;
}

/** CMakeLists.txt
# Set cpp and cmake versions
set(CMAKE_CXX_STANDARD 17)
project(ada-portfolio CXX)
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
	${CMAKE_SOURCE_DIR}/src/collinear-search.hpp
)

# Includes
include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/src
)

# Output executables
add_executable(ada-portfolio ${PROJECT_MAIN} ${PROJECT_SOURCES})

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
	add_executable(test-ada-portfolio ${TEST_MAIN} ${PROJECT_SOURCES} ${CATCH2_INCLUDE})

#	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#		set_target_properties(test-ada-portfolio PROPERTIES DEBUG 1)
#	endif()
endif()
 */ // END OF CMakeLists.txt


/** build.sh bash script
#!/usr/bin/bash

# Change to build dir
user=$(whoami)
BUILD_DIR="/home/${user}/workspace/eclipse/ada-portfolio/build"
cd $BUILD_DIR || exit 1

# Argument parsing
while [[ $# -gt 0 ]]; do
	key="$1"
	case $key in
		-d | --debug)
			build_debug=1
			shift;;
		-c | --clear)
			clear_build_dir=1
			shift;;
		-t | --test)
			build_tests=1
			shift;;
		'')
			;;
		*)
			echo "Usage: $0 [options]"
			echo "  -c (--clear) - Clear the output directory before building"
			echo "                   Does not clear any eventual ccache entries"
			echo "  -d (--debug) - Build debug version, default is Release"
			echo "  -t (--test)  - Also build test program"
			exit;;
	esac
done

# Clear build if requested
if [ $clear_build_dir ]; then
	echo "Clearing the output directory .."
	rm -r $BUILD_DIR/* || exit 1
fi

# Choose build type
if [ $build_debug ]; then build_type="Debug"
else build_type="Release"; fi

# Build
cmake -DCMAKE_BUILD_TYPE=$build_type -DBUILD_TESTS=$build_tests .. || exit 1
make || exit 1
 */ // END OF build.sh

/** Project folder structure
.
├── build/
├── build.sh
├── CMakeLists.txt
├── include/
│   ├── catch.hpp
├── src/
│   ├── collinear-search.hpp
│   └── main.cpp
└── test/
    └── test-main.cpp
 */
