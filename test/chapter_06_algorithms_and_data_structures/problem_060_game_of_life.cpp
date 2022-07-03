#include "chapter_06_algorithms_and_data_structures/problem_060_game_of_life.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>  // all_of
#include <chrono>
#include <future>  // async
#include <sstream>  // ostringstream
#include <thread>  // sleep_for

using namespace tmcppc::game_of_life;


TEST(cell, DISABLED_constructor) {
    EXPECT_TRUE(cell{}.is_dead());
}


TEST(game_of_life, DISABLED_three_by_three_display) {
    using namespace std::chrono_literals;
    std::ostringstream oss{};
    stop_game = false;
    auto fut_game = std::async(std::launch::async, [&oss]() {
        game_of_life{ oss, 3, 3 }.run();
    });
    auto fut_timeout = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(100ms);
        stop_game = true;
    });
    fut_game.get();
    fut_timeout.get();
    EXPECT_EQ(oss.str().size(), 12);
    EXPECT_TRUE(std::ranges::all_of(oss.str(), [](unsigned char c) { return c == ' ' or c == '*' or c == '\n'; }));
}


TEST(problem_60_main, DISABLED_output) {
    using namespace std::chrono_literals;

    std::ostringstream oss{};
    problem_60_main(oss, 1s);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("\\s+"));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("\\*+"));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("\n+"));
}
