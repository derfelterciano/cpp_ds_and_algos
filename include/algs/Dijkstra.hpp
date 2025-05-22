#pragma once

#include <cstddef>
#include <ds/Graph.hpp>
#include <ds/HashMap.hpp>
#include <ds/PriorityQueue.hpp>
#include <functional>
#include <tuple>

namespace algs {

enum class DijkstraState { Settled };

/// Dijkstra’s single‐source shortest‐paths on a weighted graph.
/// Returns a pair of maps:
///   - dist[v]   = minimum distance from `start` to `v`
///   - parent[v] = predecessor of `v` on that shortest path (`parent[start] ==
///   start`)
///
/// @tparam Vertex    the graph’s vertex type
/// @tparam Weight    edge‐weight type (must be totally ordered, no negatives)
/// @tparam Hash      hash functor for Vertex
/// @tparam KeyEqual  equality functor for Vertex
template <typename Vertex, typename Weight = double,
          typename Hash     = std::hash<Vertex>,
          typename KeyEqual = std::equal_to<Vertex>>
std::tuple<ds::HashMap<Vertex, Weight, Hash, KeyEqual>,  // dist map
           ds::HashMap<Vertex, Vertex, Hash, KeyEqual>>  // parent map
dijkstra(const ds::Graph<Vertex, Weight, Hash, KeyEqual>&  graph,
         const Vertex&                                     start,
         std::function<void(const Vertex&, DijkstraState)> onVisit = {}) {
    using DistMap   = ds::HashMap<Vertex, Weight, Hash, KeyEqual>;
    using ParentMap = ds::HashMap<Vertex, Vertex, Hash, KeyEqual>;
    using PQElem    = std::pair<Weight, Vertex>;

    using GraphT   = ds::Graph<Vertex, Weight, Hash, KeyEqual>;
    using AdjListT = typename GraphT::AdjList;
    using EdgeT    = typename GraphT::Edge;

    // our pq uses min heap by default
    ds::PriorityQueue<PQElem> pq;

    DistMap   dist;
    ParentMap parent;

    dist[start]   = Weight(0);
    parent[start] = start;

    pq.push({Weight(0), start});

    while (!pq.empty()) {
        auto [d, u] = pq.pop();

        // skipping stale entries
        if (d > dist[u]) {
            continue;
        }

        if (onVisit) onVisit(u, DijkstraState::Settled);

        // relax outgoing edges
        const AdjListT& neighbors = graph.neighbors(u);
        for (std::size_t i = 0; i < neighbors.len(); ++i) {
            const EdgeT&  edge = neighbors.at(i);
            const Vertex& v    = edge.to;
            Weight        nd   = d + edge.w;

            // if v is unseen or there's a shorter path to Vertex
            if (!dist.contains(v) || nd < dist[v]) {
                dist[v]   = nd;
                parent[v] = u;
                pq.push({nd, v});
            }
        }
    }

    return {std::move(dist), std::move(parent)};
}

}  // namespace algs
