/**
 * @file main.cpp
 *
 * @brief Main for chess-search portfolio assignment 2
 *
 * To build unit tests, the catch2 header is required.
 * 		https://github.com/catchorg/Catch2/releases/download/v2.13.7/catch.hpp
 * It is included in the ./include directory, but is NOT a part of my
 * assignment, as it is not my original code, just a testing framework.
 *
 * I would recommand using the included cmake for building
 *
 * @ingroup ChessSearch
 *
 * @author Søren Riisom Pedersen
 * Contact: soepe13@student.sdu.dk
 *
 * Created on: 10-11-2021
 */

/**
 * ADA Portfolio 2
 *
 * 1 Knight Problem
 *   Jakob and Jens are playing chess and they want to figure out what is
 *   the minimum number of moves it takes for a knight at a given position
 *   to reach another position.  The legal moves of a knight can be seen in
 *   figure 1. Your method should work for arbitrary sizes of chess boards.
 *   To solve this problem, you must implement your own classes, Tree and
 *   Node. You should also provide a public method that allows your
 *   instructor to test your work.
 *   Just as shown below:
 *     int minimum_steps(int board_height,
 *                       int board_width,
 *                       int knight_start_x_position,
 *                       int knight_start_y_position,
 *                       int knight_end_x_position,
 *                       int knight_end_y_position)
 *   An example could be for the knight in figure 1, then the input would be:
 *     minimum_steps(8, 8, 4, 4, 3, 2);
 *   You do not have to write your own driver.
 *   Just make sure that your codecomplies with the previously mentioned
 *   interface.
 *
 * 2 Formalia
 *   You  should  only  hand  in  ONE  file  in  the  form  of  .zip.
 *   The  name  of  the  file should be your SDU username (e.g.  jeive17).
 *   In the .zip-file, you include all the relevant source (.cpp, .h, .hpp,
 *   .java).  So only the programming languages C++and Java is acceptable and
 *   use only the standard libraries.  So your program should be able to
 *   compile using a standard compiler. The portfolio should be completed and
 *   handed in individually.
 */

#include <iostream>

#include "chess-search.hpp"

int main(int argc, char** argv) {
	// Just an example of using the knight move search
	int64_t min_steps = minimum_steps(8, 8, 4, 4, 3, 2);

	// Test 1
	int t1 = minimum_steps(8, 8, 4, 4, 4, 5);
	std::cout << "Test 1: " << (t1 == 3 ? "PASS" : "FAIL") << std::endl;

	// Test 2
	int t2 = minimum_steps(8, 8, 0, 0, 7, 7);
	std::cout << "Test 2: " << (t2 == 6 ? "PASS" : "FAIL") << std::endl;

	// Test 3
	int t3 = minimum_steps(8, 8, 0, 0, 0, 7);
	std::cout << "Test 3: " << (t3 == 5 ? "PASS" : "FAIL") << std::endl;

	// Test 4
	int t4 = minimum_steps(20, 10, 0, 4, 9, 15);
	std::cout << "Test 4: " << (t4 == 8 ? "PASS" : "FAIL") << std::endl;

	// Test 5
	int t5 = minimum_steps(100, 10, 4, 4, 9, 99);
	std::cout << "Test 5: " << (t5 == 48 ? "PASS" : "FAIL") << std::endl;

	// Test 6
	int t6 = minimum_steps(8, 8, 4, 4, 4, 4);
	std::cout << "Test 6: " << (t6 == 0 ? "PASS" : "FAIL") << std::endl;

	// Test 7
	int t7 = minimum_steps(100, 100, 50, 50, 57, 57);
	std::cout << "Test 7: " << (t7 == 6 ? "PASS" : "FAIL") << std::endl;

	return 0;
}
