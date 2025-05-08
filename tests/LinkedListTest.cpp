// main.cpp
#include <cassert>
#include <iostream>
#include <string>

#include "../include/ds/LinkedList.hpp"

int main() {
    using std::cout;
    using std::endl;
    // ——————————————————————————————————————————————————————————————
    // Default‑ctor, is_empty(), len()
    LinkedList<int> li;
    assert(li.is_empty());
    assert(li.len() == 0);

    // ——————————————————————————————————————————————————————————————
    // append(), front(), back(), pop_back()
    li.append(10);
    li.append(20);
    li.append(30);
    assert(!li.is_empty());
    assert(li.len() == 3);
    assert(li.front() == 10);
    assert(li.back() == 30);
    int x = li.pop_back();
    assert(x == 30);
    assert(li.len() == 2);

    // ——————————————————————————————————————————————————————————————
    // prepend(), pop_front()
    li.prepend(5);
    li.prepend(1);
    assert(li.len() == 4);
    assert(li.front() == 1);
    assert(li.back() == 20);
    x = li.pop_front();
    assert(x == 1);
    assert(li.len() == 3);

    // ——————————————————————————————————————————————————————————————
    // at(), operator[]
    // List is now [5,10,20]
    assert(li.at(0) == 5);
    assert(li[1] == 10);
    li[1] = 15;
    assert(li.at(1) == 15);

    // ——————————————————————————————————————————————————————————————
    // insert()
    li.clear();
    li.insert(0, 100);  // [100]
    li.insert(1, 200);  // [100,200]
    li.insert(1, 150);  // [100,150,200]
    assert(li.len() == 3);
    assert(li.at(1) == 150);
    li.insert(5, 250);  // idx>len ⇒ append ⇒ [100,150,200,250]
    assert(li.back() == 250);

    // ——————————————————————————————————————————————————————————————
    // del()
    // [100,150,200,250]
    li.del(0);  // [150,200,250]
    assert(li.front() == 150);
    li.del(li.len() - 1);  // [150,200]
    assert(li.back() == 200);
    li.del(1);  // [150]
    assert(li.len() == 1 && li.front() == 150);

    // ——————————————————————————————————————————————————————————————
    // remove()
    li.append(150);  // [150,150]
    size_t removed = li.remove(150);
    assert(removed == 2 && li.is_empty());

    // ——————————————————————————————————————————————————————————————
    // contains(), clear()
    li = LinkedList<int>{1, 2, 3, 4};
    assert(li.contains(3));
    li.clear();
    assert(li.is_empty());

    // ——————————————————————————————————————————————————————————————
    // reverse()
    li = LinkedList<int>{10, 20, 30};
    li.reverse();  // [30,20,10]
    assert(li.front() == 30 && li.back() == 10);

    // ——————————————————————————————————————————————————————————————
    // copy‑ctor, move‑ctor, copy‑assign, move‑assign
    LinkedList<int> copy(li);
    assert(copy.len() == li.len() && copy.front() == li.front());
    LinkedList<int> moved(std::move(copy));
    assert(copy.is_empty() && moved.len() == 3);

    LinkedList<int> assign;
    assign = li;
    assert(assign.len() == li.len());
    LinkedList<int> massign;
    massign = std::move(assign);
    assert(assign.is_empty() && massign.len() == 3);

    // ——————————————————————————————————————————————————————————————
    // print()
    cout << "Final int list: ";
    li.print();  // should print: 30 <=> 20 <=> 10

    // ——————————————————————————————————————————————————————————————
    // Test with another type
    LinkedList<std::string> ls{"foo", "bar", "baz"};
    assert(ls.len() == 3);
    assert(ls.front() == "foo" && ls.back() == "baz");
    ls.reverse();  // [baz,bar,foo]
    cout << "String list: ";
    ls.print();

    cout << "All tests passed!\n";
    return 0;
}
