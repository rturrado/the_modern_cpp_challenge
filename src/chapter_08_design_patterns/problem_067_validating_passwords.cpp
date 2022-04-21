#include "Chapter8_DesignPatterns.h"

#include <algorithm>  // any_of
#include <cctype>  // isdigit, islower, ispunct, isupper
#include <iostream>  // cout
#include <memory>  // make_unique, unique_ptr
#include <optional>
#include <string>
#include <string_view>


using validate_error_message = std::string;
using validate_return_type = std::optional<validate_error_message>;


// This solution uses the Chain of Responsibility pattern
//
// The PasswordStrengthValidator base class:
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
namespace password_strength_validator_v1
{
    class PasswordStrengthValidator
    {
    public:
        [[nodiscard]] virtual validate_return_type validate(std::string_view pw) const noexcept = 0;

        void set_next(PasswordStrengthValidator* next) noexcept { next_ = next; }
    protected:
        PasswordStrengthValidator* next_{ nullptr };

        [[nodiscard]] validate_return_type validate_with_next(std::string_view pw) const noexcept {
            return (next_ ? next_->validate(pw) : validate_return_type{});
        }
    };


    class MinimumLengthValidator : public PasswordStrengthValidator
    {
    public:
        MinimumLengthValidator() = default;
        explicit MinimumLengthValidator(size_t length) : length_{ length } {}

        [[nodiscard]] virtual validate_return_type validate(std::string_view pw) const noexcept override {
            if (pw.size() < length_) { return std::string{ "password length has to be at least " } + std::to_string(length_); }
            else { return validate_with_next(pw); };
        }
    private:
        size_t length_{ 8 };
    };


    template <typename Predicate>
    class ContainsValidator : public PasswordStrengthValidator
    {
    public:
        ContainsValidator() = delete;
        explicit ContainsValidator(Predicate pred, std::string_view error_message) : pred_{ pred }, error_message_{ error_message } {}

        [[nodiscard]] virtual validate_return_type validate(std::string_view pw) const noexcept override {
            if (not pred_(pw)) { return error_message_; }
            else { return validate_with_next(pw); };
        }
    private:
        Predicate pred_{};
        std::string error_message_{};
    };
}  // namespace password_strength_validator_v1


// This solution is a variant on the previous one, and a bit more similar to the book's solution
//
// The PasswordStrengthValidator base class:
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
namespace password_strength_validator_v2
{
    class PasswordStrengthValidator
    {
    public:
        [[nodiscard]] virtual validate_return_type validate(std::string_view pw) const noexcept = 0;

    protected:
        std::unique_ptr<PasswordStrengthValidator> next_{ nullptr };

        explicit PasswordStrengthValidator(std::unique_ptr<PasswordStrengthValidator> next) : next_{ std::move(next) } {}

        [[nodiscard]] validate_return_type validate_with_next(std::string_view pw) const noexcept {
            return (next_ ? next_->validate(pw) : validate_return_type{});
        }
    };


    class MinimumLengthValidator : public PasswordStrengthValidator
    {
    public:
        MinimumLengthValidator() = default;
        MinimumLengthValidator(size_t length, std::unique_ptr<PasswordStrengthValidator> next)
            : length_{ length }, PasswordStrengthValidator{ std::move(next) } {}

        [[nodiscard]] virtual validate_return_type validate(std::string_view pw) const noexcept override {
            if (pw.size() < length_) { return std::string{ "password length has to be at least " } + std::to_string(length_); }
            else { return validate_with_next(pw); };
        }
    private:
        size_t length_{ 8 };
    };


    template <typename ContainsOrErrorF>
    class ContainsValidator : public PasswordStrengthValidator
    {
    public:
        ContainsValidator() = delete;
        ContainsValidator(ContainsOrErrorF f, std::unique_ptr<PasswordStrengthValidator> next)
            : contains_or_error_f_{ f }, PasswordStrengthValidator{ std::move(next) } {}

        [[nodiscard]] virtual validate_return_type validate(std::string_view pw) const noexcept override {
            if (auto error{ contains_or_error_f_(pw) }) { return error.value(); }
            else { return validate_with_next(pw); };
        }
    private:
        ContainsOrErrorF contains_or_error_f_{};
    };
}  // namespace password_strength_validator_v2


