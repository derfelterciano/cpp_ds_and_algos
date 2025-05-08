#pragma once

#include <cstddef>
#include <initializer_list>

#include "LinkedList.hpp"

template <typename T>
class Stack {
   private:
    LinkedList<T> container_;

   public:
    Stack() noexcept = default;
    Stack(std::initializer_list<T> init) : container_(init) {}
    Stack(const Stack& other)     = default;
    Stack(Stack&& other) noexcept = default;
    ~Stack() noexcept             = default;

    Stack& operator=(const Stack& rhs)     = default;
    Stack& operator=(Stack&& rnh) noexcept = default;

    // modifiers
    void push(const T& val) {
        container_.append(val);
    }
    void push(T&& val) {
        container_.append(std::move(val));
    }

    // accessor
    T pop() {
        return container_.pop_back();
    }

    const T& top() const {
        return container_.back();
    }

    // capacity
    bool is_empty() const noexcept {
        return container_.is_empty();
    }
    std::size_t len() const noexcept {
        return container_.len();
    }

    // utils
    void clear() noexcept {
        container_.clear();
    }
};
