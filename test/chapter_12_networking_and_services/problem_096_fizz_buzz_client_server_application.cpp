#include "chapter_12_networking_and_services/problem_096_fizz_buzz_client_server_application.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(problem_96_main, DISABLED_output) {
    std::istringstream iss{
        "0\n"
        "100\n"
        "1\n"
        "2\n"
        "3\n"
        "4\n"
        "5\n"
        "15\n"
        "45\n"
        "quit\n"
    };
    std::ostringstream oss{};
    problem_96_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("[server] Starting\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("[client] Starting\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 0
        "[client] Error: invalid input\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 100
        "[client] Error: invalid input\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 1
        "[client] Says '1'\n"
        "[server] Says '1'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 2
        "[client] Says '2'\n"
        "[server] Says '2'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 3
        "[client] Says '3'\n"
        "[server] Says 'fizz'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 4
        "[client] Says '4'\n"
        "[server] Says '4'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 5
        "[client] Says '5'\n"
        "[server] Says 'buzz'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 15
        "[client] Says '15'\n"
        "[server] Says 'fizz-buzz'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 45
        "[client] Says '45'\n"
        "[server] Says 'fizz-buzz'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // quit
        "[client] Says 'quit'\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("[server] Exiting\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("[client] Exiting\n"));
    EXPECT_THAT(oss.str(), ::testing::EndsWith("\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