// Validating passwords
//
// Write a program that validates password strength based on predefined rules, which may be selected in various combinations.
// At a minimum, every password must meet a minimum length requirement.
// In addition, other rules could be enforced, such as the presence of at least one symbol, digit, uppercase and lowercase letter, and so on.
void problem_67_main()
{
    using namespace std::string_view_literals;

    auto contains_symbol = [](std::string_view sv) {
        return std::any_of(std::cbegin(sv), std::cend(sv),
            [](unsigned char c) { return std::ispunct(c); }
        );
    };
    auto contains_digit = [](std::string_view sv) {
        return std::any_of(std::cbegin(sv), std::cend(sv),
            [](unsigned char c) { return std::isdigit(c); }
        );
    };
    auto contains_lowercase = [](std::string_view sv) {
        return std::any_of(std::cbegin(sv), std::cend(sv),
            [](unsigned char c) { return std::islower(c); }
        );
    };
    auto contains_uppercase = [](std::string_view sv) {
        return std::any_of(std::cbegin(sv), std::cend(sv),
            [](unsigned char c) { return std::isupper(c); }
        );
    };

    // v1
    {
        using namespace password_strength_validator_v1;

        std::cout << "v1:\n";
        for (auto&& pw : { "hola"sv, "holaquetal"sv, "holaqueta!"sv, "h0laqueta!"sv, "H0LAQUETA!"sv, "h0laQueTa!"sv })
        {
            MinimumLengthValidator validator{ 8 };
            ContainsValidator contains_symbol_validator{ contains_symbol, "password has to contain at least one 'symbol'"sv };
            ContainsValidator contains_digit_validator{ contains_digit, "password has to contain at least one 'digit'"sv };
            ContainsValidator contains_lowercase_validator{ contains_lowercase, "password has to contain at least one 'lowercase' letter"sv };
            ContainsValidator contains_uppercase_validator{ contains_uppercase, "password has to contain at least one 'uppercase' letter"sv };

            validator.set_next(&contains_symbol_validator);
            contains_symbol_validator.set_next(&contains_digit_validator);
            contains_digit_validator.set_next(&contains_lowercase_validator);
            contains_lowercase_validator.set_next(&contains_uppercase_validator);

            if (auto error{ validator.validate(pw) }) { std::cout << "\t'" << pw << "' is not valid: " << error.value() << ".\n"; }
            else { std::cout << "\t'" << pw << "' is a valid password.\n"; }
        }
        std::cout << "\n";
    }

    // v2
    {
        using namespace password_strength_validator_v2;

        auto contains_symbol_or_error = [&contains_symbol](std::string_view sv) {
            return (contains_symbol(sv) ? validate_return_type{} : validate_error_message{ "password has to contain at least one 'symbol'" });
        };
        auto contains_digit_or_error = [&contains_digit](std::string_view sv) {
            return (contains_digit(sv) ? validate_return_type{} : validate_error_message{ "password has to contain at least one 'digit'" });
        };
        auto contains_lowercase_or_error = [&contains_lowercase](std::string_view sv) {
            return (contains_lowercase(sv) ? validate_return_type{} : validate_error_message{ "password has to contain at least one 'lowercase'" });
        };
        auto contains_uppercase_or_error = [&contains_uppercase](std::string_view sv) {
            return (contains_uppercase(sv) ? validate_return_type{} : validate_error_message{ "password has to contain at least one 'uppercase'" });
        };

        std::cout << "v2:\n";
        for (auto&& pw : { "hola"sv, "holaquetal"sv, "holaqueta!"sv, "h0laqueta!"sv, "H0LAQUETA!"sv, "h0laQueTa!"sv })
        {
            auto validator(
                std::make_unique<MinimumLengthValidator>(8,
                    std::make_unique<ContainsValidator<decltype(contains_symbol_or_error)>>(contains_symbol_or_error,
                        std::make_unique<ContainsValidator<decltype(contains_digit_or_error)>>(contains_digit_or_error,
                            std::make_unique<ContainsValidator<decltype(contains_lowercase_or_error)>>(contains_lowercase_or_error,
                                std::make_unique<ContainsValidator<decltype(contains_uppercase_or_error)>>(contains_uppercase_or_error, nullptr)
                            )
                        )
                    )
                )
            );

            if (auto error{ validator->validate(pw) }) { std::cout << "\t'" << pw << "' is not valid: " << error.value() << ".\n"; }
            else { std::cout << "\t'" << pw << "' is a valid password.\n"; }
        }
        std::cout << "\n";
    }
}
