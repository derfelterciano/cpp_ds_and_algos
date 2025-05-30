#pragma once
#include <ds/Vector.hpp>
#include <functional>
#include <ostream>
#include <utility>

#include "ds/Graph.hpp"
#include "Maze.hpp"
#include "Utilities.hpp"

enum class SolveMethod {
    DFS,
    BFS,
    DIJKSTRA,
};

// converts a maze obj into a graph object
ds::Graph<vrtx> maze_to_graph(const Maze& maze);

// given a graph, solve the maze
ds::Vector<vrtx> solve(const ds::Graph<vrtx>& graph, vrtx start, vrtx end,
                       SolveMethod                      method,
                       std::function<void(const vrtx&)> onVisit = {});

// high level interface that generates a graph, solves it, then returns the
// solution
ds::Vector<vrtx> solve_maze(const Maze& maze, SolveMethod method,
                            std::function<void(const vrtx&)> onVisit = {});
