#include <cassert>
#include <ds/Graph.hpp>
#include <iostream>

int main() {
    using ds::Graph;

    // 1) empty graph
    Graph<int> g;
    assert(g.num_vertices() == 0);
    assert(g.num_edges() == 0);

    // 2) add a directed edge 1→2 weight 3.5
    g.add_edge(1, 2, 3.5);
    assert(g.num_vertices() == 2);
    assert(g.num_edges() == 1);

    //   neighbors(1) has exactly one edge to 2
    const auto& nbrs1 = g.neighbors(1);
    assert(nbrs1.len() == 1);
    assert(nbrs1.at(0).to == 2);
    assert(nbrs1.at(0).w == 3.5);

    //   neighbors(2) exists but is empty
    const auto& nbrs2 = g.neighbors(2);
    assert(nbrs2.len() == 0);

    //   asking for unknown vertex throws
    bool threw = false;
    try {
        g.neighbors(42);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    // 3) clear all edges, then add an undirected edge 5↔6
    g.clear_edges();
    g.add_undirected_edge(5, 6, 1.1);
    assert(g.num_vertices() == 2);
    assert(g.num_edges() == 2);

    const auto& nbrs5 = g.neighbors(5);
    assert(nbrs5.len() == 1);
    assert(nbrs5.at(0).to == 6);
    assert(nbrs5.at(0).w == 1.1);

    const auto& nbrs6 = g.neighbors(6);
    assert(nbrs6.len() == 1);
    assert(nbrs6.at(0).to == 5);
    assert(nbrs6.at(0).w == 1.1);

    // 4) initializer_list constructor
    Graph<int> g2{{0, 1, 2.0}, {0, 2, 4.5}, {3, 0, 1.0}};
    assert(g2.num_vertices() == 4);
    assert(g2.num_edges() == 3);

    //   neighbors(0) should contain edges to 1 and 2
    const auto& nbrs0 = g2.neighbors(0);
    assert(nbrs0.len() == 2);
    bool found1 = false, found2 = false;
    for (std::size_t i = 0; i < nbrs0.len(); ++i) {
        if (nbrs0.at(i).to == 1 && nbrs0.at(i).w == 2.0) found1 = true;
        if (nbrs0.at(i).to == 2 && nbrs0.at(i).w == 4.5) found2 = true;
    }
    assert(found1 && found2);

    // 5) clear g2 and check it's empty again
    g2.clear_edges();
    assert(g2.num_vertices() == 0);
    assert(g2.num_edges() == 0);

    std::cout << "All Graph tests passed!\n";

    return 0;
}
