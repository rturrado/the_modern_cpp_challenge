#include "chapter_02_language_features/problem_021_system_handle_wrapper.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>  // transform
#include <sstream>  // wostringstream
#include <string>  // wstring


TEST(problem_21_main, DISABLED_output) {
    std::wostringstream woss{};
    problem_21_main(woss);
    std::wstring woss_str{ woss.str() };
    std::string oss_str(woss_str.size(), 0);
    std::ranges::transform(woss_str, std::begin(oss_str),
        [](wchar_t c) { return static_cast<char>(c);
    });
#ifdef _WIN32
    EXPECT_THAT(oss_str, ::testing::ContainsRegex(
        "Opened: .*res/sample_file.txt"
    ));
    EXPECT_THAT(oss_str, ::testing::HasSubstr(
        "Read 1024 bytes from file\n"
        "Error: I'm a throwing function!\n\n"
    ));
#endif
    EXPECT_THAT(oss_str, ::testing::Not(::testing::EndsWith("\n\n\n")));
}
