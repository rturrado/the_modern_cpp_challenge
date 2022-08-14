#include "chapter_03_strings_and_regular_expressions/problem_029_license_plate_validation.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace tmcppc::problem_29;


TEST(validate_license_plate, DISABLED_invalid) {
    EXPECT_FALSE(validate_license_plate(""));  // empty string
    EXPECT_FALSE(validate_license_plate("aaa-BB 123"));  // lowercase instead of uppercase
    EXPECT_FALSE(validate_license_plate("123-BB 123"));  // numbers in first block of letters
    EXPECT_FALSE(validate_license_plate("AAA-12 123"));  // numbers in second block of letters
    EXPECT_FALSE(validate_license_plate("AAA-BB CCC"));  // letters in block of digits
    EXPECT_FALSE(validate_license_plate("AAA/BB 123"));  // wrong separator
    EXPECT_FALSE(validate_license_plate("AAA BB-123"));  // separator in wrong place
    EXPECT_FALSE(validate_license_plate("AA-BB 123"));  // wrong number of letters in first block of letters
    EXPECT_FALSE(validate_license_plate("AAAA-BB 123"));
    EXPECT_FALSE(validate_license_plate("AA-B 123"));  // wrong number of letters in second block of letters
    EXPECT_FALSE(validate_license_plate("AA-BBB 123"));
    EXPECT_FALSE(validate_license_plate("AAA-BB 12"));  // wrong number of digits in block of digits
    EXPECT_FALSE(validate_license_plate("AAA-BB 12345"));
    EXPECT_FALSE(validate_license_plate("blah AAA-BB 123"));  // extra characters
    EXPECT_FALSE(validate_license_plate("AAA-BB 123 blah"));
}
TEST(validate_license_plate, DISABLED_valid) {
    EXPECT_TRUE(validate_license_plate("AAA-BB 123"));
    EXPECT_TRUE(validate_license_plate("AAA-BB 1234"));
}

TEST(extract_all_license_plates, DISABLED_empty_string) {
    auto license_plates{ extract_all_license_plates("") };
    EXPECT_TRUE(license_plates.empty());
}
TEST(extract_all_license_plates, DISABLED_no_license_plates) {
    auto license_plates{ extract_all_license_plates("En un lugar de la Mancha") };
    EXPECT_TRUE(license_plates.empty());
}
TEST(extract_all_license_plates, DISABLED_one_valid_license_plate) {
    auto license_plates{ extract_all_license_plates("En un lugar ABC-DE 1234 de la Mancha") };
    EXPECT_THAT(license_plates, ::testing::ElementsAre("ABC-DE 1234"));
}
TEST(extract_all_license_plates, DISABLED_many_valid_license_plates) {
    auto license_plates{ extract_all_license_plates("AAA-AA 123qwe-ty 1234 ABC-DE 123456..XYZ-WW 0001") };
    EXPECT_THAT(license_plates, ::testing::ElementsAre("AAA-AA 123", "ABC-DE 1234", "XYZ-WW 0001"));
}

TEST(problem_29_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_29_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Is \"AAA-AA 12\" a valid license plate?: false\n"
        "Is \"AAA-AA 123\" a valid license plate?: true\n"
        "Is \"ABC-DE 1234\" a valid license plate?: true\n"
        "List of valid license plates in \"AAA-AA 123qwe-ty 1234 ABC-DE 123456..XYZ-WW 0001\":\n"
        "\t[\"AAA-AA 123\", \"ABC-DE 1234\", \"XYZ-WW 0001\"]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
