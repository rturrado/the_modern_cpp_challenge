#pragma once

#include "rtc/random.h"

#include <algorithm>  // generate, shuffle
#include <memory>  // unique_ptr
#include <ostream>
#include <random>  // default_random_engine, random_device
#include <string>
#include <utility>  // move, pair
#include <vector>


namespace tmcppc::password {
    constexpr const auto digit_range{ std::pair<int, int>{ 48, 57 } };
    constexpr const auto uppercase_range{ std::pair<int, int>{ 65, 90 } };
    constexpr const auto lowercase_range{ std::pair<int, int>{ 97, 122 } };


    class password_generator {
    public:
        virtual ~password_generator() = default;

        [[nodiscard]] virtual std::string generate() const noexcept = 0;
    };


    class composite_password_generator : public password_generator {
    public:
        composite_password_generator() = default;
        ~composite_password_generator() override = default;
        composite_password_generator(const composite_password_generator& other) = delete;
        composite_password_generator& operator=(const composite_password_generator& other) = delete;
        composite_password_generator(composite_password_generator&& other) noexcept
            : gs_{ std::move(other.gs_) }
        {}
        composite_password_generator& operator=(composite_password_generator&& other) noexcept {
            gs_ = std::move(other.gs_);
            return *this;
        }

        void add_generator(std::unique_ptr<password_generator> g) noexcept { gs_.push_back(std::move(g)); }

        [[nodiscard]] std::string generate() const noexcept override {
            std::string ret{};
            for (auto&& g : gs_) {
                ret += g->generate();
            }
            std::ranges::shuffle(ret, std::default_random_engine{ std::random_device{}() });
            return ret;
        }

    private:
        std::vector<std::unique_ptr<password_generator>> gs_{};
    };


    class symbol_generator : public password_generator {
    public:
        symbol_generator() = default;
        explicit symbol_generator(size_t length) noexcept : length_{ length } {}

        [[nodiscard]] std::string generate() const noexcept override {
            static rtc::random::random_int random_character{ 0, 31 };  // 32 symbol characters
            std::string ret(length_, '!');
            std::ranges::generate(ret, []() {
                auto c{ random_character() };
                if (c <= 14) { c += '!'; }  // first group of 15 characters: !"#$%&'()*+,-./
                else if (c <= 21) { c += ':' - 15; }  // second group of 7 characters: :;<=>?@
                else if (c <= 27) { c += '[' - 22; }  // third group of 6 characters: [\]^_`
                else { c += '{' - 28; }  // fourth group of 4 characters: {|}~
                return static_cast<unsigned char>(c);
            });
            return ret;
        }

    private:
        size_t length_{ 1 };
    };


    template <std::pair<int, int> ascii_code_range>
    class contains_generator : public password_generator {
    public:
        contains_generator() = default;
        explicit contains_generator(size_t length) noexcept
            : length_{ length }
            , first_ascii_code_{ ascii_code_range.first }
            , last_ascii_code_{ ascii_code_range.second }
        {}

        [[nodiscard]] std::string generate() const noexcept override {
            static rtc::random::random_int random_character{ first_ascii_code_, last_ascii_code_ };
            std::string ret(length_, static_cast<unsigned char>(first_ascii_code_));
            std::ranges::generate(ret, []() { return static_cast<unsigned char>(random_character()); });
            return ret;
        }

    private:
        size_t length_{ 1 };
        int first_ascii_code_{ 33 };  // '!'
        int last_ascii_code_{ 126 };  // '~'
    };
}  // namespace tmcppc::password


void problem_68_main(std::ostream& os);
void problem_68_main();
