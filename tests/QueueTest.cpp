#include <cassert>
#include <iostream>
#include <string>

#include "ds/Queue.hpp"

int main() {
    using ds::Queue;
    // — Default construction, is_empty(), len() —
    Queue<int> qi;
    assert(qi.is_empty());
    assert(qi.len() == 0);

    // — enqueue, front, dequeue —
    qi.enqueue(1);
    qi.enqueue(2);
    qi.enqueue(3);
    assert(!qi.is_empty());
    assert(qi.len() == 3);
    assert(qi.front() == 1);
    int x = qi.dequeue();
    assert(x == 1);
    assert(qi.len() == 2);

    // — initializer_list ctor —
    Queue<int> qi2{4, 5, 6};
    assert(qi2.len() == 3);
    assert(qi2.front() == 4);

    // — FIFO order —
    qi2.enqueue(7);  // [4,5,6,7]
    assert(qi2.dequeue() == 4);
    assert(qi2.dequeue() == 5);
    assert(qi2.dequeue() == 6);
    assert(qi2.dequeue() == 7);
    assert(qi2.is_empty());

    // — clear() —
    qi2 = {8, 9, 10};
    assert(!qi2.is_empty());
    qi2.clear();
    assert(qi2.is_empty());
    assert(qi2.len() == 0);

    // — comparison operators == / != —
    Queue<std::string> qs1{"a", "b", "c"};
    Queue<std::string> qs2{"a", "b", "c"};
    Queue<std::string> qs3{"x", "y"};
    assert(qs1 == qs2);
    assert(!(qs1 != qs2));
    assert(qs1 != qs3);

    // — copy and move semantics —
    Queue<int> a{11, 12, 13};
    Queue<int> b = a;  // copy
    assert(b == a);
    Queue<int> c = std::move(a);  // move
    assert(c.len() == 3);
    assert(a.is_empty());

    std::cout << "All Queue tests passed!\n";

    return 0;
}
