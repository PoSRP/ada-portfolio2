#ifndef COLlINEAR_SEARCH_H_
#define COLlINEAR_SEARCH_H_

/**
 * @file collinear-search.hpp
 *
 * @brief Search algorithm for collinear points in 1d vector of 2d points
 *
 * (note: The defgroup is here because it's the only header in the project)
 * @defgroup CollinearSearch AdaPortfolio
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
#include <ostream>
#include <unordered_map>
#include <map>
#include <inttypes.h>
#include <math.h> // for std::log and std::min

/**
 * Basic int64_t 2D point class
 */
struct point2d {
	/** point2d contructor
	 *
	 * @param X and Y values
	 */
	point2d(int64_t x = 0, int64_t y = 0) : x(x), y(y) {}

	/** point2d destructor
	 */
	~point2d() {}

	/** point2d Lesser Than operator
	 *
	 * @param Another point2d
	 * @return True if x is lesser, or x is equal and y is lesser, else returns false
	 */
	bool operator< (const point2d& rhs) {
		return (x < rhs.x || (x == rhs.x && y < rhs.y)) ? true : false;
	}

	/** point2d Greater Than operator
	 *
	 * @param Another point2d
	 * @return True if x is greater, or x is equal and y is greater, else returns false
	 */
	bool operator> (const point2d& rhs) {
		return (x > rhs.x || (x == rhs.x && y > rhs.y)) ? true : false;
	}

	/** point2d Lesser Than Or Equal operator
	 *
	 * @param Another point2d
	 * @return True if operator < or == is true, else returns false
	 */
	bool operator<= (const point2d& rhs) {
		return (*this < rhs || *this == rhs ? true : false);
	}

	/** point2d Greater Than Or Equal operator
	 *
	 * @param Another point2d
	 * @return True if operator > or == is true, else returns false
	 */
	bool operator>= (const point2d& rhs) {
		return (*this > rhs || *this == rhs ? true : false);
	}

	/** point2d equals operator (lhs == rhs)
	 *
	 * @param Another point2d with same type
	 * @return True if coordinates are identical, else returns false
	 */
	bool operator== (const point2d& rhs) {
		return (x == rhs.x && y == rhs.y) ? true : false;
	}

	/** point2d not equals operator (lhs != rhs)
	 *
	 * @param Another point2d with same type
	 * @return True if coordinates NOT identical, else returns false
	 */
	bool operator!= (const point2d& rhs) {
		return !(*this == rhs);
	}

	int64_t x; ///< 1st dimension / X coordinate of the point
	int64_t y; ///< 2nd dimension / Y coordinate of the point

private:
	/** point2d ostream operator (ostream << point2d)
	 *
	 * @param Stream to output to
	 * @param point2d to write to stream
	 * @return Output stream reference
	 */
	friend std::ostream& operator<< (std::ostream& os, const point2d& point) {
		return os << "{" << std::to_string(point.x) << "," << std::to_string(point.y) << "}";
	}
};

/** vector<point2d> in-place insertion sort
 *
 * @param std::vector<point2d> point group
 * @return Nothing
 */
inline void sort_point_group_ins(std::vector<point2d> &v) {
	// For every element
	for (size_t idx{0}; idx < v.size(); idx++) {
		size_t i{idx};
		// While not at the beginning and current element is less than previous
		while (i > 0 && (v[i] < v[i-1])) {
			// Flip elements and go further back
			point2d tmp = v[i];
			v[i] = v[i-1];
			v[i-1] = tmp;
			--i;
		}
	}
}

/** vector<point2d> comparison with pre-sorting
 *
 * @param vector<point2d> point group
 * @param vector<point2d> point group
 * @return True if vector contents are identical, else returns false
 */
inline bool compare_point_group(std::vector<point2d> &v1, std::vector<point2d> &v2) {
	// If not same size, definitely different
	if (v1.size() != v2.size()) return false;
	// Sort then compare
	sort_point_group_ins(v1);
	sort_point_group_ins(v2);
	for (size_t idx{0}; idx < v1.size(); idx++) {
		if (v1[idx] != v2[idx]) return false;
	}
	return true;
}

/** Greater Than Or Equals point group comparison
 *
 * @param vector<point2d> point group
 * @param vector<point2d> point group
 * @return True if vector contents of v1 are greater than or equal v2, else returns false
 */
inline bool gte_point_group(std::vector<point2d> &v1, std::vector<point2d> &v2) {
	sort_point_group_ins(v1);
	sort_point_group_ins(v2);
	size_t idx{0};
	while (idx < std::min(v1.size(), v2.size())) {
		if (v1[idx] < v2[idx]) return false;
		idx++;
	}
	// If we reached the end of either vector here, the longest is greater
	return ((v1.size() >= v2.size()) ? true : false);
}

/** vector<vector<point2d>> in-place insertion sort
 *
 * @param vector<vector<point2d>> group of point groups
 * @return Nothing
 */
