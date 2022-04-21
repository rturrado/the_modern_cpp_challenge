#include "Chapter6_AlgorithmsAndDataStructures.h"
#include "RtcRandom.h"

#include <algorithm>  // for_each
#include <atomic>
#if defined _WIN32
#include <conio.h>  // _getch
#endif
#include <chrono>
#include <cstdlib>  // system
#include <future>  // async
#include <iostream>  // cout
#include <thread>  // this_thread
#include <vector>

std::atomic<bool> stop_game{ false };

void clear_screen()
{
#if defined _WIN32
    std::system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    std::system("clear");
#elif defined (__APPLE__)
    std::system("clear");
#endif
}

void wait_for_key_pressed()
{
#if defined _WIN32
    [[maybe_unused]] int i = _getch();
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    std::system("read");
#elif defined (__APPLE__)
    std::system("read");
#endif
}

enum class CellState { Dead, Alive };

class Cell
{
public:
    Cell() : state_{ CellState::Dead } { }

    [[nodiscard]] bool is_dead() const noexcept { return state_ == CellState::Dead; }
    [[nodiscard]] bool is_alive() const noexcept { return state_ == CellState::Alive; }

    void set_dead() { set_state(CellState::Dead); }
    void set_alive() { set_state(CellState::Alive); }

    // Set 90% of probability for a dead cell, 10% for an alive cell
    void set_random_state()
    {
        static rtc::random::RandomInt random_int_{ 0, 9 };
        state_ = random_int_() < 9 ? CellState::Dead : CellState::Alive;
    }

private:
    CellState state_{ CellState::Dead };

    [[nodiscard]] CellState get_state() const noexcept { return state_; }
    void set_state(const CellState& state) noexcept { state_ = state; }
};

class GameOfLife
{
    using Grid = std::vector<std::vector<Cell>>;

public:
    // Fill grid randomly
    GameOfLife(size_t rows = 20, size_t columns = 50)
        : rows_{ rows }, columns_{ columns }, data_{ std::vector(rows, std::vector(columns, Cell{})) }
    {
        std::for_each(std::begin(data_), std::end(data_), [](auto& row) {
            std::for_each(std::begin(row), std::end(row), [](auto& cell) {
                cell.set_random_state();
                });
            });
    }

    void run() {
        while (not stop_game)
        {
            using namespace std::chrono_literals;

            step();
            display();
            std::this_thread::sleep_for(200ms);
        }
    }

    // Print grid
    void display()
    {
        clear_screen();

        std::cout << "Press any key to finish.\n\n";

        std::for_each(std::cbegin(data_), std::cend(data_), [](const auto& row) {
            std::for_each(std::cbegin(row), std::cend(row), [](const auto& cell) {
                std::cout << (cell.is_alive() ? static_cast<char>(254) : ' ');
                });
            std::cout << "\n";
            });
    }

private:
    size_t rows_{ 20 };
    size_t columns_{ 50 };
    Grid data_{};

    size_t count_live_cell_neighbours(int i, int j)
    {
        size_t ret{ 0 };
        for (int ii{ i - 1 }; ii <= i + 1; ++ii)
        {
            if (ii < 0 or ii >= data_.size()) { continue; }

            auto& row{ data_[ii] };
            
            for (int jj{ j - 1 }; jj <= j + 1; ++jj)
            {
                if (jj < 0 or jj >= row.size()) { continue; }

                if (row[jj].is_alive()) { ret++; }
            }
        }
        return ret;
    }

    void step_cell(Cell& cell, size_t live_neighbours_count)
    {
        if (cell.is_alive())
        {
            if (live_neighbours_count < 2 or live_neighbours_count > 3) { cell.set_dead(); }
        }
        else  // cell is not alive
        {
            if (live_neighbours_count == 3) { cell.set_alive(); }
        }
    }

    void step()
    {
        for (auto i{ 0 }; i < data_.size(); ++i)
        {
            auto& row{ data_[i] };

            for (auto j{ 0 }; j < row.size(); ++j)
            {
                step_cell(row[j], count_live_cell_neighbours(i, j));
            }
        }
    }
};

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
void problem_60_main()
{
    // Initialize stop game flag
    stop_game = false;

    // Start game of life asynchronously
    auto fut_run = std::async(std::launch::async, []() { GameOfLife{}.run(); });

    // Wait for user to press any key
    wait_for_key_pressed();

    // Stop game!
    stop_game = true;
    
    // Wait for game of life to finish gracefully
    fut_run.get();

    std::cout << "\n";
}
