#pragma once

#include <cstddef>
#include <utility>

#include "PriorityQueue.hpp"

// Private functions

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

/// init constructor

template <typename T, typename C>
PriorityQueue<T, C>::PriorityQueue(std::initializer_list<T> init)
    : data_(init) {
    // bottom up heapify
    for (std::size_t i = data_.len() / 2; i-- > 0;) {
        sift_down(i);
    }
}

// modifiers

/// Pushs an element into the PriorityQueue
template <typename T, typename C>
void PriorityQueue<T, C>::push(const T& v) {
    data_.push_back(v);
    sift_up(size() - 1);
}

/// Pushs an element into the PriorityQueue
template <typename T, typename C>
void PriorityQueue<T, C>::push(T&& v) {
    data_.push_back(std::move(v));
    sift_up(size() - 1);
}

template <typename T, typename C>
T PriorityQueue<T, C>::pop() {
    if (data_.is_empty())
        throw std::out_of_range(
            "[PriorityQueue:pop()] pop() on an empty queue!");

    // grab root
    T root = std::move(data_[0]);

    // move last element as root
    data_[0] = std::move(data_.back());

    // remove old last element
    data_.pop_back();

    // sift "new root" down
    if (!data_.is_empty()) {
        sift_down(0);
    }

    return root;
}

template <typename T, typename C>
const T& PriorityQueue<T, C>::top() const {
    if (data_.is_empty())
        throw std::out_of_range(
            "[PriorityQueue::top()] Peeking an empty queue!");

    return data_[0];
}

template <typename T, typename C>
void PriorityQueue<T, C>::set_compare(C cmp) {
    // change comparator
    comp_ = std::move(cmp);

    // heapify
    for (std::size_t i = data_.len() / 2; i-- > 0;) {
        sift_down(i);
    }
}
