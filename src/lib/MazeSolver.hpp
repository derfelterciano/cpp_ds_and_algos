#pragma once

#include <ds/Graph.hpp>
#include <ds/Vector.hpp>
#include <functional>
#include <utility>

#include "Maze.hpp"

namespace std {
template <>
struct hash<std::pair<int, int>> {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
    }
};
};  // namespace std

enum class SolveMethod {
    DFS,
    BFS,
    DIJKSTRA,
};

using vrtx = std::pair<int, int>;

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
