#include <cassert>
#include <ds/PriorityQueue.hpp>
#include <functional>
#include <iostream>

int main() {
    using ds::PriorityQueue;
    using ds::Vector;

    // 1) empty() / size() / exceptions
    PriorityQueue<int> pq;
    assert(pq.empty());
    assert(pq.size() == 0);
    try {
        pq.top();
        assert(false && "top() on empty did not throw");
    } catch (const std::out_of_range&) {
    }
    try {
        pq.pop();
        assert(false && "pop() on empty did not throw");
    } catch (const std::out_of_range&) {
    }

    // 2) push & pop (min-heap by default)
    pq.push(5);
    pq.push(2);
    pq.push(8);
    assert(!pq.empty());
    assert(pq.size() == 3);
    assert(pq.top() == 2);
    assert(pq.pop() == 2);
    assert(pq.pop() == 5);
    assert(pq.pop() == 8);
    assert(pq.empty());

    // 3) initializer-list constructor + pop ordering
    PriorityQueue<int> pq2{7, 3, 9, 1};
    assert(pq2.size() == 4);
    assert(pq2.pop() == 1);
    assert(pq2.pop() == 3);
    assert(pq2.pop() == 7);
    assert(pq2.pop() == 9);
    assert(pq2.empty());

    // 4) rvalue push overload
    int x = 4;
    pq.push(x);
    pq.push(1);
    pq.push(3);
    assert(pq.pop() == 1);
    assert(pq.pop() == 3);
    assert(pq.pop() == 4);
    assert(pq.empty());

    // 5) clear()
    pq.push(10);
    pq.push(20);
    pq.clear();
    assert(pq.empty());

    // 6) max-heap via comparator
    PriorityQueue<int, std::greater<int>> maxpq{
        std::initializer_list<int>{5, 2, 8, 6}};
    assert(maxpq.size() == 4);
    assert(maxpq.top() == 8);
    assert(maxpq.pop() == 8);
    assert(maxpq.pop() == 6);
    assert(maxpq.pop() == 5);
    assert(maxpq.pop() == 2);
    assert(maxpq.empty());

    PriorityQueue<int> pq3 = {10, 3, 5, 25, 1, 3, 8, 7, 6, 4};
    Vector<int>        out_vec;

    while (!pq3.empty()) {
        out_vec.push_back(pq3.pop());
    }
    std::cout << out_vec << std::endl;

    std::cout << "All PriorityQueue tests passed!\n";
    return 0;
}
