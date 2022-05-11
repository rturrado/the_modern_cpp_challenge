#include "chapter_09_data_serialization/problem_078_creating_a_pdf_from_a_collection_of_images.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_78_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_78_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Writing PDF out to: .*/images.pdf\n"
    ));
}