inline void sort_point_groups_ins(std::vector<std::vector<point2d>> &vv) {
	// It's almost exactly like the one for single groups
	for (size_t idx{0}; idx < vv.size(); idx++) {
		size_t i{idx};
		while (i > 0 && (!gte_point_group(vv[i], vv[i-1]))) {
			std::vector<point2d> tmp = vv[i];
			vv[i] = vv[i-1];
			vv[i-1] = tmp;
			--i;
		}
	}
}

/** vector<vector<point2d>> comparison with pre-sorting
 *
 * @param vector<vector<point2d>> group of point groups
 * @param vector<vector<point2d>> group of point groups
 * @return True if 2d vector contents are identical, else returns false
 */
inline bool compare_point_groups(std::vector<std::vector<point2d>> &vv1, std::vector<std::vector<point2d>> &vv2) {
	// If not same size, definitely different
	if (vv1.size() != vv2.size()) return false;
	sort_point_groups_ins(vv1);
	sort_point_groups_ins(vv2);
	for (size_t idx{0}; idx < vv1.size(); idx++) {
		if (!compare_point_group(vv1[idx], vv2[idx])) return false;
	}
	return true;
}

const static int P1{107}; // Just some prime
const static int P2{109}; // Another some prime
/**
 * Very simple hashing function
 */
inline static int64_t hash_point2d(const point2d& p) {
	return (p.x * P1 + p.y * P2);
}
/**
 * Another very simple hashing function
 */
inline static double hash_line(const double a, const double b) {
	return (a * static_cast<double>(P1) + b * static_cast<double>(P2));
}

/** Collinear search algorithm
 *
 * @param A vector of 2d points
 * @return A vector of point-groups, where the groups are 4 or more collinear points
 */
inline static std::vector<std::vector<point2d>> collinear_search(std::vector<point2d>& points) {
	// Temporary storage during search
	std::vector<std::map<int64_t, point2d>*> out_map{};
	// The first element should be "invalid" and gets constructed here
	// It's because I reserve the 0 index for detecting value existence without using the find function
	// Using the find function would add n*logn inside the inner loop on worst cases, due to size of index_map
	out_map.push_back(new std::map<int64_t, point2d>());
	std::unordered_map<double, size_t> index_map{};
	// We also want to reserve some space in the objects to eliminate reallocations during the search
	// Maximum space complexity of both the output map and the index map is O(n*logn)
	out_map.reserve(points.size() * std::ceil<size_t>(std::log(static_cast<double>(points.size()))));
	index_map.reserve(points.size() * std::ceil<size_t>(std::log(static_cast<double>(points.size()))));

	// Sorting is a requirement from the assignment, but it isn't necessary
	// This is a simple insertion sort
	// Best case time complaxity O(n)
	// Worst case time complexity O(n*logn)
	sort_point_group_ins(points);

	// Time complexity of the search is O(n*logn) for best and worst cases
	// For every point
	for (size_t i{0}; i < points.size()-1; i++) {
		// Check line between this point and every other point
		for (size_t j{i+1}; j < points.size(); j++) {
			double a = static_cast<double>(points[j].y - points[i].y) / static_cast<double>(points[j].x - points[i].x);
			double b = static_cast<double>(points[i].y) - a * static_cast<double>(points[i].x);
			// Vertical lines are a special case, since a and b become inf or -inf or nan
			if (std::isinf(a) || std::isnan(a)) {
				// We don't care about the values of a and b anymore, only the "uniqueness"
				// Let's mock some from the points in another fashion, now that we know they are vertical
				double k = static_cast<double>(points[i].x * P1 / 1e4 + points[j].x * P2 / 1e4);
				a = hash_line(k, k);
				b = a;
			}

			// Check if the found line matches a previous one
			double hash = hash_line(a, b);
			// If there is a match, we get an index above 0
			size_t idx = index_map[hash];
			if (idx == 0) {
				// New hash, push new map to vector
				out_map.push_back(new std::map<int64_t, point2d>());
				// Set the index here
				idx = out_map.size()-1;
				// Save the index in the index map
				index_map[hash] = idx;
			}
			// Using a map as container to "sort out" duplicates within each group
			int64_t phash1 = hash_point2d(points[i]);
			int64_t phash2 = hash_point2d(points[j]);
			// Insertion
			out_map.at(idx)->insert(std::pair<int64_t, point2d>(phash1, points[i]));
			out_map.at(idx)->insert(std::pair<int64_t, point2d>(phash2, points[j]));
		}
	}

	// Transfer map contents to output vector<vector<point2d>>
	std::vector<std::vector<point2d>> out{};
	for (const std::map<int64_t, point2d> *map : out_map) {
		if (map->size() < 4) continue;
		out.push_back(std::vector<point2d>());
		for (const std::pair<int64_t, point2d>& p : *map) {
			out.back().push_back(p.second);
		}
	}

	// Remember to delete the maps
	for (std::map<int64_t, point2d> *map : out_map) {
		delete map;
	}

	return out;
}

#endif // COLINEAR_SEARCH_H_



