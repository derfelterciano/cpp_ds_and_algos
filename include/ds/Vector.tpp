#pragma once

#include <cstddef>
#include <initializer_list>
#include <new>
#include <stdexcept>
#include <utility>

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

template <typename T>
void Vector<T>::reallocate(std::size_t cap) {
    // raw allocate
    T* new_data = static_cast<T*>(::operator new[](cap * sizeof(T)));

    // move and initalize if possible
    for (size_t i = 0; i < size_; ++i) {
        new (new_data + i) T(std::move_if_noexcept(data_[i]));
        data_[i].~T();
    }

    // free old buffer
    ::operator delete[](data_);

    data_     = new_data;
    capacity_ = cap;
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

// overload constrcutors

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs) {
    if (this != &rhs) {
        // destroy all our items
        clear();

        // reuse or grow
        reserve(rhs.size_);

        for (size_t i = 0; i < rhs.size_; ++i) {
            new (data_ + i) T(rhs.data_[i]);
        }
        size_ = rhs.size_;
    }

    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) noexcept {
    if (this != &rhs) {
        // destroy contents and free memory
        clear();
        ::operator delete[](data_);

        data_     = rhs.data_;
        size_     = rhs.size_;
        capacity_ = rhs.capacity_;

        // zero out rhs
        rhs.data_     = nullptr;
        rhs.size_     = 0;
        rhs.capacity_ = 0;
    }

    return *this;
}

// capacity operations

template <typename T>
void Vector<T>::reserve(std::size_t new_cap) {
    if (new_cap <= capacity_) return;

    reallocate(new_cap);

    return;
}

template <typename T>
void Vector<T>::shrink_fit() {
    if (capacity_ <= size_) return;

    reallocate(size_);
    return;
}

// utils

template <typename T>
void Vector<T>::clear() noexcept {
    for (size_t i = 0; i < size_; ++i) {
        data_[i].~T();
    }

    size_ = 0;
    return;
}

// Modifiers

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) grow();

    new (data_ + size_) T(value);

    ++size_;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
    if (size_ == capacity_) grow();

    new (data_ + size_) T(move(value));

    ++size_;
}

template <typename T>
T Vector<T>::pop_back() {
    if (size_ == 0) throw out_of_range("popping on an empty vector!");
    --size_;

    T tmp = move(data_[size_]);
    data_[size_].~T();

    return tmp;
}

// Accessors

template <typename T>
T& Vector<T>::at(std::size_t idx) {
    if (idx >= size_)
        throw out_of_range("[Vector::at()] idx is out of range in vector!");

    return data_[idx];
}

template <typename T>
const T& Vector<T>::at(std::size_t idx) const {
    if (idx >= size_)
        throw out_of_range("[Vector::at()] idx is out of range in vector!");

    return data_[idx];
}

template <typename T>
T& Vector<T>::operator[](std::size_t idx) {
    return data_[idx];
}

template <typename T>
const T& Vector<T>::operator[](std::size_t idx) const {
    return data_[idx];
}

template <typename T>
T& Vector<T>::front() {
    if (size_ == 0)
        throw out_of_range("[Vector::front()] This vector is empty!");

    return data_[0];
}

template <typename T>
const T& Vector<T>::front() const {
    if (size_ == 0)
        throw out_of_range("[Vector::front()] This vector is empty!");

    return data_[0];
}

template <typename T>
T& Vector<T>::back() {
    if (size_ == 0)
        throw out_of_range("[Vector::back()] This vector is empty!");

    return data_[size_ - 1];
}

template <typename T>
const T& Vector<T>::back() const {
    if (size_ == 0)
        throw out_of_range("[Vector::back()] This vector is empty!");

    return data_[size_ - 1];
}

// comparators
template <typename T>
bool Vector<T>::operator==(const Vector& rhs) const noexcept {
    if (len() != rhs.len()) return false;

    for (size_t i = 0; i < len(); ++i) {
        if (data_[i] != rhs.data_[i]) return false;
    }

    return true;
}
