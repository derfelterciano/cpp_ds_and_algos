#include <algs/AStar.hpp>
#include <cassert>
#include <cmath>
#include <ds/Graph.hpp>
#include <functional>

// EXAMPLE 1: Integers as Vertices, Trivial Heuristic (Dijkstra)
void test_a_star_with_integers() {
    using Vertex = int;
    using Weight = double;
    using Graph  = ds::Graph<Vertex, Weight>;

    Graph g;
    g.add_edge(1, 2, 1.0);  // 1 --1.0--> 2
    g.add_edge(2, 3, 2.0);  // 2 --2.0--> 3
    g.add_edge(1, 4, 2.5);  // 1 --2.5--> 4
    g.add_edge(4, 3, 0.5);  // 4 --0.5--> 3

    Vertex start = 1;
    Vertex goal  = 3;

    // Heuristic: Dijkstra (always zero)
    std::function<Weight(const Vertex&)> zero_heuristic = [](const Vertex&) {
        return 0.0;
    };

    auto [gScore, parent] = algs::astar::a_star(g, start, goal, zero_heuristic);

    ds::Vector<Vertex> path =
        algs::astar::reconstruct_path(parent, start, goal);

    // Accept either shortest path (1->2->3 or 1->4->3)
    bool is_123 =
        path.len() == 3 && path[0] == 1 && path[1] == 2 && path[2] == 3;
    bool is_143 =
        path.len() == 3 && path[0] == 1 && path[1] == 4 && path[2] == 3;
    assert(is_123 || is_143);

    std::cout << "Integer graph path: ";
    for (std::size_t i = 0; i < path.len(); ++i) {
        std::cout << path[i];
        if (i + 1 < path.len()) std::cout << " -> ";
    }
    std::cout << "\nTotal cost: " << gScore[goal] << std::endl;
}

// EXAMPLE 2: String Vertices, Custom Heuristic
void test_a_star_with_strings() {
    using Vertex = std::string;
    using Weight = double;
    using Graph  = ds::Graph<Vertex, Weight>;

    Graph g;
    g.add_edge("A", "B", 2.0);
    g.add_edge("A", "C", 5.0);
    g.add_edge("B", "D", 2.0);
    g.add_edge("C", "D", 1.0);

    Vertex start = "A";
    Vertex goal  = "D";

    // Heuristic: Difference in string length (silly example)
    std::function<Weight(const Vertex&)> heuristic = [goal](const Vertex& v) {
        return std::abs(static_cast<int>(v.length()) -
                        static_cast<int>(goal.length()));
    };

    auto [gScore, parent] = algs::astar::a_star(g, start, goal, heuristic);
    ds::Vector<Vertex> path =
        algs::astar::reconstruct_path(parent, start, goal);

    assert(path.len() >= 2);  // At least start and goal
    assert(path[0] == "A" && path[path.len() - 1] == "D");

    std::cout << "String graph path: ";
    for (std::size_t i = 0; i < path.len(); ++i) {
        std::cout << path[i];
        if (i + 1 < path.len()) std::cout << " -> ";
    }
    std::cout << "\nTotal cost: " << gScore[goal] << std::endl;
}

int main() {
    test_a_star_with_integers();
    test_a_star_with_strings();

    std::cout << "All A* tests passed!" << std::endl;
    return 0;
}
