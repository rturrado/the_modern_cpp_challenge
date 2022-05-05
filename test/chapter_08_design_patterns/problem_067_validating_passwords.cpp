#include "chapter_08_design_patterns/problem_067_validating_passwords.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_67_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_67_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "v1:\n"
        "\t'hola' is not valid: password length has to be at least 8.\n"
        "\t'holaquetal' is not valid: password has to contain at least one 'symbol'.\n"
        "\t'holaqueta!' is not valid: password has to contain at least one 'digit'.\n"
        "\t'h0laqueta!' is not valid: password has to contain at least one 'uppercase' letter.\n"
        "\t'H0LAQUETA!' is not valid: password has to contain at least one 'lowercase' letter.\n"
        "\t'h0laQueTa!' is a valid password.\n"
        "\n"
        "v2:\n"
        "\t'hola' is not valid: password length has to be at least 8.\n"
        "\t'holaquetal' is not valid: password has to contain at least one 'symbol'.\n"
        "\t'holaqueta!' is not valid: password has to contain at least one 'digit'.\n"
        "\t'h0laqueta!' is not valid: password has to contain at least one 'uppercase'.\n"
        "\t'H0LAQUETA!' is not valid: password has to contain at least one 'lowercase'.\n"
        "\t'h0laQueTa!' is a valid password.\n"
    ));
}
