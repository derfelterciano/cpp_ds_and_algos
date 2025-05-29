#pragma once

#include <ds/Graph.hpp>
#include <ds/Vector.hpp>
#include <utility>

#include "Maze.hpp"

enum class SolveMethod {
    DFS,
    BFS,
    ASTAR,
    DIJKSTRA,
};

using vrtx = std::pair<int, int>;

// converts a maze obj into a graph object
ds::Graph<vrtx> maze_to_graph(const Maze& maze);

// given a graph, solve the maze
ds::Vector<vrtx> solve(const ds::Graph<vrtx>& graph, vrtx start, vrtx end, SolveMethod method);

// high level interface that generates a graph, solves it, then returns the
// solution
ds::Vector<vrtx> solve_maze(const Maze& maze, SolveMethod method);