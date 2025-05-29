#include "MazeSolver.hpp"

#include <algs/AStar.hpp>
#include <algs/BFS.hpp>
#include <algs/DFS.hpp>
#include <algs/Dijkstra.hpp>
#include <ds/Graph.hpp>
#include <ds/Vector.hpp>
#include <functional>
#include <utility>

#include "Maze.hpp"

namespace {
ds::Vector<vrtx> reconstruct_path(const vrtx& start, const vrtx& end,
                                  const ds::HashMap<vrtx, vrtx>& came_from) {
    ds::Vector<vrtx> path;
    vrtx             current = end;

    while (current != start) {
        path.push_back(current);

        if (!came_from.contains(current)) return ds::Vector<vrtx>{};
        current = came_from.at(current);
    }
    path.push_back(start);

    std::reverse(path.begin(), path.end());
    return path;
}
};  // namespace

ds::Graph<vrtx> maze_to_graph(const Maze& maze) {
    ds::Graph<vrtx> graph;
    int             rows = maze.rows(), cols = maze.cols();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            vrtx curr = {i, j};

            // up
            if (!maze.cell(i, j).top_wall && maze.in_bounds(i - 1, j)) {
                graph.add_edge(curr, vrtx{i - 1, j});
            }

            // down
            if (!maze.cell(i, j).bottom_wall && maze.in_bounds(i + 1, j)) {
                graph.add_edge(curr, vrtx{i + 1, j});
            }

            // right
            if (!maze.cell(i, j).right_wall && maze.in_bounds(i, j + 1)) {
                graph.add_edge(curr, vrtx{i, j + 1});
            }

            // left
            if (!maze.cell(i, j).left_wall && maze.in_bounds(i, j - 1)) {
                graph.add_edge(curr, vrtx{i, j - 1});
            }
        }
    }

    return graph;
}

ds::Vector<vrtx> solve(const ds::Graph<vrtx>& graph, vrtx start, vrtx end,
                       SolveMethod                      method,
                       std::function<void(const vrtx&)> onVisit) {
    ds::HashMap<vrtx, vrtx> came_from;
    switch (method) {
        case SolveMethod::DFS: {
            auto adapted =
                onVisit
                    ? [&](const vrtx& v, algs::DFSState) { return onVisit(v); }
                    : std::function<void(const vrtx&, algs::DFSState)>{};
            came_from = algs::dfs(graph, start, adapted);
            break;
        }
        case SolveMethod::BFS: {
            auto adapted =
                onVisit
                    ? [&](const vrtx& v, algs::BFSState) { return onVisit(v); }
                    : std::function<void(const vrtx&, algs::BFSState)>{};

            auto [dist, parent] = algs::bfs(graph, start, adapted);
            came_from           = parent;
            break;
        }
        case SolveMethod::DIJKSTRA: {
            auto adapted =
                onVisit
                    ? [&](const vrtx& v,
                          algs::DijkstraState) { return onVisit(v); }
                    : std::function<void(const vrtx&, algs::DijkstraState)>{};

            auto [dist, parent] = algs::dijkstra(graph, start, adapted);
            came_from           = parent;
            break;
        }
        default:
            throw std::invalid_argument("Unknown Solve Method!");
    }

    return reconstruct_path(start, end, came_from);
}

ds::Vector<vrtx> solve_maze(const Maze& maze, SolveMethod method,
                            std::function<void(const vrtx&)> onVisit) {
    ds::Graph<vrtx> graph = maze_to_graph(maze);
    vrtx            start = maze.get_start();
    vrtx            end   = maze.get_end();

    return solve(graph, start, end, method, onVisit);
}
