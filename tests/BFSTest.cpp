#include <algs/BFS.hpp>
#include <cassert>
#include <ds/Graph.hpp>
#include <iostream>

int main() {
    using algs::bfs;
    using ds::Graph;
    using Vertex = int;

    // 1) Simple directed “diamond” graph:
    //    0 → {1, 2}, 1 → 3, 2 → 3
    Graph<Vertex> g{{0, 1, 1.0}, {0, 2, 1.0}, {1, 3, 1.0}, {2, 3, 1.0}};

    auto [dist, parent] = bfs(g, 0);

    std::cout << "g1 dist: " << dist << std::endl;
    std::cout << "g1 parent: " << parent << std::endl;

    // distances
    assert(dist.size() == 4);
    assert(dist[0] == 0);
    assert(dist[1] == 1);
    assert(dist[2] == 1);
    assert(dist[3] == 2);

    // parent pointers
    assert(parent[0] == 0);  // start’s parent is itself
    assert(parent[1] == 0);
    assert(parent[2] == 0);
    // 3 was first discovered from 1 (since 1 was dequeued before 2)
    assert(parent[3] == 1);

    // 2) Disconnected / single‐edge graph
    Graph<Vertex> g2{{10, 11, 2.5}};
    auto [dist2, parent2] = bfs(g2, 10);

    std::cout << "g2 dist: " << dist2 << std::endl;
    std::cout << "g2 parent: " << parent2 << std::endl;

    assert(dist2.size() == 2);
    assert(dist2[10] == 0);
    assert(dist2[11] == 1);

    assert(parent2[10] == 10);
    assert(parent2[11] == 10);

    std::cout << "All BFS tests passed!\n";
    return 0;
}
