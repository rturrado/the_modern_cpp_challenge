#include "chapter_06_algorithms_and_data_structures/console.h"
#include "chapter_06_algorithms_and_data_structures/problem_060_game_of_life.h"
#include "chapter_06_algorithms_and_data_structures/timer.h"
#include "console/fake.h"
#include "timer/fake.h"

#include <algorithm>  // all_of
#include <chrono>
#include <future>  // async
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream
#include <thread>  // sleep_for

using namespace std::chrono_literals;
using namespace tmcppc::chrono;
using namespace tmcppc::game_of_life;
using namespace tmcppc::system;


TEST(cell, constructor) {
    EXPECT_TRUE(cell{}.is_dead());
}


TEST(game_of_life, grid_size_5_5) {
    std::ostringstream oss{};
    stop_game = false;
    auto fut_game = std::async(std::launch::async, [&oss]() {
        game_of_life{
            oss,
            console{ std::make_unique<console_fake>() },
            timer{ std::make_unique<timer_fake>() },
            10,
            10
        }.run();
    });
    auto fut_timeout = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(100ms);
        stop_game = true;
    });
    fut_game.get();
    fut_timeout.get();
    EXPECT_TRUE(std::ranges::all_of(oss.str(), [](unsigned char c) { return c == ' ' or c == '*' or c == '\n'; }));
}


TEST(problem_60_main, output) {
    std::ostringstream oss{};
    problem_60_main(
        oss,
        console{ std::make_unique<console_fake>() },
        timer{ std::make_unique<timer_fake>() },
        100ms
    );
    EXPECT_TRUE(std::ranges::all_of(oss.str(), [](unsigned char c) { return c == ' ' or c == '*' or c == '\n'; }));
    EXPECT_THAT(oss.str(), ::testing::EndsWith("\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
