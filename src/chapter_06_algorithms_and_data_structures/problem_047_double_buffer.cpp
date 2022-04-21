#include "Chapter6_AlgorithmsAndDataStructures.h"
#include "Chapter6_AlgorithmsAndDataStructures/DoubleBuffer.h"
#include "RtcPrint.h"

#include <algorithm>  // for_each
#include <chrono>
#include <iostream>  // cout
#include <numeric>  // iota
#include <thread>  // this_thread
#include <vector>

// This test shows that, if we don't update the full buffer on every write operation, we'll get unexpected results
// This is due to the the fact that the double buffering technique swaps the read and write buffers after every write
//
// For example, the output for the test below may be:
// (thread 1 writing) w_1 w_2 w_3 w_4 w_5 (thread 2 reading) r_1 w_6 r_2 w_7 r_3 w_8 r_4 w_9 r_5 w_10 r_6 r_0 r_8 r_0 r_10
//
// Thread 2 happens to read entries 1 to 6, and 8 and 10 from the same buffer where thread 1 wrote them to
// However, it doesn't read entries 7 and 9 from the buffer where they were written to, so it just reads zeroes
//
// Buffer w: 0 0 0 0 0 0 0 0 0 0   // initial state
// Buffer r: 0 0 0 0 0 0 0 0 0 0
//
// Buffer w: 1 0 0 0 0 0 0 0 0 0   // write 1
// Buffer r: 0 0 0 0 0 0 0 0 0 0
//
// Buffer w: 0 0 0 0 0 0 0 0 0 0   // swap buffers
// Buffer r: 1 0 0 0 0 0 0 0 0 0
//
// Buffer w: 1 0 0 0 0 0 0 0 0 0   // write 2, swap buffers
// Buffer r: 0 2 0 0 0 0 0 0 0 0
//
// Buffer w: 0 2 0 4 0 0 0 0 0 0   // ... until after write 5, swap buffers; at this point we read 1
// Buffer r: 1 0 3 0 5 0 0 0 0 0
//
// Buffer w: 1 0 3 0 5 0 0 0 0 0   // write 6, swap buffers, read 2
// Buffer r: 0 2 0 4 0 6 0 0 0 0
//
// Buffer w: 1 0 3 0 5 0 7 0 9 0   // ... write 10, swap buffers, read 6, 0, 8, 0 and 10
// Buffer r: 0 2 0 4 0 6 0 8 0 10
void test_1()
{
    using namespace std::chrono_literals;

    // We work over a double buffer of 10 elements, initially set to 0
    DoubleBuffer<int> db{ 10 };

    // Thread 1 writes every 100ms
    // It writes a sequence of numbers starting from 1
    auto thread_1_l = [&db]() {
        std::cout << " (thread 1 writing)";
        for (auto i{ 0 }; i < db.size(); ++i)
        {
            db.write(i, i + 1);
            std::cout << " w_" << i + 1;
            std::this_thread::sleep_for(100ms);
        }
    };
    // Thread 2 reads every 100ms
    auto thread_2_l = [&db]() {
        std::cout << " (thread 2 reading)";
        for (auto i{ 0 }; i < db.size(); ++i)
        {
            std::cout << " r_" << db.read(i);
            std::this_thread::sleep_for(100ms);
        }
    };

    // Thread 2 starts 500ms after thread 1
    // Initial thoughts are it should read something like { 1, 2, 3, ..., n-1, n, 0, 0, ..., 0 }. But it doesn't
    std::thread thread_1{ thread_1_l };
    std::this_thread::sleep_for(500ms);
    std::thread thread_2{ thread_2_l };

    thread_1.join();
    thread_2.join();

    std::cout << "\n\n";
}

// Book's example
// There's no problem here as write operations update the full buffer
void test_2()
{
    using namespace std::chrono_literals;

    DoubleBuffer<int> db{ 10 };

    // Thread 1 writes the full buffer 10 times, every 100ms
    // First time, it writes a sequence of numbers from 0 to 9
    // Every successive time it adds 10 to the the sequence of numbers
    auto thread_1_l = [&db]() {
        std::vector<int> v(db.size());
        std::iota(begin(v), end(v), 0);
        for (auto i{ 0 }; i < 10; ++i)
        {
            db.write(0, v);
            std::this_thread::sleep_for(100ms);
            std::for_each(begin(v), end(v), [](auto& n) { n += 10; });
        }
    };

    // Thread 2 reads and prints the full buffer 10 times, every 150ms
    auto thread_2_l = [&db]() {
        std::vector<int> v(db.size());
        for (auto i{ 0 }; i < 10; ++i)
        {
            v = db.read(0, v.size());
            std::cout << v << "\n";
            std::this_thread::sleep_for(150ms);
        }
        std::cout << "\n";
    };

    // Thread 2 starts 50ms after thread 1
    std::thread thread_1{ thread_1_l };
    std::this_thread::sleep_for(50ms);
    std::thread thread_2{ thread_2_l };

    thread_1.join();
    thread_2.join();
}

// Double buffer
//
// Write a class that represents a buffer that could be written and read at the same time
// without the two operations colliding.
// A read operation must provide access to the old data while a write operation is in progress.
// Newly written data must be available for reading upon completion of the write operation.
void problem_47_main()
{
    test_1();
    test_2();
}
