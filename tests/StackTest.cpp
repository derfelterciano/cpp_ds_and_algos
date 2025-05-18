#include <cassert>

#include "ds/Stack.hpp"

int main() {
    using ds::Stack;

    // — Default construction, is_empty(), len() —
    Stack<int> si;
    assert(si.is_empty());
    assert(si.len() == 0);

    // — push, top, pop —
    si.push(42);
    assert(!si.is_empty());
    assert(si.len() == 1);
    assert(si.top() == 42);
    int x = si.pop();
    assert(x == 42);
    assert(si.is_empty());

    // — initializer_list ctor —
    Stack<int> si2{1, 2, 3};
    assert(si2.len() == 3);
    assert(si2.top() == 3);

    // — LIFO order —
    si2.push(4);             // [1,2,3,4]
    assert(si2.pop() == 4);  // back to [1,2,3]
    assert(si2.pop() == 3);
    assert(si2.pop() == 2);
    assert(si2.pop() == 1);
    assert(si2.is_empty());

    // — clear() —
    si2 = {10, 20, 30};
    assert(!si2.is_empty());
    si2.clear();
    assert(si2.is_empty());
    assert(si2.len() == 0);

    // — comparison operators ==
    Stack<std::string> ss1{"a", "b", "c"};
    Stack<std::string> ss2{"a", "b", "c"};
    Stack<std::string> ss3{"a", "b"};
    assert(ss1 == ss2);
    assert(!(ss1 != ss2));
    assert(ss1 != ss3);

    // — copy and move semantics —
    Stack<int> a{5, 6, 7};
    Stack<int> b = a;  // copy
    assert(b == a);
    Stack<int> c = std::move(a);  // move
    assert(c.len() == 3);
    assert(a.is_empty());

    std::cout << "All Stack tests passed!\n";
    return 0;
}
