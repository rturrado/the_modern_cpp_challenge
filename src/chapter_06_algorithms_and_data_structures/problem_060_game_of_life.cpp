#include "chapter_06_algorithms_and_data_structures/console.h"
#include "chapter_06_algorithms_and_data_structures/problem_060_game_of_life.h"
#include "chapter_06_algorithms_and_data_structures/timer.h"

#include <chrono>
#include <fmt/ostream.h>
#include <future>  // async
#include <iostream>  // cout
#include <thread>  // sleep_for

using namespace tmcppc::chrono;
using namespace tmcppc::game_of_life;
using namespace tmcppc::system;


void problem_60_main(std::ostream& os, const console& console, const timer& timer, std::chrono::duration<double> timeout) {
    // Initialize stop game flag
    stop_game = false;

    // Start game of life asynchronously
    auto fut_game = std::async(std::launch::async, [&os, &console, &timer]() {
        game_of_life{ os, console, timer }.run();
    });
    // Wait for timeout and stop game
    auto fut_timeout = std::async(std::launch::async, [&timeout]() {
        std::this_thread::sleep_for(timeout);
        stop_game = true;
    });

    // Wait for game of life to finish gracefully
    fut_game.get();
    fut_timeout.get();

    fmt::print(os, "\n");
}


// The Game of Life
//
// Write a program that implements the Game of Life cellular automaton proposed by John Horton Conway.
// The universe of this game is a grid of square cells that could have one of two states: dead or alive.
// Every cell interacts with its adjacent neighbors, with the following transactions occurring on every step:
//
// - Any live cell with fewer than two live neighbors dies, as if caused by underpopulation.
// - Any live cell with two or three live neighbors lives on to the next generation.
// - Any live cell with more than three live neighbors dies, as if by overpopulation.
// - Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
//
// The status of the game on each iteration should be displayed to the console,
// and for convenience, you should pick a reasonable size, such as 20 rows x 50 columns.
void problem_60_main() {
    using namespace std::chrono_literals;

    problem_60_main(
        std::cout
        , console{ std::make_unique<console_impl>() }
        , timer{ std::make_unique<timer_impl>() }
        , 5s
    );
}
