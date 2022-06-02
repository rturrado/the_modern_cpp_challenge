#include "chapter_10_archives_images_and_databases/problem_080_zip_compression.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(problem_80_main, DISABLED_output) {
    std::istringstream iss{ "y\ny\n" };
    std::ostringstream oss{};
    problem_80_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Compressing: .*res/sample_folder/dilbert.jpg -> .*/dilbert.zip\n"
        "\tAdding entry: .*res/sample_folder/dilbert.jpg\n"
        "Decompressing: .*/dilbert.zip -> .*/\n"
        "\tOpening archive file: .*/dilbert.zip\n"
        "\tExtracting: .*res/sample_folder/dilbert.jpg\n"
        "Checking input '.*res/sample_folder/dilbert.jpg' and output '.*res/sample_folder/dilbert.jpg' are equal\n"
        "\tOK\n"
        "Are you sure you want to remove '.*' and all of its contents\\? \\[y/n\\] "
        "\tOK\n"
        "\n"
        "Compressing: .*res/sample_folder/sample_subfolder -> .*/sample_subfolder.zip\n"
        "\tAdding entry: .*res/sample_folder/sample_subfolder/use_your_illussion_ii.jpg\n"
        "Decompressing: .*/sample_subfolder.zip -> .*/\n"
        "\tOpening archive file: .*/sample_subfolder.zip\n"
        "\tExtracting: .*res/sample_folder/sample_subfolder/use_your_illussion_ii.jpg\n"
        "Checking input '.*res/sample_folder/sample_subfolder' and output '.*res/sample_folder/sample_subfolder' are equal\n"
        "\tOK\n"
        "Are you sure you want to remove '.*' and all of its contents\\? \\[y/n\\] "
        "\tOK\n"
    ));
}
