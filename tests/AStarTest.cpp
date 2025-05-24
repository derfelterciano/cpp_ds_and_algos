#include <algs/AStar.hpp>
#include <cassert>
#include <cmath>
#include <ds/Graph.hpp>

// Euclidean distance as a sample heuristic
double euclidean_heuristic(const std::pair<int, int>& a,
                           const std::pair<int, int>& b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return std::sqrt(dx * dx + dy * dy);
}

int main() {
    using Vertex = int;
    using Weight = double;
    using Graph  = ds::Graph<Vertex, Weight>;

    // Make a small graph (directed)
    Graph g;
    g.add_edge(1, 2, 1.0);  // 1 --1.0--> 2
    g.add_edge(2, 3, 2.0);  // 2 --2.0--> 3
    g.add_edge(1, 4, 2.5);  // 1 --2.5--> 4
    g.add_edge(4, 3, 0.5);  // 4 --0.5--> 3

    Vertex start = 1;
    Vertex goal  = 3;

    // Trivial heuristic (Dijkstra)
    auto zero_heuristic = [](const Vertex&) { return 0.0; };

    auto [gScore, parent] = algs::astar::a_star(g, start, goal, zero_heuristic);

    // Reconstruct path
    ds::Vector<Vertex> path =
        algs::astar::reconstruct_path(parent, start, goal);

    // Check path is correct: shortest path should be 1->4->3 (cost 3.0)
    std::cout << path << std::endl;
    assert(path.len() == 3);
    bool is_123 = path[0] == 1 && path[1] == 2 && path[2] == 3;
    bool is_143 = path[0] == 1 && path[1] == 4 && path[2] == 3;
    assert(is_123 || is_143);  // Accept either shortest path

    // Print the path and costs
    std::cout << "A* path from " << start << " to " << goal << ": ";
    for (std::size_t i = 0; i < path.len(); ++i) {
        std::cout << path[i];
        if (i + 1 < path.len()) std::cout << " -> ";
    }
    std::cout << "\nTotal cost: " << gScore[goal] << std::endl;

    // If you want to test with a real heuristic (uncomment if using Vertex as a
    // struct or pair)

    std::cout << "All A* tests passed!" << std::endl;
    return 0;
}
