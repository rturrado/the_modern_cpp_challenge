#pragma once

#include "console.h"
#include "timer.h"

#include <algorithm>  // for_each
#include <atomic>
#include <chrono>
#include <iostream>  // flush
#include <ostream>
#include <rtc/random.h>
#include <thread>  // sleep_for
#include <vector>

namespace ch = std::chrono;


namespace tmcppc::game_of_life {
    inline constinit std::atomic<bool> stop_game{ false };


    enum class cell_state { dead, alive };


    class cell {
    public:
        cell() : state_{ cell_state::dead } { }

        [[nodiscard]] bool is_dead() const noexcept { return get_state() == cell_state::dead; }
        [[nodiscard]] bool is_alive() const noexcept { return get_state() == cell_state::alive; }

        void set_dead() { set_state(cell_state::dead); }
        void set_alive() { set_state(cell_state::alive); }

        // Set 90% of probability for a dead cell, 10% for an alive cell
        void set_random_state() {
            static rtc::random::random_int random_int_{ 0, 9 };
            set_state(random_int_() < 9 ? cell_state::dead : cell_state::alive);
        }

    private:
        cell_state state_{ cell_state::dead };

        [[nodiscard]] cell_state get_state() const noexcept { return state_; }
        void set_state(const cell_state& state) noexcept { state_ = state; }
    };


    class game_of_life {
        using grid = std::vector<std::vector<cell>>;

    public:
        // Fill grid randomly
        game_of_life(std::ostream& os, const tmcppc::system::console& console, const tmcppc::chrono::timer& timer,
            size_t rows = 20, size_t columns = 50)

            : os_{ os }
            , console_{ console }
            , timer_{ timer }
            , data_{ std::vector(rows, std::vector(columns, cell{})) } {

            std::ranges::for_each(data_, [](auto& row) {
                std::ranges::for_each(row, [](auto& cell) {
                    cell.set_random_state();
                });
            });
        }

        void run() {
            using namespace std::chrono_literals;
            while (not stop_game) {
                step();
                display();
                timer_.sleep_for(200ms);
            }
        }

        // Print grid
        void display() {
            console_.clear_screen();

            std::ranges::for_each(data_, [this](const auto& row) {
                std::ranges::for_each(row, [this](const auto& cell) {
                    fmt::print(os_, "{}", cell.is_alive() ? '*' : ' ');
                });
                fmt::print(os_, "\n");
            });
            os_ << std::flush;
        }

    private:
        std::ostream& os_;
        const tmcppc::system::console& console_;
        const tmcppc::chrono::timer& timer_;
        grid data_{};

        size_t count_live_cell_neighbours(size_t i, size_t j) {
            size_t ret{ 0 };
            for (size_t ii{ i - 1 }; ii <= i + 1; ++ii) {
                if (ii >= data_.size()) {
                    continue;
                }

                auto& row{ data_[ii] };

                for (size_t jj{ j - 1 }; jj <= j + 1; ++jj) {
                    if (jj >= row.size()) {
                        continue;
                    }
                    if (row[jj].is_alive()) {
                        ret++;
                    }
                }
            }
            return ret;
        }

        static void step_cell(cell& cell, size_t live_neighbours_count) {
            if (cell.is_alive()) {
                if (live_neighbours_count < 2 or live_neighbours_count > 3) {
                    cell.set_dead();
                }
            } else {  // cell is not alive
                if (live_neighbours_count == 3) {
                    cell.set_alive();
                }
            }
        }

        void step() {
            for (size_t i{ 0 }; i < data_.size(); ++i) {
                auto& row{ data_[i] };

                for (size_t j{ 0 }; j < row.size(); ++j) {
                    step_cell(row[j], count_live_cell_neighbours(i, j));
                }
            }
        }
    };
}  // namespace tmcppc::game_of_life


void problem_60_main(std::ostream& os, const tmcppc::system::console& console, const tmcppc::chrono::timer& timer,
    std::chrono::duration<double> timeout = {});
