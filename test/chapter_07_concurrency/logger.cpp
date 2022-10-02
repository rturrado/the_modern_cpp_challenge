#include "chapter_07_concurrency/logger.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream

using namespace tmcppc::logging::v2;


TEST(logger_v2, log_no_messages) {
    std::ostringstream oss{};
    logger::get_instance().log(oss);
    EXPECT_TRUE(oss.str().empty());
}

TEST(logger_v2, log_messages) {
    std::ostringstream oss{};
    logger::get_instance().log(oss, "// This is ", 111, "\n");
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("// This is 111\n"));
}
