#pragma once
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>

#include "LinkedList.hpp"
using namespace std;

template <typename T>
LinkedList<T>::LinkedList(){};

template <typename T>
LinkedList<T>::LinkedList(initializer_list<T> init)
    : head_(nullptr), tail_(nullptr), size_(0), pos_(0) {
    for (auto& v : init) {
        append(v);
    }
}

/**
 * Copy constructors
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
    : head_(nullptr), tail_(nullptr), size_(0), pos_(0) {
    // iterate through each of the nodes
    for (Node* curr = other.head_; curr != nullptr; curr = curr->next) {
        append(curr->data);
    }
}

/**
 * Move constructors
 */
template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
    : head_(other.head_),
      tail_(other.tail_),
      size_(other.size_),
      pos_(other.pos_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
    other.pos_  = 0;
}

// Deconstructor
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// === Modifiers ===

template <typename T>
void LinkedList<T>::prepend(const T& val) {
    // allocate node
    Node* newNode = new Node(val);

    // set the new node to become the head
    newNode->next = head_;
    newNode->prev = nullptr;

    if (head_) {
        head_->prev = newNode;
    }
    head_ = newNode;

    if (!tail_) {
        tail_ = newNode;
    }

    ++size_;
}

template <typename T>
void LinkedList<T>::prepend(T&& val) {
    Node* newNode = new Node(std::move(val));

    // set the new node to become the head
    newNode->next = head_;
    newNode->prev = nullptr;

    if (head_) {
        head_->prev = newNode;
    }
    head_ = newNode;

    if (!tail_) {
        tail_ = newNode;
    }

    ++size_;
}

template <typename T>
void LinkedList<T>::append(const T& val) {
    Node* newNode = new Node(val);

    // set the previous to become the new tail
    newNode->prev = tail_;
    newNode->next = nullptr;

    if (tail_) {
        tail_->next = newNode;
    }
    tail_ = newNode;

    if (!head_) {
        head_ = newNode;
    }

    ++size_;
}

template <typename T>
void LinkedList<T>::append(T&& val) {
    Node* newNode = new Node(std::move(val));

    // set the previous to become the new tail
    newNode->prev = tail_;
    newNode->next = nullptr;

    if (tail_) {
        tail_->next = newNode;
    }
    tail_ = newNode;

    if (!head_) {
        head_ = newNode;
    }

    ++size_;
}

template <typename T>
T LinkedList<T>::pop_front() {
    if (head_) {
        Node* front_node = head_;
        T     val        = std::move(front_node->data);

        head_ = front_node->next;

        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        // disconnect node from entire struct
        front_node->next = nullptr;
        front_node->prev = nullptr;

        delete front_node;
        front_node = nullptr;

        --size_;

        return val;
    } else {
        out_of_range("Cannot pop front an empty list!");
    }
}

template <typename T>
T LinkedList<T>::pop_back() {
    if (tail_) {
        Node* rear_node = tail_;
        T     val       = std::move(rear_node->data);

        tail_ = rear_node->prev;

        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        rear_node->prev = nullptr;
        rear_node->next = nullptr;

        delete rear_node;
        rear_node = nullptr;

        --size_;

        return val;
    } else {
        out_of_range("Cannot pop back from an empty list!");
    }
}

template <typename T>
void LinkedList<T>::clear() noexcept {
    while (size_ > 0) {
        pop_back();
    }
}

// helper function
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::node_at(
    size_t idx) const noexcept {
    if (idx >= size_) return nullptr;

    Node* curr = head_;

    for (size_t i = 0; i < idx && curr; ++i) {
        curr = curr->next;
    }

    return curr;
}

template <typename T>
void LinkedList<T>::insert(std::size_t idx, const T& value) {
    if (idx == 0) {
        prepend(value);
        return;
    }

    if (idx >= size_) {
        append(value);
        return;
    }

    // Middle insertion
    Node* nextNode = node_at(idx);
    Node* prevNode = nextNode->prev;

    Node* newNode = new Node(value);
    newNode->prev = prevNode;
    newNode->next = nextNode;

    prevNode->next = newNode;
    nextNode->prev = newNode;

    ++size_;
}

template <typename T>
void LinkedList<T>::insert(std::size_t idx, T&& value) {
    if (idx == 0) {
        prepend(std::move(value));
        return;
    }

    if (idx >= size_) {
        append(std::move(value));
        return;
    }

    // Middle insertion
    Node* nextNode = node_at(idx);
    Node* prevNode = nextNode->prev;

    Node* newNode = new Node(std::move(value));
    newNode->prev = prevNode;
    newNode->next = nextNode;

    prevNode->next = newNode;
    nextNode->prev = newNode;

    ++size_;
}

