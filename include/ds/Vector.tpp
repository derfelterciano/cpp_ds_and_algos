#pragma once

#include <cstddef>
#include <initializer_list>

#include "Vector.hpp"

using namespace std;

// private functions
template <typename T>
void Vector<T>::grow() {
    // double capacity or start at 1 if empty
    size_t newCapacity = capacity_ ? capacity_ * 2 : 1;

    reserve(newCapacity);

    return;
}

// Constructors
template <typename T>
Vector<T>::Vector(std::size_t count, const T& val)
    : data_(nullptr), size_(0), capacity_(0) {
    reserve(count);
    for (size_t i = 0; i < count; ++i) {
        new (data_ + i) T(val);
    }

    size_ = count;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : data_(nullptr), size_(0), capacity_(0) {
    reserve(init.size());

    size_t idx = 0;
    for (auto& v : init) {
        new (data_ + idx) T(v);
        ++idx;
    }

    size_ = init.size();
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : data_(nullptr), size_(0), capacity_(0) {
    reserve(other.size_);
    for (size_t i = 0; i < other.size_; ++i) {
        new (data_ + i) T(other.data_[i]);
    }

    size_ = other.size_;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    // make other vector empty
    other.data_     = nullptr;
    other.size_     = 0;
    other.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
    // delete elements
    clear();

    ::operator delete[](data_);
    data_ = nullptr;
}
