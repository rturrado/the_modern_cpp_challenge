#include "Chapter8_DesignPatterns.h"
#include "RtcRandom.h"

#include <algorithm>  // generate, shuffle
#include <iostream>  // cout
#include <memory>  // make_unique, unique_ptr
#include <random>  // default_random_engine, random_device
#include <string>
#include <utility>  // pair
#include <vector>


constexpr const auto digit_range{ std::pair<int, int>{ 48, 57 } };
constexpr const auto uppercase_range{ std::pair<int, int>{ 65, 90 } };
constexpr const auto lowercase_range{ std::pair<int, int>{ 97, 122 } };


class PasswordGenerator
{
public:
    virtual ~PasswordGenerator() = default;

    [[nodiscard]] virtual std::string generate() const noexcept = 0;
};


class CompositePasswordGenerator : public PasswordGenerator
{
public:
    CompositePasswordGenerator() = default;
    ~CompositePasswordGenerator() = default;
    CompositePasswordGenerator(const CompositePasswordGenerator& other) = delete;
    CompositePasswordGenerator& operator=(const CompositePasswordGenerator& other) = delete;
    CompositePasswordGenerator(CompositePasswordGenerator&& other) noexcept : gs_{ std::move(other.gs_) } {}
    CompositePasswordGenerator& operator=(CompositePasswordGenerator&& other) noexcept { gs_ = std::move(other.gs_); return *this; }

    void add_generator(std::unique_ptr<PasswordGenerator> g) noexcept { gs_.push_back(std::move(g)); }

    [[nodiscard]] virtual std::string generate() const noexcept override
    {
        std::string ret{};
        for (auto&& g : gs_) { ret += g->generate(); }
        std::shuffle(std::begin(ret), std::end(ret), std::default_random_engine{ std::random_device{}() });
        return ret;
    }

private:
    std::vector<std::unique_ptr<PasswordGenerator>> gs_{};
};


class SymbolGenerator : public PasswordGenerator
{
public:
    SymbolGenerator() = default;
    SymbolGenerator(size_t length) noexcept : length_{ length } {}

    [[nodiscard]] virtual std::string generate() const noexcept override {
        static rtc::random::RandomInt random_character{ 0, 31 };  // 32 symbol characters
        std::string ret(length_, '!');
        std::generate(std::begin(ret), std::end(ret), []() {
                auto c{ random_character() };
                if (c <= 14) { c += '!'; }  // first group of 15 characters: !"#$%&'()*+,-./
                else if (c <= 21) { c += ':' - 15; }  // second group of 7 characters: :;<=>?@
                else if (c <= 27) { c += '[' - 22; }  // third group of 6 characters: [\]^_`
                else { c += '{' - 28; }  // fourth group of 4 characters: {|}~
                return static_cast<unsigned char>(c);
            }
        );
        return ret;
    }

private:
    size_t length_{ 1 };
};


template <std::pair<int, int> ascii_code_range>
class ContainsGenerator : public PasswordGenerator
{
public:
    ContainsGenerator() = default;
    ContainsGenerator(size_t length) noexcept
        : length_{ length }, first_ascii_code_{ ascii_code_range.first }, last_ascii_code_{ ascii_code_range.second }
    {}

    [[nodiscard]] virtual std::string generate() const noexcept override {
        static rtc::random::RandomInt random_character{ first_ascii_code_, last_ascii_code_ };
        std::string ret(length_, static_cast<unsigned char>(first_ascii_code_));
        std::generate(std::begin(ret), std::end(ret), []() { return static_cast<unsigned char>(random_character()); });
        return ret;
    }

private:
    size_t length_{ 1 };
    int first_ascii_code_{ 33 };  // '!'
    int last_ascii_code_{ 126 };  // '~'
};


// Generating random passwords
//
// Write a program that can generate random passwords according to some predefined rules.
// Every password must have a configurable minimum length.
// In addition, it should be possible to include in the generation rules such as the presence of at least one digit,
// symbol, lower or uppercase character, and so on. These additional rules must be configurable and composable.
void problem_68_main()
{
    auto g{ std::make_unique<CompositePasswordGenerator>() }; std::cout << "Creating a password ";

    g->add_generator(std::make_unique<SymbolGenerator>(2)); std::cout << "with 2 symbols, ";
    g->add_generator(std::make_unique<ContainsGenerator<digit_range>>(2)); std::cout << "2 digits, ";
    g->add_generator(std::make_unique<ContainsGenerator<lowercase_range>>(2)); std::cout << "2 lowercase letters, ";
    g->add_generator(std::make_unique<ContainsGenerator<uppercase_range>>(2)); std::cout << "and 2 uppercase letters: ";

    std::cout << g->generate() << "\n\n";
}
