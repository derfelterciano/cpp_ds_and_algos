#pragma once

#include <cstddef>
#include <initializer_list>

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

    for (auto& bucket : old_buckets) {
        for (auto& kv : bucket) {
            insert(std::move(kv.first), std::move(kv.second));
        }
    }
}

// modifiers

template <typename Key, typename T, typename Hash, typename KeyEqual>
void HashMap<Key, T, Hash, KeyEqual>::insert(const Key& key, const T& val) {}

template <typename Key, typename T, typename Hash, typename KeyEqual>
void HashMap<Key, T, Hash, KeyEqual>::insert(Key&& key, T&& val) {}

// Lookup

template <typename Key, typename T, typename Hash, typename KeyEqual>
T& HashMap<Key, T, Hash, KeyEqual>::at(const Key& key) {}

template <typename Key, typename T, typename Hash, typename KeyEqual>
const T& HashMap<Key, T, Hash, KeyEqual>::at(const Key& key) const {}

template <typename Key, typename T, typename Hash, typename KeyEqual>
T& HashMap<Key, T, Hash, KeyEqual>::operator[](const Key& key) {}

// removal and query

template <typename Key, typename T, typename Hash, typename KeyEqual>
bool HashMap<Key, T, Hash, KeyEqual>::erase(const Key& key) {}

template <typename Key, typename T, typename Hash, typename KeyEqual>
bool HashMap<Key, T, Hash, KeyEqual>::contains(const Key& key) const noexcept {}

// capacity

template <typename Key, typename T, typename Hash, typename KeyEqual>
void HashMap<Key, T, Hash, KeyEqual>::clear() noexcept {}
