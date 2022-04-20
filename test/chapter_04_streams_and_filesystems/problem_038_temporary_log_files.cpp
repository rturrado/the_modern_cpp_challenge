#include "chapter_04_streams_and_filesystems/problem_038_temporary_log_files.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_38_main, output) {
    std::ostringstream oss{};
    problem_38_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Creating logger_1 and logger_2 instances...\n"
        "Writing out to logger_1 and logger_2...\n"
        "\tR u awake\\? Want 2 chat\\?\n"
        "\tO Rom. Where4 art thou\\?\n"
        "\tOutside yr window.\n"
        "\tStalker! J/K.\n"
        "\tHad 2-feeln' romantc.\n"
        "\tB careful. My family h8 u.\n"
        "\tI no. What about u\\?\n"
        "\t'M up for marriage if u r. Is tht a bit fwd\\?\n"
        "\tNo. Yes. No. Oh, dsnt mat-r. 2moro @ 9\\?\n"
        "\tLuv U xxxx\n"
        "Moving logger_1 from '.*log' to '.*log_1.txt'\n"
        "Writing out something else to logger_1...\n"
        "\tCU then xxxx\n"
        "Moving logger_1 from '.*log_1.txt' to '.*log_1-new.txt'\n"
        "Asking for logger_1 location: '.*log_1-new.txt'\n"
    ));
}
