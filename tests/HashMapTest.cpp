#include <cassert>
#include <ds/HashMap.hpp>
#include <string>

int main() {
    // Default map
    HashMap<std::string, int> h1;
    assert(h1.empty());
    assert(h1.size() == 0);

    // insert, contains, at
    h1.insert("one", 1);
    h1.insert("two", 2);
    assert(!h1.empty());
    assert(h1.size() == 2);
    assert(h1.contains("one"));
    assert(h1.contains("two"));
    assert(h1.at("one") == 1);
    assert(h1.at("two") == 2);
    std::cout << h1 << std::endl;

    // overwrite
    h1.insert("one", 11);
    assert(h1.size() == 2);
    assert(h1.at("one") == 11);
    h1.insert("one", 1);
    std::cout << h1 << std::endl;

    // operator[]
    assert(h1["two"] == 2);
    h1["two"] = 22;
    assert(h1["two"] == 22);
    h1["two"] = 2;

    h1["three"] = 3;
    assert(h1.size() == 3);
    assert(h1.at("three") == 3);
    std::cout << h1 << std::endl;

    // erase
    assert(h1.erase("two"));
    assert(!h1.contains("two"));
    assert(h1.size() == 2);
    assert(!h1.erase("twenty"));
    assert(h1.size() == 2);
    std::cout << h1 << std::endl;

    // throwing
    bool threw = false;
    try {
        h1.at("hundred");
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);
    std::cout << h1 << std::endl;

    HashMap<int, int> m2{{10, 100}, {20, 200}, {30, 300}};
    assert(m2.size() == 3);
    assert(m2.at(10) == 100);
    assert(m2.at(20) == 200);
    assert(m2.at(30) == 300);

    // 9) clear
    m2.clear();
    assert(m2.empty());
    assert(m2.size() == 0);

    // 10) load factor & rehash growth
    HashMap<int, int> mh(2);
    mh.insert(1, 1);
    mh.insert(2, 4);
    std::size_t bc_before = mh.bucket_count();
    mh.insert(3, 9);  // should trigger rehash (load_factor > 1.0)
    assert(mh.bucket_count() >= bc_before * 2);
    for (int i = 1; i <= 3; ++i) {
        assert(mh.contains(i));
        assert(mh.at(i) == i * i);
    }

    // 11) copy constructor
    HashMap<int, int> mh_copy = mh;
    assert(mh_copy.size() == mh.size());
    for (int i = 1; i <= 3; ++i) {
        assert(mh_copy.at(i) == mh.at(i));
    }

    // 12) move constructor
    HashMap<int, int> mh_moved = std::move(mh_copy);
    assert(mh_moved.size() == 3);
    for (int i = 1; i <= 3; ++i) {
        assert(mh_moved.at(i) == i * i);
    }
    assert(mh_copy.empty());  // moved‑from map should be empty or size()==0

    // 13) move assignment
    HashMap<int, int> mh_assign;
    mh_assign = std::move(mh_moved);
    assert(mh_assign.size() == 3);
    for (int i = 1; i <= 3; ++i) {
        assert(mh_assign.contains(i));
        assert(mh_assign.at(i) == i * i);
    }

    std::cout << "All HashMap tests passed!\n";

    return 0;
}
