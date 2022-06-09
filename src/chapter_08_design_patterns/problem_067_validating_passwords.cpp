#include "chapter_08_design_patterns/problem_067_validating_passwords.h"

#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>


namespace tmcppc::password {
    namespace validator::v1 {
        void test_validator(std::ostream& os) {
            using namespace std::string_view_literals;

            fmt::print(os, "v1:\n");
            for (auto&& pw : { "hola"sv, "holaquetal"sv, "holaqueta!"sv, "h0laqueta!"sv, "H0LAQUETA!"sv, "h0laQueTa!"sv }) {
                minimum_length_validator validator{ 8 };
                contains_validator contains_symbol_validator{
                    contains_symbol,
                    "password has to contain at least one 'symbol'"sv
                };
                contains_validator contains_digit_validator{
                    contains_digit,
                    "password has to contain at least one 'digit'"sv
                };
                contains_validator contains_lowercase_validator{
                    contains_lowercase,
                    "password has to contain at least one 'lowercase' letter"sv
                };
                contains_validator contains_uppercase_validator{
                    contains_uppercase,
                    "password has to contain at least one 'uppercase' letter"sv
                };

                validator.set_next(&contains_symbol_validator);
                contains_symbol_validator.set_next(&contains_digit_validator);
                contains_digit_validator.set_next(&contains_lowercase_validator);
                contains_lowercase_validator.set_next(&contains_uppercase_validator);

                if (auto error{ validator.validate(pw) }) {
                    fmt::print(os, "\t'{}' is not valid: {}.\n", pw, error.value());
                } else {
                    fmt::print(os, "\t'{}' is a valid password.\n", pw);
                }
            }
            fmt::print(os, "\n");
        }
    }  // namespace validator::v1

    namespace validator::v2 {
        void test_validator(std::ostream& os) {
            using namespace std::string_view_literals;

            auto contains_symbol_or_error = [](std::string_view sv) {
                return contains_symbol(sv)
                    ? validate_return_type{}
                    : validate_error_message{ "password has to contain at least one 'symbol'" };
            };
            auto contains_digit_or_error = [](std::string_view sv) {
                return contains_digit(sv)
                    ? validate_return_type{}
                    : validate_error_message{ "password has to contain at least one 'digit'" };
            };
            auto contains_lowercase_or_error = [](std::string_view sv) {
                return contains_lowercase(sv)
                    ? validate_return_type{}
                    : validate_error_message{ "password has to contain at least one 'lowercase'" };
            };
            auto contains_uppercase_or_error = [](std::string_view sv) {
                return contains_uppercase(sv)
                    ? validate_return_type{}
                    : validate_error_message{ "password has to contain at least one 'uppercase'" };
            };

            fmt::print(os, "v2:\n");
            for (auto&& pw : { "hola"sv, "holaquetal"sv, "holaqueta!"sv, "h0laqueta!"sv, "H0LAQUETA!"sv, "h0laQueTa!"sv }) {
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

                if (auto error{ validator->validate(pw) }) {
                    fmt::print(os, "\t'{}' is not valid: {}.\n", pw, error.value());
                } else {
                    fmt::print(os, "\t'{}' is a valid password.\n", pw);
                }
            }
            fmt::print(os, "\n");
        }
    }  // namespace validator::v2
}  // namespace tmcppc::password



void problem_67_main(std::ostream& os) {
    tmcppc::password::validator::v1::test_validator(os);
    tmcppc::password::validator::v2::test_validator(os);
}


// Validating passwords
//
// Write a program that validates password strength based on predefined rules, which may be selected in various combinations.
// At a minimum, every password must meet a minimum length requirement.
// In addition, other rules could be enforced, such as the presence of at least one symbol, digit, uppercase and lowercase letter, and so on.
void problem_67_main() {
    problem_67_main(std::cout);
}