template <typename T>
void LinkedList<T>::del(size_t idx) {
    if (size_ == 0) return;

    if (idx == 0) {
        pop_front();
        return;
    }
    if (idx >= size_ - 1) {
        pop_back();
        return;
    }
    // Middle delete
    Node* midNode  = node_at(idx);
    Node* nextNode = midNode->next;
    Node* prevNode = midNode->prev;

    // connect the neightboring nodes together
    nextNode->prev = prevNode;
    prevNode->next = nextNode;

    midNode->next = midNode->prev = nullptr;

    delete midNode;
    midNode = nullptr;

    --size_;
}

// remove all occurances of T& val
template <typename T>
std::size_t LinkedList<T>::remove(const T& val) {
    size_t count = 0;
    Node*  curr  = head_;

    while (curr) {
        Node* next = curr->next;

        if (curr->data == val) {
            // unlink
            if (curr->prev) {
                curr->prev->next = curr->next;
            } else {
                head_ = curr->next;
            }

            if (curr->next) {
                curr->next->prev = curr->prev;
            } else {
                tail_ = curr->prev;
            }

            curr->next = curr->prev = nullptr;
            delete curr;
            curr = nullptr;

            --size_;
            ++count;
        }

        curr = next;
    }

    return count;
}

// === lookup ===
template <typename T>
bool LinkedList<T>::contains(const T& val) const noexcept {
    for (Node* curr = head_; curr; curr = curr->next) {
        if (curr->data == val) {
            return true;
        }
    }
    return false;
}

// === utility ===
template <typename T>
void LinkedList<T>::reverse() noexcept {
    if (!head_ && !head_->next) return;

    Node* curr = head_;
    Node* temp = nullptr;

    while (curr) {
        temp       = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;

        // curr->prev is old next after swap
        curr = curr->prev;
    }

    // swap heads and tails
    temp  = head_;
    head_ = tail_;
    tail_ = temp;
}

template <typename T>
void LinkedList<T>::print() const {
    for (Node* curr = head_; curr; curr = curr->next) {
        T data = curr->data;

        std::cout << data;
        if (curr->next) {
            std::cout << " <=> ";
        }
    }

    std::cout << std::endl;
}

/**
 *  === Access ===
 */
template <typename T>
T& LinkedList<T>::front() {
    if (!head_) throw out_of_range("front on empty list!");
    return head_->data;
}

template <typename T>
const T& LinkedList<T>::front() const {
    if (!head_) throw std::out_of_range("front on empty list");
    return head_->data;
}

template <typename T>
T& LinkedList<T>::back() {
    if (!tail_) throw std::out_of_range("back on empty list");
    return tail_->data;
}

template <typename T>
const T& LinkedList<T>::back() const {
    if (!tail_) throw std::out_of_range("back on empty list");
    return tail_->data;
}

// === Indexing ===
template <typename T>
T& LinkedList<T>::at(std::size_t idx) {
    auto* n = node_at(idx);
    if (!n) throw std::out_of_range("at(): index out of range");
    return n->data;
}
template <typename T>
const T& LinkedList<T>::at(std::size_t idx) const {
    auto* n = node_at(idx);
    if (!n) throw std::out_of_range("at(): index out of range");
    return n->data;
}

template <typename T>
T& LinkedList<T>::operator[](std::size_t idx) {
    auto* n = node_at(idx);
    // no range‑check
    return n->data;
}
template <typename T>
const T& LinkedList<T>::operator[](std::size_t idx) const {
    return node_at(idx)->data;
}

// === Aissignment Operator ===
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs) {
    if (this != &rhs) {
        clear();
        for (Node* cur = rhs.head_; cur; cur = cur->next) append(cur->data);
    }
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& rhs) noexcept {
    if (this != &rhs) {
        // clean up current
        clear();
        // steal
        head_ = rhs.head_;
        tail_ = rhs.tail_;
        size_ = rhs.size_;
        // leave rhs empty
        rhs.head_ = rhs.tail_ = nullptr;
        rhs.size_             = 0;
    }
    return *this;
}

// === comparisons ===

template <typename T>
bool LinkedList<T>::operator==(const LinkedList& rhs) const noexcept {
    if (len() != rhs.len()) return false;

    Node* a = head_;
    Node* b = rhs.head_;

    while (a != nullptr) {
        if (a->data != b->data) return false;

        a = a->next;
        b = b->next;
    }

    return true;
}
