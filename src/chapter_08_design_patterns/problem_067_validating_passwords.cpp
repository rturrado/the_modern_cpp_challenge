#include "chapter_08_design_patterns/problem_067_validating_passwords.h"

#include <fmt/ostream.h>
#include <iostream>  // cout
#include <memory>  // make_unique
#include <ostream>


namespace tmcppc::password::validator {
    namespace v1 {
        void test_validator(std::ostream& os) {
            using namespace std::string_view_literals;

            minimum_length_validator validator{ 8 };
            validator.set_next(&contains_symbol_validator);
            contains_symbol_validator.set_next(&contains_digit_validator);
            contains_digit_validator.set_next(&contains_lowercase_validator);
            contains_lowercase_validator.set_next(&contains_uppercase_validator);

            fmt::print(os, "v1:\n");
            for (auto&& pw : { "hola"sv, "holaquetal"sv, "holaqueta!"sv, "h0laqueta!"sv, "H0LAQUETA!"sv, "h0laQueTa!"sv }) {
                if (auto error{ validator.validate(pw) }) {
                    fmt::print(os, "\t'{}' is not valid: {}.\n", pw, error.value());
                } else {
                    fmt::print(os, "\t'{}' is a valid password.\n", pw);
                }
            }
            fmt::print(os, "\n");
        }
    }  // namespace v1

    namespace v2 {
        void test_validator(std::ostream& os) {
            using namespace std::string_view_literals;

            auto validator(
                std::make_unique<minimum_length_validator>(8,
                    std::make_unique<contains_validator<decltype(contains_symbol_or_error)>>(contains_symbol_or_error,
                        std::make_unique<contains_validator<decltype(contains_digit_or_error)>>(contains_digit_or_error,
                            std::make_unique<contains_validator<decltype(contains_lowercase_or_error)>>(contains_lowercase_or_error,
                                std::make_unique<contains_validator<decltype(contains_uppercase_or_error)>>(contains_uppercase_or_error,
                                    nullptr
                                    )
                                )
                            )
                        )
                    )
            );

            fmt::print(os, "v2:\n");
            for (auto&& pw : { "hola"sv, "holaquetal"sv, "holaqueta!"sv, "h0laqueta!"sv, "H0LAQUETA!"sv, "h0laQueTa!"sv }) {
                if (auto error{ validator->validate(pw) }) {
                    fmt::print(os, "\t'{}' is not valid: {}.\n", pw, error.value());
                } else {
                    fmt::print(os, "\t'{}' is a valid password.\n", pw);
                }
            }
            fmt::print(os, "\n");
        }
    }  // namespace v2
}  // namespace tmcppc::password::validator



// Validating passwords
//
// Write a program that validates password strength based on predefined rules, which may be selected in various combinations.
// At a minimum, every password must meet a minimum length requirement.
// In addition, other rules could be enforced, such as the presence of at least one symbol, digit, uppercase and lowercase letter, and so on.
void problem_67_main(std::ostream& os) {
    tmcppc::password::validator::v1::test_validator(os);
    tmcppc::password::validator::v2::test_validator(os);
}
