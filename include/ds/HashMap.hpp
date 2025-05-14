#pragma once

#include <cstddef>
#include <functional>
#include <utility>

#include "LinkedList.hpp"
#include "Vector.hpp"

template <typename Key, typename T, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
class HashMap {
   private:
    using Pair   = std::pair<Key, T>;
    using Bucket = LinkedList<Pair>;

    Vector<Bucket> buckets_;
    std::size_t    size_ = 0;

    Hash     hasher_;
    KeyEqual key_equal_;

    static constexpr float max_load_factor = 1.0f;

    std::size_t bucket_index(const Key& key) const noexcept;

    void rehash_if_needed();
    void rehash(std::size_t new_bucket_count);

   public:
    // c-tor / d-tor
    HashMap();
    explicit HashMap(std::size_t bucket_count);
    HashMap(std::initializer_list<Pair> init);
    HashMap(const HashMap& other)     = default;
    HashMap(HashMap&& other) noexcept = default;
    ~HashMap()                        = default;

    HashMap& operator=(const HashMap& rhs)     = default;
    HashMap& operator=(HashMap&& rhs) noexcept = default;

    // modifiers
    void insert(const Key& key, const T& val);
    void insert(Key&& key, T&& val);

    // Lookup
    T&       at(const Key& key);
    const T& at(const Key& key) const;
    T&       operator[](const Key& key);

    // removal and query
    bool erase(const Key& key);
    bool contains(const Key& key) const noexcept;

    // capacity
    std::size_t size() const noexcept {
        return size_;
    }
    bool empty() const noexcept {
        return size_ == 0;
    }
    void clear() noexcept;

    std::size_t bucket_count() const noexcept {
        return buckets_.len();
    }
    float load_factor() const noexcept {
        return float(size_) / buckets_.len();
    }
};

#include "HashMap.tpp"
