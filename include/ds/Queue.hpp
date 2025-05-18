#pragma once

#include <cstddef>
#include <initializer_list>

#include "LinkedList.hpp"

namespace ds {

template <typename T>
class Queue {
   private:
    LinkedList<T> container_;

   public:
    Queue() noexcept = default;
    Queue(std::initializer_list<T> init) : container_(init) {}
    Queue(const Queue& other)     = default;
    Queue(Queue&& other) noexcept = default;
    ~Queue() noexcept             = default;

    Queue& operator=(const Queue& rhs)     = default;
    Queue& operator=(Queue&& rhs) noexcept = default;

    // enqueue
    void enqueue(const T& val) {
        container_.append(val);
    }
    void enqueue(T&& val) {
        container_.append(std::move(val));
    }

    // dequeue
    T dequeue() {
        return container_.pop_front();
    }

    // peek
    const T& front() const {
        return container_.front();
    }

    // capacity
    bool is_empty() const noexcept {
        return container_.is_empty();
    }
    std::size_t len() const noexcept {
        return container_.len();
    }

    // utility
    void clear() noexcept {
        container_.clear();
    }

    // comparisons
    bool operator==(const Queue& rhs) const noexcept {
        return container_ == rhs.container_;
    }
    bool operator!=(const Queue& rhs) const noexcept {
        return !(*this == rhs);
    }
};
}  // namespace ds
