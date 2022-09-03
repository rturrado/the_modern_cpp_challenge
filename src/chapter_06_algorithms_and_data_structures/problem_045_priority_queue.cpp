#include "chapter_06_algorithms_and_data_structures/problem_045_priority_queue.h"
#include "chapter_06_algorithms_and_data_structures/priority_queue.h"

#include "rtc/print.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <functional>  // greater, less
#include <iostream>  // cout
#include <stdexcept>  // runtime_error
#include <vector>


void problem_45_main(std::ostream& os) {
    using tmcppc::data_structures::priority_queue;

    const std::vector<int> v{ 3, 6, 7, 2, 4, 9, 5, 1, 8, 0 };
    fmt::print(os, "v: {}\n", v);

    priority_queue<int> pq_1{ cbegin(v), cend(v) };
    fmt::print(os, "priority_queue<int> pq_1(cbegin(v), cend(v));\n");
    fmt::print(os, "\tpq_1: {}\n", pq_1);

    // Notice pq_2 won't necessarily output { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    //
    // The array representation of a heap doesn't necessarily store things in sequential order.
    // For example, inserting the items 1, 2, and 3 into a min-heap can create the array representation [1, 3, 2] or [1, 2, 3].
    // Both are valid heaps. Which one is created depends on insertion order.
    //
    // From Stack Overflow: https://stackoverflow.com/a/38365848/260313
    priority_queue<int, std::greater<int>> pq_2{ cbegin(v), cend(v) };
    fmt::print(os, "priority_queue<int, std::greater<int>> pq_2(cbegin(v), cend(v));\n");
    fmt::print(os, "\tpq_2: {}\n", pq_2);
    // priority_queue<int, std::less<int>> pq_4{ pq_1 };  // wrong: argument types are priority_queue<int, std::greater<int>>

    priority_queue<int> pq_3{};
    fmt::print(os, "priority_queue<int> pq_3();\n");
    fmt::print(os, "\tpq_3: {}\n", pq_3);

    priority_queue<int> pq_5{ std::move(pq_1) };
    fmt::print(os, "priority_queue<int> pq_5(std::move(pq_1));\n");
    fmt::print(os, "\tpq_5: {}\n", pq_5);
    // fmt::print(os, "\tpq_1: {}\n", pq_1);  // wrong: use of a moved from object

    swap(pq_5, pq_3);
    fmt::print(os, "pq_5.swap(pq_3);\n");
    fmt::print(os, "\tpq_5: {}\n", pq_5);
    fmt::print(os, "\tpq_3: {}\n", pq_3);

    pq_5.push(-20);
    fmt::print(os, "pq_5.push(-20);\n");
    fmt::print(os, "\tpq_5: {}\n", pq_5);
    pq_5.push(15);
    fmt::print(os, "pq_5.push(15);\n");
    fmt::print(os, "\tpq_5: {}\n", pq_5);

    if (not pq_5.empty()) {
        pq_5.pop();
        fmt::print(os, "pq_5.pop()\n");
        fmt::print(os, "\tpq_5: {}\n", pq_5);
    }
    if (not pq_5.empty()) {
        pq_5.pop();
        fmt::print(os, "pq_5.pop();\n");
        fmt::print(os, "\tpq_5: {}\n", pq_5);
    }
    // pq_3.pop();  // wrong: same behaviour as erase(cbegin(v)) in an empty vector

    if (not pq_5.empty()) {
        fmt::print(os, "pq_5.top(): {}\n", pq_5.top());
    }
    // fmt::print(os, "pq_3.top(): {}\n", pq_3.top());  // wrong: same behaviour as v.front() in an empty vector

    fmt::print(os, "pq_5.size(): {}\n", pq_5.size());

    fmt::print(os, "pq_3.empty(): {}\n", pq_3.empty());
    fmt::print(os, "pq_5.empty(): {}\n", pq_5.empty());

    priority_queue<int, std::greater<int>> pq_6{};
    fmt::print(os, "priority_queue<int, std::greater<int>> pq_6();\n");
    fmt::print(os, "\tpq_6: {}\n", pq_6);

    for (int i{ 9 }; i > 0; --i) {
        pq_6.push(i);
        fmt::print(os, "pq_6.push({});\n", i);
        fmt::print(os, "\tpq_6: {}\n", pq_6);
    }

    // Notice the smallest element is always the one being removed, since this is a min-heap
    while (not pq_6.empty()) {
        pq_6.pop();
        fmt::print(os, "pq_6.pop();\n");
        fmt::print(os, "\tpq_6: {}\n", pq_6);
    }
    fmt::print(os, "\n");
}


// Priority queue
//
// Write a data structure that represents a priority queue that provides constant time lookup for the largest element,
// but has logarithmic time complexity for adding and removing elements.
//
// A queue inserts new elements at the end and removes elements from the top.
//
// By default, the queue should use operator< to compare elements,
// but it should be possible for the user to provide a comparison function object
// that returns true if the first argument is less than the second.
//
// The implementation must provide at least the following operations:
//
// - push() to add a new element. This sorts the container.
// - pop() to remove the top element.
// - top() to provide access to the top element.
// - size() to indicate the number of elements in the queue.
// - empty() to indicate whether the queue is empty.
void problem_45_main() {
    problem_45_main(std::cout);
}
