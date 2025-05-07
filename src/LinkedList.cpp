#include "../headers/LinkedList.hpp"

#include <initializer_list>
#include <iostream>
#include <utility>

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
    Node* newNode = new Node(move(val));

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
