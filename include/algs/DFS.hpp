#pragma once

#include <ds/Graph.hpp>
#include <ds/HashMap.hpp>
#include <functional>

namespace algs {

/// DFS callback enums
enum class DFSState { Discover, Finish };

/// Depth First Search: records a parent-pointer tree.
/// - `parent[start] == start`
/// - For every other reached vertex `v`, `parent[v]` is the vertex
///   from which `v` was first discovered.
/// - Optional `onVisit(u, state)` callback at discover/finish times.
///
/// Returns the parent‐map for every reachable vertex.
template <typename Vertex, typename Weight, typename Hash, typename KeyEqual>
ds::HashMap<Vertex, Weight, Hash, KeyEqual> dfs(
    const ds::Graph<Vertex, Weight, Hash, KeyEqual> graph, const Vertex& start,
    std::function<void(const Vertex&, DFSState)> onVisit = {}) {
    using ParentMap  = ds::HashMap<Vertex, Vertex, Hash, KeyEqual>;
    using VisitedMap = ds::HashMap<Vertex, bool, Hash, KeyEqual>;
    using GraphT     = ds::Graph<Vertex, Weight, Hash, KeyEqual>;
    using AdjListT   = typename GraphT::AdjList;
    using EdgeT      = typename GraphT::Edge;

    ParentMap  parent;
    VisitedMap visited;

    // c++17 recursive lambda helper function
    std::function<void(const Vertex&)> dfs_recurse;

    dfs_recurse = [&](const Vertex& u) {
        visited[u] = true;
        if (onVisit) onVisit(u, DFSState::Discover);

        const AdjListT& neighbor = graph.neighbors(u);

        for (std::size_t i = 0; i < neighbor.len(); ++i) {
            const EdgeT&  edge = neighbor.at(i);
            const Vertex& v    = edge.to;

            if (!visited.contains(v)) {
                parent[v] = u;
                dfs_recurse(v);
            }
        }
    };

    // initialize
    parent[start] = start;
    dfs_recurse(start);
    return parent;
}

}  // namespace algs
