#include "chapter_11_cryptography/problem_092_computing_file_hashes.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_92_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_92_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
