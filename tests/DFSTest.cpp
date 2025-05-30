#include <algs/DFS.hpp>
#include <cassert>
#include <ds/Graph.hpp>
#include <iostream>
#include <tuple>

#include "../src/lib/Utilities.hpp"

int main() {
    using algs::dfs;
    using ds::Graph;
    using Vertex = int;

    // 1) A simple directed “diamond” graph:
    //    0 → {1,2}, 1 → 3, 2 → 3
    Graph<Vertex> g = {{0, 1, 1.0}, {0, 2, 1.0}, {1, 3, 1.0}, {2, 3, 1.0}};

    auto parent = dfs(g, 0);

    // We should have exactly four entries: 0,1,2,3
    assert(parent.size() == 4);

    // start’s parent is itself
    assert(parent[0] == 0);

    // 1 and 2 discovered directly from 0
    assert(parent[1] == 0);
    assert(parent[2] == 0);

    // 3 first discovered via 1 (since DFS goes 0→1→3 before backtracking to 2)
    assert(parent[3] == 1);

    // 2) A graph with a single edge 10→11
    Graph<Vertex> g2{{10, 11, 2.5}};
    auto          parent2 = dfs(g2, 10);

    assert(parent2.size() == 2);
    assert(parent2[10] == 10);
    assert(parent2[11] == 10);

    // 3) Test DFS with std::pair<int, int> vertices (like in your maze)
    Graph<vrtx> grid_graph;
    // A 2x2 grid: (0,0) - (0,1)
    //              |       |
    //            (1,0) - (1,1)
    grid_graph.add_edge({0, 0}, {0, 1});
    grid_graph.add_edge({0, 0}, {1, 0});
    grid_graph.add_edge({0, 1}, {1, 1});
    grid_graph.add_edge({1, 0}, {1, 1});
    // Undirected: add reverse edges too
    grid_graph.add_edge({0, 1}, {0, 0});
    grid_graph.add_edge({1, 0}, {0, 0});
    grid_graph.add_edge({1, 1}, {0, 1});
    grid_graph.add_edge({1, 1}, {1, 0});

    auto parent_pair = dfs(grid_graph, {0, 0});

    assert(parent_pair.size() == 4);  // all four nodes reachable
    assert(parent_pair[vrtx({0, 0})] ==
           vrtx({0, 0}));  // Start is its own parent

    // The other parents could be any neighbor, since DFS can take different
    // orders. So check they exist and have a valid parent.
    assert(parent_pair.contains({0, 1}));
    assert(parent_pair.contains({1, 0}));
    assert(parent_pair.contains({1, 1}));

    // Print parent map for debugging
    std::cout << "DFS parent map for 2x2 grid:\n";
    for (auto node : {vrtx{0, 0}, vrtx{0, 1}, vrtx{1, 0}, vrtx{1, 1}}) {
        auto par = parent_pair.at(node);
        std::cout << "[" << node.first << "," << node.second << "] <- "
                  << "[" << par.first << "," << par.second << "]\n";
    }

    std::cout << "All DFS tests passed!\n";

    return 0;
}
