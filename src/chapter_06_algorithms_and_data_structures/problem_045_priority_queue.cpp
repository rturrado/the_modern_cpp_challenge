#include "Chapter6_AlgorithmsAndDataStructures.h"
#include "Chapter6_AlgorithmsAndDataStructures/PriorityQueue.h"
#include "RtcPrint.h"

#include <ios>  // boolalpha
#include <functional>  // greater, less
#include <iostream>  // cout
#include <vector>

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
void problem_45_main()
{
    const std::vector<int> v{ 3, 6, 7, 2, 4, 9, 5, 1, 8, 0 };
    std::cout << "v: " << v << "\n\n";
    
    PriorityQueue<int> pq_1{ cbegin(v), cend(v) };
    std::cout << "PriorityQueue<int> pq_1{ cbegin(v), cend(v) };\n";
    std::cout << "\tpq_1: " << pq_1 << "\n\n";
    
    // Notice pq_2 won't necessarily output { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    //
    // The array representation of a heap doesn't necessarily store things in sequential order.
    // For example, inserting the items 1, 2, and 3 into a min-heap can create the array representation [1, 3, 2] or [1, 2, 3].
    // Both are valid heaps. Which one is created depends on insertion order.
    //
    // From Stack Overflow: https://stackoverflow.com/a/38365848/260313
    PriorityQueue<int, std::greater<int>> pq_2{ cbegin(v), cend(v) };
    std::cout << "PriorityQueue<int, std::greater<int>> pq_2{ cbegin(v), cend(v) };\n";
    std::cout << "\tpq_2: " << pq_2 << "\n\n";
    // PriorityQueue<int, std::less<int>> pq_4{ pq_1 };  // wrong: argument types are PriorityQueue<int, std::greater<int>>

    PriorityQueue<int> pq_3{};
    std::cout << "PriorityQueue<int> pq_3{};\n";
    std::cout << "\tpq_3: " << pq_3 << "\n\n";

    PriorityQueue<int> pq_5{ std::move(pq_1) };
    std::cout << "PriorityQueue<int> pq_5{ std::move(pq_1) }; pq_5: " << pq_5 << "\n\n";
    // std::cout << pq_1 << "\n";  // wrong: use of a moved from object

    swap(pq_5, pq_3);
    std::cout << "pq_5.swap(pq_3);\n";
    std::cout << "\tpq_5: " << pq_5 << "\n";
    std::cout << "\tpq_3: " << pq_3 << "\n\n";

    pq_5.push(-20);
    std::cout << "pq_5.push(-20); pq_5: " << pq_5 << "\n";
    pq_5.push(15);
    std::cout << "pq_5.push(15); pq_5: " << pq_5 << "\n\n";

    if (not pq_5.empty()) { pq_5.pop(); std::cout << "pq_5.pop(); pq_5: " << pq_5 << "\n"; }
    if (not pq_5.empty()) { pq_5.pop(); std::cout << "pq_5.pop(); pq_5: " << pq_5 << "\n\n"; }
    // pq_3.pop();  // wrong: same behaviour as erase(cbegin(v)) in an empty vector

    if (not pq_5.empty()) { std::cout << "pq_5.top(): " << pq_5.top() << "\n\n"; }
    // std::cout << "pq_3.top(): " << pq_3.top() << "\n";  // wrong: same behaviour as v.front() in an empty vector
    
    std::cout << "pq_5.size(): " << pq_5.size() << "\n\n";

    std::cout << std::boolalpha << "pq_3.empty(): " << pq_3.empty() << "\n";
    std::cout << std::boolalpha << "pq_5.empty(): " << pq_5.empty() << "\n\n";

    PriorityQueue<int, std::greater<int>> pq_6{};
    std::cout << "PriorityQueue<int, std::greater<int>> pq_6{};\n";
    std::cout << "\tpq_6: " << pq_6 << "\n\n";

    for (int i{ 9 }; i > 0; --i)
    {
        pq_6.push(i);
        std::cout << "pq_6.push(" << i << "); pq_6: " << pq_6 << "\n";
    }
    std::cout << "\n";

    // Notice the smallest element is always the one being removed, since this is a min-heap
    while (not pq_6.empty())
    {
        pq_6.pop();
        std::cout << "pq_6.pop(); pq_6: " << pq_6 << "\n";
    }
    std::cout << "\n";
}
