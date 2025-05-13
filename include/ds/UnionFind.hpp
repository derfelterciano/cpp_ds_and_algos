#pragma once

#include <cstddef>
#include <type_traits>

#include "Vector.hpp"

/// Union Find with union by rank and path compressions
/// Index = type used for elements (def: std::size_t)
/// An index must be some sort of integral type
template <typename Index = std::size_t>
class UnionFind {
    static_assert(std::is_integral<Index>::value,
                  "UnionFind<Index>: Index must be of intgral type!");

   private:
    Vector<Index> parent_;
    Vector<Index> rank_;

   public:
    /// Construct singleton sets
    explicit UnionFind(Index n) noexcept : parent_(n), rank_(n, 0) {
        for (Index i = 0; i < n; ++i) {
            parent_[i] = i;
        }
    };

    /// find rep. root of set set containing x
    Index find(Index x) noexcept {
        if (parent_[x] != x) {
            parent_[x] = find(parent_[x]);
        }

        return parent_[x];
    }

    /// unite sets containing a and b
    /// return true if in different sets
    bool unite(Index a, Index b) noexcept {
        Index ra = find(a);
        Index rb = find(b);

        if (ra == rb) return false;

        // union by rank
        if (rank_[ra] < rank_[rb]) {
            parent_[ra] = rb;
        } else if (rank_[rb] < rank_[ra]) {
            parent_[rb] = ra;
        } else {
            parent_[rb] = ra;
            ++rank_[ra];
        }

        return true;
    }

    /// check if a and b are the same set
    bool connected(Index a, Index b) noexcept {
        return find(a) == find(b);
    }
};
