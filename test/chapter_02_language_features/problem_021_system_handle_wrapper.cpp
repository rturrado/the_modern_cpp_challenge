#include "chapter_02_language_features/problem_021_system_handle_wrapper.h"

#include <algorithm>  // transform
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // wostringstream
#include <string>  // wstring


TEST(problem_21_main, DISABLED_output) {
    std::wostringstream woss{};
    problem_21_main(woss);
    std::wstring woss_str{ woss.str() };
    std::string oss_str(woss_str.size(), 0);
    std::transform(std::begin(woss_str), std::end(woss_str), std::begin(oss_str),
        [](wchar_t c) { return static_cast<char>(c); });
#ifdef _WIN32
    EXPECT_THAT(oss_str, ::testing::ContainsRegex(
        "Opened: .*res/sample_file.txt"
    ));
    EXPECT_THAT(oss_str, ::testing::HasSubstr(
        "Read 1024 from file\n"
        "Error: I'm a throwing function!\n"
    ));
#endif
}
