#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <string>
#include <utility>

template <typename T>
class Vector {
   private:
    T*          data_     = nullptr;
    std::size_t size_     = 0;
    std::size_t capacity_ = 0;

    /// increases buffer size
    void grow();

    /// reallocates cap amount of memory
    /// then moves data to newly allocated buffer
    void reallocate(std::size_t cap);

   public:
    // De/Constructors
    Vector() noexcept = default;
    Vector(std::size_t count, const T& val = T());
    Vector(std::initializer_list<T> init);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    Vector& operator=(const Vector& rhs);
    Vector& operator=(Vector&& rhs) noexcept;

    // modifiers
    void push_back(const T& value);
    void push_back(T&& value);

    T pop_back();

    // Accessors
    T&       at(std::size_t idx);
    const T& at(std::size_t idx) const;

    T&       operator[](std::size_t idx);
    const T& operator[](std::size_t idx) const;

    T&       front();
    const T& front() const;
    T&       back();
    const T& back() const;

    // Capacity
    bool is_empty() const noexcept {
        return size_ == 0;
    }
    std::size_t len() const noexcept {
        return size_;
    }
    std::size_t capacity() const noexcept {
        return capacity_;
    }

    /// Main memory controller
    void reserve(std::size_t new_cap);

    /// Shrinks memory foot print if possible
    void shrink_fit();

    // utils
    void                 clear() noexcept;
    std::string          debug_vec() const;
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
        os << v.debug_vec();
        return os;
    }

    // iterators
    T* begin() noexcept {
        return data_;
    }
    const T* begin() const noexcept {
        return data_;
    }
    T* end() noexcept {
        return data_ + size_;
    }
    const T* end() const noexcept {
        return data_ + size_;
    }

    // comparators
    bool operator==(const Vector& rhs) const noexcept;
    bool operator!=(const Vector& rhs) const noexcept {
        return !(*this == rhs);
    }
};

#include "Vector.tpp"
