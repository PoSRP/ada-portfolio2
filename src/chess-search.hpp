#ifndef CHESS_SEARCH_H_
#define CHESS_SEARCH_H_

/**
 * @file chess-search.hpp
 *
 * @brief Search algorithm for chess board
 *
 * (note: The defgroup is here because it's the only header in the project)
 * @defgroup ChessSearch AdaPortfolio2
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

#include <inttypes.h>
#include <unordered_map>
#include <vector>
#include <math.h>

struct Coordinate {
	// Parameters
	int64_t x{0}, y{0};

	// Constructors
	Coordinate () : x{0}, y{0} {}
	Coordinate (int64_t x, int64_t y) : x(x), y(y) {}
	Coordinate (const Coordinate& coordinate) : x(coordinate.x), y(coordinate.y) {}

	// Functions
	bool is_within_bounds(Coordinate bounds) {
		if (x > bounds.x || x < 0)
			return false;
		else if (y > bounds.y || y < 0)
			return false;
		else
			return true;
	}

	// Operators
	bool operator == (Coordinate& rhs) {
		return (this->x == rhs.x) && (this->y == rhs.y);
	}
	bool operator != (Coordinate& rhs) {
		return !(*this == rhs);
	}
};

struct Node {
	Node (const Node* parent, const Coordinate position) : parent(parent), position(position) {}
	const Node* parent;
	std::vector<Node*> children;
	Coordinate position;

	void populate_children(Coordinate bounds) {
		typedef struct {
			int d1 = 1;
			int d2 = 2;
		} knight_move_t;
		knight_move_t knight_move;

		Coordinate tmp_pos = position;
		tmp_pos.x += knight_move.d1;
		tmp_pos.y += knight_move.d2;
		if (tmp_pos.is_within_bounds(bounds))
			children.push_back(new Node(this, tmp_pos));

		tmp_pos = position;
		tmp_pos.x -= knight_move.d1;
		tmp_pos.y -= knight_move.d2;
		if (tmp_pos.is_within_bounds(bounds))
			children.push_back(new Node(this, tmp_pos));

		tmp_pos = position;
		tmp_pos.x += knight_move.d1;
		tmp_pos.y -= knight_move.d2;
		if (tmp_pos.is_within_bounds(bounds))
			children.push_back(new Node(this, tmp_pos));

		tmp_pos = position;
		tmp_pos.x -= knight_move.d1;
		tmp_pos.y += knight_move.d2;
		if (tmp_pos.is_within_bounds(bounds))
			children.push_back(new Node(this, tmp_pos));

		tmp_pos = position;
		tmp_pos.x += knight_move.d2;
		tmp_pos.y += knight_move.d1;
		if (tmp_pos.is_within_bounds(bounds))
			children.push_back(new Node(this, tmp_pos));

		tmp_pos = position;
		tmp_pos.x -= knight_move.d2;
		tmp_pos.y -= knight_move.d1;
		if (tmp_pos.is_within_bounds(bounds))
			children.push_back(new Node(this, tmp_pos));

		tmp_pos = position;
		tmp_pos.x += knight_move.d2;
		tmp_pos.y -= knight_move.d1;
		if (tmp_pos.is_within_bounds(bounds))
			children.push_back(new Node(this, tmp_pos));

		tmp_pos = position;
		tmp_pos.x -= knight_move.d2;
		tmp_pos.y += knight_move.d1;
		if (tmp_pos.is_within_bounds(bounds))
			children.push_back(new Node(this, tmp_pos));

		return;
	}
	Node* has_child(Coordinate& pos) {
		for (Node* child : children) {
			if (child->position == pos)
				return child;
		}
		return nullptr;
	}

};

class Tree {
public:
	~Tree() {
		// TODO: Unwind the tree
	}

	Node* root{nullptr};



private:

};

inline int minimum_steps(
		int board_height,
		int board_width,
		int knight_start_x_position,
		int knight_start_y_position,
		int knight_end_x_position,
		int knight_end_y_position) {

	Coordinate board_size{board_width, board_height};
	Coordinate start_pos{knight_start_x_position, knight_start_y_position};
	Coordinate end_pos{knight_end_x_position, knight_end_y_position};

	if (board_size.x <= 0 || board_size.y <= 0)
		return -1; // Board has to exist
	if (!start_pos.is_within_bounds(board_size))
		return -2; // Start outside of board
	if (!end_pos.is_within_bounds(board_size))
		return -3; // End outside of board

	if (start_pos == end_pos)
		return 0; // Already there

	// Populate the tree level by level until we find a match
	Coordinate tmp_move = start_pos;
	Tree tree;
	tree.root = new Node{nullptr, start_pos};
	Node* node = tree.root;

	// Seed first level
	node->populate_children(board_size);
	int level{1};

	// Storage for working pointers
	std::vector<Node*> ptr_storage = node->children;

	const int max_depth = 1000; // Just to avoid infinite loops if bugged
	while (level < max_depth) {
		// Check the currently stored nodes
		for (Node* n : ptr_storage) {
			// If match, return level
			if (n->position == end_pos)
				return level;
		}

		// Populate children for the nodes we just checked
		for (Node* n : ptr_storage) {
			n->populate_children(board_size);
		}

		// Replace pointers in storage vector with new children
		// Don't allow multiples of same position
		// The check using a vector is quite time consuming, but ends up being great for high levels
		std::vector<Node*> tmp = std::move(ptr_storage);
		for (Node* n : tmp) {
			for (Node* child : n->children) {
				bool add{true};
				for (Node* existing : ptr_storage) {
					if (existing->position == child->position)
						add = false;
				}
				if (add)
					ptr_storage.push_back(child);
			}
		}

		// Increment level
		level++;
	}

	// Nothing found .. ?
	return -4;
}


#endif // CHESS_SEARCH_H_



