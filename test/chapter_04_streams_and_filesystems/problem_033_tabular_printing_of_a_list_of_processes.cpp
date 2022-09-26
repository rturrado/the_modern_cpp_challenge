#include "chapter_04_streams_and_filesystems/problem_033_tabular_printing_of_a_list_of_processes.h"

#include "fmt/format.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream

using namespace tmcppc::problem_33;


TEST(info, constructor) {
    info info{ 1044, "crome.exe", status_t::running, "marius.bancila", 25180454, platform_t::x32 };
    EXPECT_EQ(info.id(), 1044);
    EXPECT_EQ(info.name(), "crome.exe");
    EXPECT_EQ(info.status(), status_t::running);
    EXPECT_EQ(info.account_name(), "marius.bancila");
    EXPECT_EQ(info.mem_size_b(), 25180454);
    EXPECT_EQ(info.platform(), platform_t::x32);
}


TEST(status_t, fmt_format_running) {
    EXPECT_THAT(fmt::format("{}", status_t::running), ::testing::HasSubstr("Running"));
}
TEST(status_t, fmt_format_suspended) {
    EXPECT_THAT(fmt::format("{}", status_t::suspended), ::testing::HasSubstr("Suspended"));
}
TEST(status_t, operator_insertion_running) {
    std::ostringstream oss{};
    oss << status_t::running;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Running"));
}
TEST(status_t, operator_insertion_suspended) {
    std::ostringstream oss{};
    oss << status_t::suspended;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Suspended"));
}
TEST(status_t, to_string_running) {
    EXPECT_THAT(to_string(status_t::running), ::testing::HasSubstr("Running"));
}
TEST(status_t, to_string_suspended) {
    EXPECT_THAT(to_string(status_t::suspended), ::testing::HasSubstr("Suspended"));
}


TEST(platform_t, fmt_format_x32) {
    EXPECT_THAT(fmt::format("{}", platform_t::x32), ::testing::HasSubstr("32-bit"));
}
TEST(platform_t, fmt_format_x64) {
    EXPECT_THAT(fmt::format("{}", platform_t::x64), ::testing::HasSubstr("64-bit"));
}
TEST(platform_t, operator_insertion_x32) {
    std::ostringstream oss{};
    oss << platform_t::x32;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("32-bit"));
}
TEST(platform_t, operator_insertion_x64) {
    std::ostringstream oss{};
    oss << platform_t::x64;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("64-bit"));
}
TEST(platform_t, to_string_x32) {
    EXPECT_THAT(to_string(platform_t::x32), ::testing::HasSubstr("32-bit"));
}
TEST(platform_t, to_string_x64) {
    EXPECT_THAT(to_string(platform_t::x64), ::testing::HasSubstr("64-bit"));
}


TEST(print_process_infos, no_infos) {
    std::ostringstream oss{};
    std::vector<info> infos{};
    print_process_infos(oss, infos);
    EXPECT_TRUE(oss.str().empty());
}
TEST(print_process_infos, one_info) {
    std::ostringstream oss{};
    std::vector<info> infos{
        { 1044, "chrome.exe", status_t::running, "marius.bancila", 25180454, platform_t::x32 }
    };
    print_process_infos(oss, infos);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "1044 chrome.exe Running marius.bancila 24590 32-bit"
    ));
}
TEST(print_process_infos, many_infos) {
    std::ostringstream oss{};
    std::vector<info> infos{
        { 512, "cmd.exe", status_t::running, "SYSTEM", 148293, platform_t::x64 },
        { 1044, "chrome.exe", status_t::running, "marius.bancila", 25180454, platform_t::x32 }
    };
    print_process_infos(oss, infos);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "1044 chrome.exe Running marius.bancila 24590 32-bit\n"
        "512  cmd.exe    Running SYSTEM           144 64-bit"
    ));
}


TEST(problem_33_main, output) {
    std::ostringstream oss{};
    problem_33_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "1044  chrome.exe   Running   marius.bancila  24590 32-bit\n"
        "10100 chrome.exe   Running   marius.bancila 222418 32-bit\n"
        "512   cmd.exe      Running   SYSTEM            144 64-bit\n"
        "7108  explorer.exe Running   marius.bancila   2883 64-bit\n"
        "22456 skype.exe    Suspended marius.bancila  16474 64-bit\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
