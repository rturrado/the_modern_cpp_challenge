#include "chapter_04_streams_and_filesystems/logger.h"

#include "rtc/filesystem.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <sstream>  // ostringstream

namespace fs = std::filesystem;
using namespace rtc::filesystem;
using namespace tmcppc::logging::v1;


TEST(logger, DISABLED_log_empty_text) {
    logger logger{};
    logger.log("");
    auto file_content{ get_text_file_content(logger.get_file_path()) };
    EXPECT_TRUE(file_content.empty());
}

TEST(logger, DISABLED_log_text) {
    std::string log_file_path{};
    {
        logger logger{};
        logger.log("R u awake\\? Want 2 chat\\?\n");
        auto log_new_location{ std::filesystem::temp_directory_path() / "logger_log_text_test.txt" };
        logger.move_file(log_new_location);
        log_file_path = logger.get_file_path();
    }
    auto file_content{ get_text_file_content(log_file_path) };
    EXPECT_THAT(file_content, ::testing::HasSubstr("R u awake\\? Want 2 chat\\?\n"));
}

TEST(logger, DISABLED_move_file) {
    logger logger{};
    logger.log("R u awake\\? Want 2 chat\\?\n");

    auto old_file_path{ logger.get_file_path() };
    auto log_new_location{ std::filesystem::temp_directory_path() / "logger_move_file_test.txt" };
    logger.move_file(log_new_location);
    auto new_file_path{ logger.get_file_path() };
    EXPECT_FALSE(fs::exists(old_file_path));
    EXPECT_EQ(new_file_path, log_new_location.generic_string());

    auto file_content{ get_text_file_content(log_new_location) };
    EXPECT_THAT(file_content, ::testing::HasSubstr("R u awake\\? Want 2 chat\\?\n"));
}

TEST(logger, DISABLED_destructor_and_not_moved) {
    std::string log_file_path{};
    {
        logger logger{};
        log_file_path = logger.get_file_path();
    }
    EXPECT_FALSE(fs::exists(log_file_path));
}

TEST(logger, DISABLED_destructor_and_moved) {
    std::string log_file_path{};
    {
        logger logger{};
        auto log_new_location{ std::filesystem::temp_directory_path() / "logger_destructor_and_moved_test.txt" };
        logger.move_file(log_new_location);
        log_file_path = logger.get_file_path();
    }
    EXPECT_TRUE(fs::exists(log_file_path));
}
