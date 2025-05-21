#pragma once

#include <cstddef>
#include <initializer_list>
#include <tuple>

#include "HashMap.hpp"
#include "LinkedList.hpp"

namespace ds {

template <typename Vertex, typename Weight = double,
          typename Hash     = std::hash<Vertex>,
          typename KeyEqual = std::equal_to<Vertex>>
class Graph {
   public:
    struct Edge {
        Vertex to;
        Weight w;

        Edge() = default;
        Edge(const Vertex& _to, Weight _w) : to(_to), w(_w) {}
    };

    using AdjList = LinkedList<Edge>;

    // c-tors / d-tors

    explicit Graph() noexcept = default;

    /// initializer list
    Graph(std::initializer_list<std::tuple<Vertex, Vertex, Weight>> init) {
        for (auto& e : init) {
            add_edge(std::get<0>(e), std::get<1>(e), std::get<2>(e));
        }
    }

    // modifiers

    /// Add a directed edge
    void add_edge(const Vertex& u, const Vertex& v, Weight w = Weight()) {
        AdjList& v_list = adj_[u];
        v_list.append({v, w});

        ++edge_count_;

        // ensure v exists
        adj_.operator[](v);
    }

    /// Add an undirected edge
    void add_undirected_edge(const Vertex& u, const Vertex& v,
                             Weight w = Weight()) {
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    /// remove all edges
    void clear_edges() noexcept {
        adj_.clear();
        edge_count_ = 0;
    }

    // accessors

    /// return adjacency list
    const AdjList& neighbors(const Vertex& u) const {
        if (!adj_.contains(u))
            throw std::out_of_range("[Graph::neighbors()] Unknown Vertex!");

        return adj_.at(u);
    }

    // Info

    std::size_t num_vertices() const noexcept {
        return adj_.size();
    }
    std::size_t num_edges() const noexcept {
        return edge_count_;
    }

   private:
    HashMap<Vertex, AdjList, Hash, KeyEqual> adj_;
    std::size_t                              edge_count_ = 0;
};

}  // namespace ds
