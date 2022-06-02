#include "chapter_11_cryptography/problem_091_validating_user_credentials.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(problem_91_main, DISABLED_output) {
    std::istringstream iss{
        "marcos\nzuck3rb3rg!\n"
        "bill\nw1ndoze&g4tes\n"
        "samantha\nf0xxx\n"
        "michelle\nfail4her\n"
        "marcos\nblah\n"
        "bill\nfoo\n"
        "meh\n"
        "quit\n"
    };
    std::ostringstream oss{};
    problem_91_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Please enter username ('quit' for exiting): "  // marcos
        "Please enter password: "  // zuck3rb3rg!
        "\tOK: access granted\n"
        "Please enter username ('quit' for exiting): "  // bill
        "Please enter password: "  // w1ndoze&g4tes
        "\tOK: access granted\n"
        "Please enter username ('quit' for exiting): "  // samantha
        "Please enter password: "  // f0xxx
        "\tOK: access granted\n"
        "Please enter username ('quit' for exiting): "  // michelle
        "Please enter password: "  // fail4her
        "\tOK: access granted\n"
        "Please enter username ('quit' for exiting): "  // marcos
        "Please enter password: "  // blah
        "\tError: incorrect password\n"
        "Please enter username ('quit' for exiting): "  // bill
        "Please enter password: "  // foo
        "\tError: incorrect password\n"
        "Please enter username ('quit' for exiting): "  // meh
        "\tError: username not found\n"
        "Please enter username ('quit' for exiting): "  // quit
    ));
}
