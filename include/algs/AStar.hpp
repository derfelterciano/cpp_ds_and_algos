#pragma once

#include <ds/Graph.hpp>
#include <ds/HashMap.hpp>
#include <ds/PriorityQueue.hpp>
#include <functional>
#include <limits>
#include <tuple>
#include <utility>

namespace algs {
namespace astar {

template <typename Vertex, typename Weight = double,
          typename Hash     = std::hash<Vertex>,
          typename KeyEqual = std::equal_to<Vertex>>
std::tuple<ds::HashMap<Vertex, Weight, Hash, KeyEqual>,  // gscore map
           ds::HashMap<Vertex, Vertex, Hash, KeyEqual>   // parent map
           >
a_star(const ds::Graph<Vertex, Weight, Hash, KeyEqual>& graph,
       const Vertex& start, const Vertex& goal,
       std::function<Weight(const Vertex&)> heuristic) {
    using DistMap   = ds::HashMap<Vertex, Weight, Hash, KeyEqual>;
    using ParentMap = ds::HashMap<Vertex, Vertex, Hash, KeyEqual>;
    using PQElem    = std::pair<Weight, Vertex>;

    ds::PriorityQueue<PQElem> openSet;

    DistMap   gScore;
    DistMap   fScore;
    ParentMap parent;

    gScore[start] = Weight(0);
    fScore[start] = heuristic(start);

    openSet.push({fScore[start], start});
    parent[start] = start;

    while (!openSet.empty()) {
        PQElem currElem = openSet.pop();
        Weight currF    = currElem.first;
        Vertex currV    = currElem.second;

        // we reached out goal
        if (currV == goal) {
            break;
        }

        const auto& neighbors = graph.neighbors(currV);
        for (std::size_t i = 0; i < neighbors.len(); ++i) {
            const auto&   edge             = neighbors.at(i);
            const Vertex& neighbor         = edge.to;
            Weight        tentative_gScore = gScore[currV] + edge.w;

            if (!gScore.contains(neighbor) ||
                tentative_gScore < gScore[neighbor]) {
                parent[neighbor] = currV;
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = tentative_gScore + heuristic(neighbor);
                openSet.push({fScore[neighbor], neighbor});
            }
        }
    }

    return {std::move(gScore), std::move(parent)};
}

}  // namespace astar
}  // namespace algs
