#include "chapter_10_archives_images_and_databases/problem_081_zip_compression_with_password.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // istringstream, ostringstream


TEST(problem_81_main, output) {
    std::istringstream iss{ "n\nn\n" };
    std::ostringstream oss{};
    problem_81_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Compressing: .*res/sample_folder/dilbert.jpg -> .*/dilbert.zip\n"
        "\tAdding entry: .*res/sample_folder/dilbert.jpg\n"
        "Decompressing: .*/dilbert.zip -> .*\n"
        "\tOpening archive file: .*/dilbert.zip\n"
        "\tExtracting: .*/dilbert.jpg\n"
        "Checking input '.*res/sample_folder/dilbert.jpg' and output '.*/dilbert.jpg' are equal\n"
        "\tOK\n"
        "Are you sure you want to remove '.*' and all of its contents\\? \\[y/n\\] "  // n
        "\tOK\n"
        "\n"
        "Compressing: .*res/sample_folder/sample_subfolder -> .*/sample_subfolder.zip\n"
        "\tAdding entry: .*res/sample_folder/sample_subfolder/use_your_illussion_ii.jpg\n"
        "Decompressing: .*/sample_subfolder.zip -> .*\n"
        "\tOpening archive file: .*/sample_subfolder.zip\n"
        "\tExtracting: .*/sample_subfolder/use_your_illussion_ii.jpg\n"
        "Checking input '.*res/sample_folder/sample_subfolder' and output '.*/sample_subfolder' are equal\n"
        "\tOK\n"
        "Are you sure you want to remove '.*' and all of its contents\\? \\[y/n\\] "  // n
        "\tOK\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
