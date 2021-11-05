/**
 * @file test-main.cpp
 *
 * @brief Test cases for the portfolio search algorithm.
 *
 * Building tests require the Catch2 'catch.hpp', see
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

#define CATCH_CONFIG_MAIN

#include <vector>

#include "catch.hpp"
#include "collinear-search.hpp"


TEST_CASE("Point2d <= operator - false", "[point2d]") {
	point2d p1(1,1);
	point2d p2(1,2);
	point2d p3(2,1);

	REQUIRE((p2 <= p1) == false);
	REQUIRE((p3 <= p2) == false);
	REQUIRE((p3 <= p1) == false);
}

TEST_CASE("Point2d <= operator - true", "[point2d]") {
	point2d p1(1,1);
	point2d p2(1,2);
	point2d p3(2,1);
	point2d p4(1,1);

	REQUIRE((p1 <= p2) == true);
	REQUIRE((p2 <= p3) == true);
	REQUIRE((p1 <= p3) == true);
	REQUIRE((p1 <= p4) == true);
}

TEST_CASE("Point2d >= operator - false", "[point2d]") {
	point2d p1(1,1);
	point2d p2(1,2);
	point2d p3(2,1);

	REQUIRE((p1 >= p2) == false);
	REQUIRE((p2 >= p3) == false);
	REQUIRE((p1 >= p3) == false);
}

TEST_CASE("Point2d >= operator - true", "[point2d]") {
	point2d p1(1,1);
	point2d p2(1,2);
	point2d p3(2,1);
	point2d p4(1,1);

	REQUIRE((p2 >= p1) == true);
	REQUIRE((p3 >= p2) == true);
	REQUIRE((p3 >= p1) == true);
	REQUIRE((p4 >= p1) == true);
}

TEST_CASE("Point2d == operator - false", "[point2d]") {
	point2d p1(1,2);
	point2d p2(2,2);
	point2d p3(2,1);

	REQUIRE((p1 == p2) == false);
	REQUIRE((p2 == p1) == false);
	REQUIRE((p1 == p3) == false);
	REQUIRE((p3 == p1) == false);
}

TEST_CASE("Point2d == operator - true", "[point2d]") {
	point2d p1(1,2);
	point2d p2(1,2);

	REQUIRE((p1 == p1) == true);
	REQUIRE((p1 == p2) == true);
}

TEST_CASE("Point2d != operator - false", "[point2d]") {
	point2d p1(1,2);
	point2d p2(1,2);

	REQUIRE((p1 != p1) == false);
	REQUIRE((p1 != p2) == false);
}

TEST_CASE("Point2d != operator - true", "[point2d]") {
	point2d p1(1,2);
	point2d p2(2,2);
	point2d p3(2,1);

	REQUIRE((p1 != p2) == true);
	REQUIRE((p2 != p1) == true);
	REQUIRE((p1 != p3) == true);
	REQUIRE((p3 != p1) == true);
}

TEST_CASE("Point group comparison - false", "[compare_point_group]") {
	std::vector<point2d> input1 {{1,1},{2,2},{3,3},{4,4}};
	std::vector<point2d> input2 {{1,1},{2,2},{3,3},{4,3}};
	std::vector<point2d> input3 {{2,1},{2,2},{3,3},{4,4}};
	std::vector<point2d> input4 {{4,4},{1,2},{2,2},{3,3}};
	std::vector<point2d> input5 {{1,6},{2,2},{3,5},{4,4}};
	std::vector<point2d> input6 {{1,6},{3,5},{2,2},{4,4}};

	REQUIRE(compare_point_group(input1,  input2) == false);
	REQUIRE(compare_point_group(input1,  input3) == false);
	REQUIRE(compare_point_group(input1,  input4) == false);
	REQUIRE(compare_point_group(input1,  input5) == false);
	REQUIRE(compare_point_group(input1,  input6) == false);
}

TEST_CASE("Point group comparison - true", "[compare_point_group]") {
	std::vector<point2d> input1 {{1,1},{2,2},{3,3},{4,4}};
	std::vector<point2d> input2 {{4,4},{3,3},{2,2},{1,1}};
	std::vector<point2d> input3 {{3,3},{1,1},{2,2},{4,4}};
	std::vector<point2d> input4 {{4,4},{2,2},{3,3},{1,1}};

	REQUIRE(compare_point_group(input1,  input1) == true);
	REQUIRE(compare_point_group(input1,  input2) == true);
	REQUIRE(compare_point_group(input1,  input3) == true);
	REQUIRE(compare_point_group(input1,  input4) == true);
}

TEST_CASE("Point groups comparison - false", "[compare_point_groups]") {
	std::vector<std::vector<point2d>> input1 {
		{{1,1},{2,2},{3,3},{4,4}},	// Three groups, one diagonal,
		{{1,1},{2,1},{3,1},{4,1}},	// one vertical, one horizontal
		{{1,1},{1,2},{1,3},{1,4}}};
	std::vector<std::vector<point2d>> input2 {
		{{1,3},{2,2},{3,3},{4,4}},
		{{1,1},{2,1},{3,1},{4,1}},
		{{1,1},{1,2},{1,3},{1,4}}};
	std::vector<std::vector<point2d>> input3 {
		{{1,1},{2,2},{3,3},{4,4}},
		{{1,1},{2,1},{3,1},{4,1}},
		{{1,1},{1,1},{1,3},{1,4}}};
	std::vector<std::vector<point2d>> input4 {
		{{1,1},{2,2},{3,3},{4,4}},
		{{2,2},{2,1},{3,1},{4,1}},
		{{1,1},{1,2},{1,3},{1,4}}};
	std::vector<std::vector<point2d>> input5 {};
	std::vector<std::vector<point2d>> input6 {
		{{1,1},{2,2},{3,3},{4,4}},
		{{2,2},{2,1},{3,1},{4,1}}};
	std::vector<std::vector<point2d>> input7 {
		{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6}},
		{{1,1},{2,2},{3,3}},
		{{2,2},{2,1},{3,1},{4,1}}};

	REQUIRE(compare_point_groups(input1, input2) == false);
	REQUIRE(compare_point_groups(input1, input3) == false);
	REQUIRE(compare_point_groups(input1, input4) == false);
	REQUIRE(compare_point_groups(input1, input5) == false);
	REQUIRE(compare_point_groups(input1, input6) == false);
	REQUIRE(compare_point_groups(input1, input7) == false);
}

TEST_CASE("Point groups comparison - true", "[compare_point_groups]") {
	std::vector<std::vector<point2d>> input1 {
		{{1,1},{2,2},{3,3},{4,4}},	// Three groups, one diagonal,
		{{1,1},{2,1},{3,1},{4,1}},	// one vertical, one horizontal
		{{1,1},{1,2},{1,3},{1,4}}};
	std::vector<std::vector<point2d>> input2 {
		{{1,1},{2,2},{3,3},{4,4}},	// Idential vector
		{{1,1},{2,1},{3,1},{4,1}},
		{{1,1},{1,2},{1,3},{1,4}}};
	std::vector<std::vector<point2d>> input3 {
		{{1,1},{2,1},{3,1},{4,1}},	// Rows shifted
		{{1,1},{1,2},{1,3},{1,4}},
		{{1,1},{2,2},{3,3},{4,4}}};
	std::vector<std::vector<point2d>> input4 {
		{{2,2},{4,4},{1,1},{3,3}},	// Row contents shifted
		{{1,1},{4,1},{3,1},{2,1}},
		{{1,3},{1,4},{1,1},{1,2}}};
	std::vector<std::vector<point2d>> input5 {
		{{1,1},{4,1},{3,1},{2,1}},  // Rows shifted and rows content shifted
		{{1,3},{1,4},{1,1},{1,2}},
		{{2,2},{4,4},{1,1},{3,3}}};

	REQUIRE(compare_point_groups(input1, input1) == true);
	REQUIRE(compare_point_groups(input1, input2) == true);
	REQUIRE(compare_point_groups(input1, input3) == true);
	REQUIRE(compare_point_groups(input1, input4) == true);
	REQUIRE(compare_point_groups(input1, input5) == true);
}

TEST_CASE("Group of 4 collinear points", "[collinear_search]") {
	// Input values
	std::vector<point2d> input {{7,1},{12,3},{14,6},{9,4},{1,6},{1,1},{2,2},{3,3},{4,4},{1,2},{2,4},{3,6},{4,7}};

	// Expected output
	std::vector<std::vector<point2d>> expected_output {{{1,1},{2,2},{3,3},{4,4}}};

	// Run the algorithm
	std::vector<std::vector<point2d>> actual_output = collinear_search(input);

	// Test
	REQUIRE(compare_point_groups(expected_output, actual_output) == true);
}

TEST_CASE("No group of 4 collinear points", "[collinear_search]") {
	// Input values
	std::vector<point2d> input {{7,1},{12,5},{14,6},{9,4},{1,6},{2,2},{3,3},{4,4},{1,2},{2,4},{3,6},{4,7}};

	// Expected output
	std::vector<std::vector<point2d>> expected_output {};

	// Run the algorithm
	std::vector<std::vector<point2d>> actual_output = collinear_search(input);

	// Test
	REQUIRE(compare_point_groups(expected_output, actual_output) == true);
}

TEST_CASE("Collinear points on a vertical plane", "[collinear_search]") {
	// Input values
	std::vector<point2d> input {{7,1},{12,3},{14,6},{9,4},{1,6},{2,1},{1,4},{1,5},{4,4},{1,2},{2,5},{3,6},{4,8}};

	// Expected output
	std::vector<std::vector<point2d>> expected_output {{{1,2},{1,4},{1,5},{1,6}}};

	// Run the algorithm
	std::vector<std::vector<point2d>> actual_output = collinear_search(input);

	// Test
	REQUIRE(compare_point_groups(expected_output, actual_output) == true);
}

TEST_CASE("Multiple groups of collinear points", "[collinear_search]") {
	// Input values
	std::vector<point2d> input {{2,2},{3,3},{4,4},{7,1},{14,6},{9,4},{1,1},{1,4},{1,5},{4,4},{1,2},{2,4}};

	// Expected output
	std::vector<std::vector<point2d>> expected_output{
		{{1,1},{1,2},{1,4},{1,5}},
		{{1,1},{2,2},{3,3},{4,4}},
		{{4,4},{9,4},{1,4},{2,4}}};

	// Run the algorithm
	std::vector<std::vector<point2d>> actual_output = collinear_search(input);

	// Test
	REQUIRE(compare_point_groups(expected_output, actual_output) == true);
}
