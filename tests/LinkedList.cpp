#include "../headers/LinkedList.hpp"

#include <iostream>

int main() {
    LinkedList<int> L{
        1,
        2,
        3,
    };
    L.prepend(0);
    L.append(20);

    // test that copy & move ctors compile
    LinkedList<int> C = L;             // copy
    LinkedList<int> M = std::move(L);  // move

    (void)C;
    (void)M;  // silence “unused variable” warnings

    return 0;
}
