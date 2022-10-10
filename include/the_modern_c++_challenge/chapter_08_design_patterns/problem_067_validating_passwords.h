#pragma once

#include <algorithm>  // any_of
#include <cctype>  // isdigit, islower, ispunct, isupper
#include <fmt/format.h>
#include <iosfwd>
#include <memory>  // unique_ptr
#include <optional>
#include <string>
#include <string_view>
#include <utility>  // move


namespace tmcppc::password {
    inline auto contains_symbol = [](std::string_view sv) {
        return std::ranges::any_of(sv,
            [](unsigned char c) { return std::ispunct(c); }
        );
    };
    inline auto contains_digit = [](std::string_view sv) {
        return std::ranges::any_of(sv,
            [](unsigned char c) { return std::isdigit(c); }
        );
    };
    inline auto contains_lowercase = [](std::string_view sv) {
        return std::ranges::any_of(sv,
            [](unsigned char c) { return std::islower(c); }
        );
    };
    inline auto contains_uppercase = [](std::string_view sv) {
        return std::ranges::any_of(sv,
            [](unsigned char c) { return std::isupper(c); }
        );
    };


    namespace validator {
        using validate_error_message = std::string;
        using validate_return_type = std::optional<validate_error_message>;


        // This solution uses the Chain of Responsibility pattern
        //
        // The password_strength_validator base class:
        //   - specifies a 'validate' interface,
        //   - holds a raw pointer to the next validator in the chain, offering a setter for it, and
        //   - lets validators continue the validation process through a 'validate_with_next' method
        //
        // The different concrete classes:
        //   - implement the validate interface, and
        //   - whether they return an error or they return control to the base class to continue with the validation
        //
        // The client:
        //   - has to create the validators separately, then
        //   - chain them using the 'set_next' base class method (passing the address of each validator as argument), and, finally,
        //   - call 'validate' on the first of them
        namespace v1 {
            class password_strength_validator {
            public:
                [[nodiscard]] virtual validate_return_type validate(std::string_view pw) const noexcept = 0;

                void set_next(password_strength_validator* next) noexcept { next_ = next; }
            protected:
                password_strength_validator* next_{ nullptr };

                [[nodiscard]] validate_return_type validate_with_next(std::string_view pw) const noexcept {
                    return (next_ ? next_->validate(pw) : validate_return_type{});
                }
            };


            class minimum_length_validator : public password_strength_validator {
            public:
                minimum_length_validator() = default;
                explicit minimum_length_validator(size_t length) : length_{ length } {}

                [[nodiscard]] validate_return_type validate(std::string_view pw) const noexcept override {
                    if (pw.size() < length_) {
                        return fmt::format("{} {}", "password length has to be at least", length_);
                    } else {
                        return validate_with_next(pw);
                    }
                }
            private:
                size_t length_{ 8 };
            };


            template <typename Predicate>
            class contains_validator : public password_strength_validator {
            public:
                contains_validator() = delete;
                explicit contains_validator(Predicate pred, std::string_view error_message)
                    : pred_{ pred }
                    , error_message_{ error_message }
                {}

                [[nodiscard]] validate_return_type validate(std::string_view pw) const noexcept override {
                    if (not pred_(pw)) {
                        return error_message_;
                    } else {
                        return validate_with_next(pw);
                    }
                }
            private:
                Predicate pred_{};
                std::string error_message_{};
            };


            // Helpers
            //
            static inline contains_validator contains_symbol_validator{
                contains_symbol,
                "password has to contain at least one 'symbol'"
            };
            static inline contains_validator contains_digit_validator{
                contains_digit,
                "password has to contain at least one 'digit'"
            };
            static inline contains_validator contains_lowercase_validator{
                contains_lowercase,
                "password has to contain at least one 'lowercase' letter"
            };
            static inline contains_validator contains_uppercase_validator{
                contains_uppercase,
                "password has to contain at least one 'uppercase' letter"
            };


            void test_validator(std::ostream& os);
        }  // namespace v1


        // This solution is a variant on the previous one, and a bit more similar to the book's solution
        //
        // The password_strength_validator base class:
        //   - specifies a 'validate' interface,
        //   - holds a unique pointer to the next validator in the chain, which receives as a constructor argument, and
        //   - lets validators continue the validation process through a 'validate_with_next' method
        //
        // The different concrete classes:
        //   - implement the validate interface, and
        //   - whether they return an error or they return control to the base class to continue with the validation
        //
        // The client:
        //   - creates all the validators on the go, chaining them via their constructors, and
        //   - calls 'validate' on the outermost one
        namespace v2 {
            class password_strength_validator {
            public:
                virtual ~password_strength_validator() = default;

                [[nodiscard]] virtual validate_return_type validate(std::string_view pw) const noexcept = 0;

            protected:
                std::unique_ptr<password_strength_validator> next_{ nullptr };

                explicit password_strength_validator(std::unique_ptr<password_strength_validator> next = nullptr)
                    : next_{ std::move(next) }
                {}

                [[nodiscard]] validate_return_type validate_with_next(std::string_view pw) const noexcept {
                    return (next_ ? next_->validate(pw) : validate_return_type{});
                }
            };


            class minimum_length_validator : public password_strength_validator {
            public:
                minimum_length_validator() = default;
                explicit minimum_length_validator(size_t length, std::unique_ptr<password_strength_validator> next = nullptr)
                    : password_strength_validator{ std::move(next) }
                    , length_{ length }
                {}

                [[nodiscard]] validate_return_type validate(std::string_view pw) const noexcept override {
                    if (pw.size() < length_) {
                        return fmt::format("{} {}", "password length has to be at least", length_);
                    } else {
                        return validate_with_next(pw);
                    }
                }
            private:
                size_t length_{ 8 };
            };


            template <typename ContainsOrErrorF>
            class contains_validator : public password_strength_validator {
            public:
                contains_validator() = delete;
                explicit contains_validator(ContainsOrErrorF f, std::unique_ptr<password_strength_validator> next = nullptr)
                    : password_strength_validator{ std::move(next) }
                    , contains_or_error_f_{ f }
                {}

                [[nodiscard]] validate_return_type validate(std::string_view pw) const noexcept override {
                    if (auto error{ contains_or_error_f_(pw) }) {
                        return error.value();
                    } else {
                        return validate_with_next(pw);
                    }
                }
            private:
                ContainsOrErrorF contains_or_error_f_{};
            };


            // Helpers
            //
            inline auto contains_symbol_or_error = [](std::string_view sv) {
                return contains_symbol(sv)
                    ? validate_return_type{}
                    : validate_error_message{ "password has to contain at least one 'symbol'" };
            };
            inline auto contains_digit_or_error = [](std::string_view sv) {
                return contains_digit(sv)
                    ? validate_return_type{}
                    : validate_error_message{ "password has to contain at least one 'digit'" };
            };
            inline auto contains_lowercase_or_error = [](std::string_view sv) {
                return contains_lowercase(sv)
                    ? validate_return_type{}
                    : validate_error_message{ "password has to contain at least one 'lowercase'" };
            };
            inline auto contains_uppercase_or_error = [](std::string_view sv) {
                return contains_uppercase(sv)
                    ? validate_return_type{}
                    : validate_error_message{ "password has to contain at least one 'uppercase'" };
            };


            void test_validator(std::ostream& os);
        }  // namespace v2
    }  // namespace validator
}  // namespace tmcppc::password


void problem_67_main(std::ostream& os);
