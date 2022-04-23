#include "chapter_04_streams_and_filesystems/problem_033_tabular_printing_of_a_list_of_processes.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_33_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_33_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "1044  chrome.exe   Running   marius.bancila  24590 Running\n"
        "10100 chrome.exe   Running   marius.bancila 222418 Running\n"
        "512   cmd.exe      Running   SYSTEM            144 Running\n"
        "7108  explorer.exe Running   marius.bancila   2883 Running\n"
        "22456 skype.exe    Suspended marius.bancila  16474 Suspended\n"
    ));
}
