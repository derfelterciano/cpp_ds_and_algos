#pragma once

#include <cstddef>
#include <initializer_list>
#include <utility>

template <typename T>
class LinkedList {
   private:
    struct Node {
        T     data;
        Node* prev;
        Node* next;

        // constructor using initializer list
        Node(const T& v) : data(v), prev(nullptr), next(nullptr) {}
        Node(T&& v) : data(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    Node*       head_ = nullptr;
    Node*       tail_ = nullptr;
    std::size_t size_ = 0;
    std::size_t pos_  = 0;

    // grabs node at index
    Node* node_at(std::size_t idx) const noexcept;

   public:
    LinkedList();
    LinkedList(std::initializer_list<T> init);
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;
    ~LinkedList();

    LinkedList& operator=(const LinkedList& rhs);
    LinkedList& operator=(LinkedList&& rhs) noexcept;

    // === Capacity ===
    bool is_empty() const noexcept {
        return size_ == 0;
    }
    std::size_t len() const noexcept {
        return size_;
    }

    // === Indexing ===
    T&       at(std::size_t index);
    const T& at(std::size_t index) const;

    T&       operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    // === Access ===
    T&       front();
    const T& front() const;
    T&       back();
    const T& back() const;

    // === Modifier ===
    void prepend(const T& val);
    void prepend(T&& val);

    void append(const T& val);
    void append(T&& val);

    T pop_front();
    T pop_back();

    void insert(std::size_t idx, const T& value);
    void insert(std::size_t idx, T&& value);

    void        del(std::size_t idx);
    std::size_t remove(const T& val);

    void clear() noexcept;

    // === Lookup ===
    bool contains(const T& val) const noexcept;

    // === Utils ===
    void reverse() noexcept;
    void print() const;

    // === comparisons ===
    bool operator==(const LinkedList& rhs) const noexcept;
    bool operator!=(const LinkedList& rhs) const noexcept {
        return !(*this == rhs);
    }
};

#include "LinkedList.tpp"
