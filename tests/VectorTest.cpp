#include <cassert>
#include <iostream>
#include <ostream>

#include "ds/Vector.hpp"

int main() {
    using ds::Vector;

    // constructor
    Vector<int> v;
    assert(v.is_empty());
    assert(v.len() == 0);
    assert(v.capacity() == 0);

    // reserve
    v.reserve(8);
    assert(v.len() == 0);
    assert(v.capacity() >= 8);

    // push
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    assert(!v.is_empty());
    assert(v.len() == 3);
    assert(v[0] == 10 && v[1] == 20 && v[2] == 30);
    assert(v.at(1) == 20);
    assert(v.front() == 10);
    assert(v.back() == 30);
    std::cout << v.debug_vec() << std::endl;

    // pop
    int x = v.pop_back();
    assert(x == 30);
    assert(v.len() == 2);
    assert(v.back() == 20);

    // init list
    Vector<int> v2 = {1, 2, 3, 4};
    assert(v2.len() == 4);
    assert(v2.capacity() >= 4);
    for (std::size_t i = 0; i < v2.len(); ++i) {
        assert(v2[i] == static_cast<int>(i + 1));
    }
    std::cout << v2.debug_vec() << std::endl;

    // fill constructor
    Vector<int> v3(5, 7);
    assert(v3.len() == 5);
    for (std::size_t i = 0; i < v3.len(); ++i) {
        assert(v3[i] == 7);
    }
    std::cout << v3.debug_vec() << std::endl;

    // clear
    v2.clear();
    assert(v2.is_empty());
    assert(v2.len() == 0);
    // capacity remains unchanged
    assert(v2.capacity() >= 4);
    std::cout << v2.debug_vec() << std::endl;

    // shrink
    v2.shrink_fit();
    assert(v2.capacity() == v2.len());

    // copy ctor
    Vector<int> v4{5, 6, 7};
    Vector<int> v5 = v4;
    assert(v5 == v4);
    assert(!(v5 != v4));

    // move constructor & move assignment
    Vector<int> v6 = std::move(v5);
    assert(v6.len() == 3);
    assert(v5.is_empty());

    Vector<int> v7;
    v7 = std::move(v6);
    assert(v7.len() == 3);
    assert(v6.is_empty());

    // iterators + range‑based for
    Vector<std::string> vs{"foo", "bar", "baz"};
    std::string         concat;
    for (auto it = vs.begin(); it != vs.end(); ++it) {
        concat += *it + ";";
    }
    for (auto val : vs) {
        std::cout << val << std::endl;
    }

    assert(concat == "foo;bar;baz;");

    concat.clear();
    for (auto& s : vs) {
        concat += s + "-";
    }
    assert(concat == "foo-bar-baz-");

    // debug_vec()
    Vector<int> v8{9, 8, 7};
    assert(v8.debug_vec() == "[9, 8, 7]");

    // exception safety
    bool threw = false;
    try {
        v8.at(100);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    threw = false;
    Vector<int> v9;
    try {
        v9.pop_back();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    Vector<int> v10 = {1, 2, 3, 4, 5};
    v10.push_back(11);
    std::cout << v10.debug_vec() << std::endl;

    Vector<Vector<int>> v11 = {{10}, {20, 30}};

    std::cout << v11 << std::endl;

    std::cout << "All Vector tests passed!\n";

    return 0;
}
