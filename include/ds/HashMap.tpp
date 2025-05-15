#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "HashMap.hpp"

// c-tors

template <typename Key, typename T, typename Hash, typename KeyEqual>
HashMap<Key, T, Hash, KeyEqual>::HashMap()
    : buckets_(10), size_(0), hasher_(), key_equal_() {}

template <typename Key, typename T, typename Hash, typename KeyEqual>
HashMap<Key, T, Hash, KeyEqual>::HashMap(std::size_t bucket_count)
    : buckets_(bucket_count), size_(0), hasher_(), key_equal_() {}

template <typename Key, typename T, typename Hash, typename KeyEqual>
HashMap<Key, T, Hash, KeyEqual>::HashMap(std::initializer_list<Pair> init)
    : buckets_(init.size() * 2), size_(0), hasher_(), key_equal_() {
    for (auto& kv : init) {
        insert(kv.first, kv.second);
    }
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
HashMap<Key, T, Hash, KeyEqual>::HashMap(HashMap&& other) noexcept
    : buckets_(std::move(other.buckets_)),
      size_(other.size_),
      hasher_(std::move(other.hasher_)),
      key_equal_(std::move(other.key_equal_)) {
    other.size_ = 0;
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
HashMap<Key, T, Hash, KeyEqual>& HashMap<Key, T, Hash, KeyEqual>::operator=(
    HashMap&& other) noexcept {
    if (this != &other) {
        buckets_    = std::move(other.buckets_);
        size_       = other.size_;
        hasher_     = std::move(other.hasher_);
        key_equal_  = std::move(other.key_equal_);
        other.size_ = 0;
    }

    return *this;
}

// private functions

template <typename Key, typename T, typename Hash, typename KeyEqual>
std::size_t HashMap<Key, T, Hash, KeyEqual>::bucket_index(
    const Key& key) const noexcept {
    return hasher_(key) % buckets_.len();
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
void HashMap<Key, T, Hash, KeyEqual>::rehash_if_needed() {
    if (load_factor() > max_load_factor) {
        rehash(bucket_count() * 2);
    }
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
void HashMap<Key, T, Hash, KeyEqual>::rehash(std::size_t new_bucket_count) {
    // lets grab old bucket
    Vector<Bucket> old_buckets = std::move(buckets_);

    // make a new set of buckets
    buckets_.clear();
    buckets_.reserve(new_bucket_count);

    for (std::size_t i = 0; i < new_bucket_count; ++i) {
        buckets_.push_back(Bucket{});
    }
    size_ = 0;

    for (Bucket& bucket : old_buckets) {
        // Linked List has no iteration method

        for (std::size_t i = 0; i < bucket.len(); ++i) {
            Pair& kv = bucket[i];
            insert(std::move(kv.first), std::move(kv.second));
        }
        // for (auto& kv : bucket) {
        //     insert(std::move(kv.first), std::move(kv.second));
        // }
    }
}

// modifiers

template <typename Key, typename T, typename Hash, typename KeyEqual>
void HashMap<Key, T, Hash, KeyEqual>::insert(const Key& key, const T& val) {
    std::size_t idx = bucket_index(key);
    Bucket&     b   = buckets_[idx];

    for (std::size_t i = 0; i < b.len(); ++i) {
        Pair& kv = b.at(i);

        if (key_equal_(kv.first, key)) {
            kv.second = val;
            return;
        }
    }

    b.append({key, val});
    ++size_;

    rehash_if_needed();
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
void HashMap<Key, T, Hash, KeyEqual>::insert(Key&& key, T&& val) {
    std::size_t idx = bucket_index(key);
    Bucket&     b   = buckets_[idx];

    for (std::size_t i = 0; i < b.len(); ++i) {
        Pair& kv = b.at(i);

        if (key_equal_(kv.first, key)) {
            kv.second = std::move(val);
            return;
        }
    }

    b.append({key, val});
    ++size_;

    rehash_if_needed();
}

// Lookup

template <typename Key, typename T, typename Hash, typename KeyEqual>
T& HashMap<Key, T, Hash, KeyEqual>::at(const Key& key) {
    std::size_t idx = bucket_index(key);
    Bucket&     b   = buckets_[idx];

    for (std::size_t i = 0; i < b.len(); ++i) {
        Pair& kv = b.at(i);

        if (key_equal_(kv.first, key)) {
            return kv.second;
        }
    }

    throw std::out_of_range("[HashMap::at()] Key does not exist!");
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
const T& HashMap<Key, T, Hash, KeyEqual>::at(const Key& key) const {
    std::size_t   idx = bucket_index(key);
    const Bucket& b   = buckets_[idx];

    for (std::size_t i = 0; i < b.len(); ++i) {
        const Pair& kv = b.at(i);

        if (key_equal_(kv.first, key)) {
            return kv.second;
        }
    }

    throw std::out_of_range("[HashMap::at()] Key does not exist!");
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
T& HashMap<Key, T, Hash, KeyEqual>::operator[](const Key& key) {
    std::size_t idx = bucket_index(key);
    Bucket&     b   = buckets_[idx];

    for (std::size_t i = 0; i < b.len(); ++i) {
        Pair& kv = b[i];
        if (key_equal_(kv.first, key)) {
            return kv.second;
        }
    }

    // just insert if key doesnt exist!
    b.append({key, T()});
    ++size_;
    rehash_if_needed();

    // return the new element
    return b.back().second;
}

// removal and query

template <typename Key, typename T, typename Hash, typename KeyEqual>
bool HashMap<Key, T, Hash, KeyEqual>::erase(const Key& key) {
    std::size_t idx = bucket_index(key);
    Bucket&     b   = buckets_[idx];

    for (std::size_t i = 0; i < b.len(); ++i) {
        Pair& kv = b[i];
        if (key_equal_(kv.first, key)) {
            // remove node and update size
            b.del(i);
            --size_;
            return true;
        }
    }

    return false;
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
bool HashMap<Key, T, Hash, KeyEqual>::contains(const Key& key) const noexcept {
    std::size_t   idx = bucket_index(key);
    const Bucket& b   = buckets_[idx];

    for (std::size_t i = 0; i < b.len(); ++i) {
        const Pair& kv = b[i];

        if (key_equal_(kv.first, key)) {
            return true;
        }
    }

    return false;
}

// capacity

template <typename Key, typename T, typename Hash, typename KeyEqual>
void HashMap<Key, T, Hash, KeyEqual>::clear() noexcept {
    for (Bucket& b : buckets_) {
        b.clear();
    }
    size_ = 0;
}

// utils

template <typename Key, typename T, typename Hash, typename KeyEqual>
std::ostream& operator<<(std::ostream&                          os,
                         const HashMap<Key, T, Hash, KeyEqual>& m) {
    os << "{";
    bool first = true;
    for (std::size_t bi = 0; bi < m.bucket_count(); ++bi) {
        const auto& bucket = m.buckets_[bi];
        for (std::size_t i = 0; i < bucket.len(); ++i) {
            const auto& kv = bucket[i];

            if (!first) os << ", ";
            first = false;
            os << "\"" << kv.first << "\": " << kv.second;
        }
    }

    os << "}";
    return os;
}
