#include <cassert>
#include <cstddef>
#include <ds/UnionFind.hpp>
#include <iostream>

int main() {
    using std::size_t;

    // create 5 singleton sets
    UnionFind<> uf(5);

    for (size_t i = 0; i < 5; ++i) {
        assert(uf.find(i) == i);
        assert(uf.connected(i, i));
    }

    // 2) Initially no two different elements are connected
    assert(!uf.connected(0, 1));
    assert(!uf.connected(2, 4));

    // 3) unite(0,1) merges the sets containing 0 and 1
    bool merged01 = uf.unite(0, 1);
    assert(merged01);  // they were separate
    assert(uf.connected(0, 1));
    assert(uf.find(0) == uf.find(1));

    // 4) unite(0,1) again should do nothing and return false
    bool mergedAgain = uf.unite(0, 1);
    assert(!mergedAgain);

    // 5) Build a larger component: unite(1,2)
    assert(uf.unite(1, 2));
    assert(uf.connected(0, 2));
    assert(uf.find(2) == uf.find(0));

    // 6) Another separate pair: unite(3,4)
    assert(uf.unite(3, 4));
    assert(uf.connected(3, 4));
    assert(!uf.connected(0, 3));

    // 7) Merge the two components: unite(2,4)
    assert(uf.unite(2, 4));
    for (size_t i = 0; i < 5; ++i) {
        // Now all 0–4 should be in one set
        assert(uf.connected(0, i));
        assert(uf.connected(i, 4));
    }

    // 8) Test with a different integral Index type
    UnionFind<int> uf_int(3);
    assert(uf_int.find(1) == 1);
    assert(uf_int.unite(0, 2));
    assert(uf_int.connected(0, 2));
    assert(!uf_int.connected(1, 2));

    std::cout << "All UnionFind tests passed!\n";

    return 0;
}
