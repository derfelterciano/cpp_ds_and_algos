#pragma once

#include <cstddef>
#include <utility>

#include "PriorityQueue.hpp"

template <typename T, typename C>
void PriorityQueue<T, C>::sift_up(std::size_t idx) {
    // bubble up idx until heap is satisfied
    while (idx > 0) {
        std::size_t parent = (idx - 1) / 2;

        if (comp_(data_[idx], data_[parent])) {
            T tmp         = std::move(data_[idx]);
            data_[idx]    = std::move(data_[parent]);
            data_[parent] = std::move(tmp);

            idx = parent;
        } else {
            break;
        }
    }
}

template <typename T, typename C>
void PriorityQueue<T, C>::sift_down(std::size_t idx) {
    // push element down until heap is satisfied

    std::size_t n = data_.len();
    while (true) {
        std::size_t left  = 2 * idx + 1;
        std::size_t right = 2 * idx + 2;
        std::size_t best  = idx;

        if (left < n && comp_(data_[left], data_[best])) {
            best = left;
        }
        if (right < n && comp_(data_[right], data_[best])) {
            best = right;
        }

        // if we cant outrank anything else then we are
        // done
        if (best == idx) break;

        // else keep swapping
        T tmp       = std::move(data_[idx]);
        data_[idx]  = std::move(data_[best]);
        data_[best] = std::move(tmp);
        idx         = best;
    }
}
