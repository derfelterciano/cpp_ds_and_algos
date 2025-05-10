#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <utility>

template <typename T>
class Vector {
   private:
    T*          data_     = nullptr;
    std::size_t size_     = 0;
    std::size_t capacity_ = 0;

    // increases buffer size
    void grow();

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
    void push_pack(T&& value);

    T& pop_back();

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
    std::size_t Capacity() const noexcept {
        return capacity_;
    }

    void reserve(std::size_t new_cap);
    void shrink_fit();

    // utils
    void clear() noexcept;

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
