#include <algs/Dijkstra.hpp>
#include <cassert>
#include <ds/Graph.hpp>
#include <iostream>
#include <tuple>

int main() {
    using algs::dijkstra;
    using ds::Graph;
    using Vertex = int;
    using Weight = int;

    // 1) A small weighted graph:
    //    0 → 1 (5), 0 → 2 (3), 1 → 3 (1), 2 → 3 (7), 0 → 3 (10)
    Graph<Vertex, Weight> g{
        {0, 1, 5}, {0, 2, 3}, {1, 3, 1}, {2, 3, 7}, {0, 3, 10}};

    auto [dist, parent] = dijkstra(g, 0);

    // distances
    assert(dist.size() == 4);
    assert(dist[0] == 0);
    assert(dist[1] == 5);
    assert(dist[2] == 3);
    // shortest path to 3 is 0→1→3 with cost 6
    assert(dist[3] == 6);

    // parent pointers
    assert(parent[0] == 0);
    assert(parent[1] == 0);
    assert(parent[2] == 0);
    assert(parent[3] == 1);

    // 2) A graph with a single edge 10→11 (weight 2)
    Graph<Vertex, Weight> g2{{10, 11, 2}};
    auto [d2, p2] = dijkstra(g2, 10);

    assert(d2.size() == 2);
    assert(d2[10] == 0);
    assert(d2[11] == 2);

    assert(p2[10] == 10);
    assert(p2[11] == 10);

    std::cout << "All Dijkstra tests passed!\n";

    return 0;
}
