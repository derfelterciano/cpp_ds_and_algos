#include <algs/DFS.hpp>
#include <cassert>
#include <ds/Graph.hpp>
#include <iostream>
#include <tuple>

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

    std::cout << "All DFS tests passed!\n";

    return 0;
}
