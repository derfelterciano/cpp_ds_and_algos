#pragma once

#include "Vector.hpp"

template <typename T, typename Comp = std::less<T>>
class PriorityQueue {
   private:
    Vector<T> data_;
    Comp      comp_;

    /// restore heap by moving toward root
    void sift_up(std::size_t idx);

    /// restore heap by moving toward leaves (down)
    void sift_down(std::size_t idx);

   public:
    // c-tor + d-tor

    PriorityQueue() noexcept = default;
    PriorityQueue(std::initializer_list<T> init);
    ~PriorityQueue() noexcept = default;

    PriorityQueue(const PriorityQueue&)                = default;
    PriorityQueue(PriorityQueue&&) noexcept            = default;
    PriorityQueue& operator=(const PriorityQueue&)     = default;
    PriorityQueue& operator=(PriorityQueue&&) noexcept = default;

    // modifiers

    void push(const T& v);
    void push(T&& v);

    // remove
    T pop();

    // access

    // peek at the top element
    const T& top() const;

    // capacity
    bool empty() const noexcept {
        return data_.is_empty();
    }
    std::size_t size() const noexcept {
        return data_.len();
    }
    void clear() noexcept {
        data_.clear();
    }

    // runtime comparator
    void set_compare(Comp cmp);
};

#include "PriorityQueue.tpp"
