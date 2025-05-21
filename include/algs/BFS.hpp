#pragma once

#include <cstddef>
#include <ds/HashMap.hpp>
#include <functional>

#include "ds/Graph.hpp"
#include "ds/Queue.hpp"

namespace algs {

enum class BFSState { Enqueued, Dequeued };

/// Breadth First Search
/// - records the number of edges from start dist[v]
/// - records the vertex from which v was first reached parent[v]
/// - optionally calls onVisit to store visited vertices
template <typename Vertex, typename Weight = double,
          typename Hash     = std::hash<Vertex>,
          typename KeyEqual = std::equal_to<Vertex>>
std::tuple<ds::HashMap<Vertex, std::size_t, Hash, KeyEqual>,  // dists
           ds::HashMap<Vertex, Vertex, Hash, KeyEqual>>
bfs(const ds::Graph<Vertex, Weight, Hash, KeyEqual>& graph, const Vertex& start,
    std::function<void(const Vertex&, BFSState)> onVisit = {}) {
    using MapDist   = ds::HashMap<Vertex, std::size_t, Hash, KeyEqual>;
    using MapParent = ds::HashMap<Vertex, Vertex, Hash, KeyEqual>;
    MapDist           dist;
    MapParent         parent;
    ds::Queue<Vertex> Q;  // queue

    // init
    dist[start]   = 0;
    parent[start] = start;
    Q.enqueue(start);
    if (onVisit) onVisit(start, BFSState::Enqueued);

    while (!Q.is_empty()) {
        Vertex u = Q.dequeue();
        if (onVisit) onVisit(u, BFSState::Dequeued);

        std::size_t du = dist[u];

        using GraphT   = ds::Graph<Vertex, Weight, Hash, KeyEqual>;
        using AdjListT = typename GraphT::AdjList;

        const AdjListT& neighbors = graph.neighbors(u);

        // at the time of making this, the linked list ds does not
        // contain an iterator
        for (std::size_t i = 0; i < neighbors.len(); ++i) {
            using EdgeT = typename GraphT::Edge;

            const EdgeT&  edge = neighbors.at(i);
            const Vertex& v    = edge.to;

            if (!dist.contains(v)) {
                dist[v]   = du + 1;
                parent[v] = u;

                Q.enqueue(v);

                if (onVisit) onVisit(v, BFSState::Enqueued);
            }
        }
    }

    return {std::move(dist), std::move(parent)};
}

}  // namespace algs
