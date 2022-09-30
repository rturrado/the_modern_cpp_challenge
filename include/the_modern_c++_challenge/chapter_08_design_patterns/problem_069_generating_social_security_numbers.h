#pragma once

#include <algorithm>  // binary_search, sort
#include <chrono>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <initializer_list>
#include <numeric>  // accumulate
#include <ostream>
#include <rtc/random.h>
#include <sstream>  // ostringstream
#include <string>  // to_string
#include <unordered_map>
#include <vector>

namespace ch = std::chrono;


namespace tmcppc::ssn {
    enum class sex { female, male };


    struct person {
        sex sex_{};
        ch::year_month_day birth_date_{};
    };


    class ssn_generator {
    public:
        virtual ~ssn_generator() = default;

        template <typename person>
        [[nodiscard]] std::string generate(person&& p) {
            auto ymd{ encode_birth_date(p.birth_date_) };
            auto ssn_without_crc{ fmt::format("{}{}{}", encode_sex(p.sex_), ymd, encode_random_number(ymd)) };
            return fmt::format("{}{}", ssn_without_crc, encode_crc(ssn_without_crc));
        }

    protected:
        [[nodiscard]] virtual int get_sex_female_code() const noexcept = 0;
        [[nodiscard]] virtual int get_sex_male_code() const noexcept = 0;
        [[nodiscard]] virtual int get_random_number_max() const noexcept = 0;
        [[nodiscard]] virtual int get_random_number_str_size() const noexcept = 0;
        [[nodiscard]] virtual int get_crc_modulo() const noexcept = 0;

    private:
        using random_number_str = std::string;
        using date_str = std::string;
        using vector_of_date_str = std::vector<date_str>;
        mutable std::unordered_map<random_number_str, vector_of_date_str> random_number_str_cache_{};

        [[nodiscard]] std::string encode_sex(sex sex) const noexcept {
            return fmt::format("{}", (sex == sex::female) ? get_sex_female_code() : get_sex_male_code());
        }
        [[nodiscard]] static std::string encode_birth_date(const ch::year_month_day& birth_date) noexcept {
            return fmt::format("{:%Y%m%d}", ch::sys_days(birth_date));
        }
        [[nodiscard]] std::string encode_random_number(const std::string& birth_date_str) const noexcept {
            rtc::random::random_int random_int{ 0, get_random_number_max() };

            for (;;) {
                auto rn_str{ random_number_to_string(random_int()) };

                if (random_number_str_cache_.contains(rn_str)) {
                    auto& v{ random_number_str_cache_.find(rn_str)->second };
                    if (std::ranges::binary_search(v, birth_date_str)) {
                        continue;
                    }

                    v.push_back(birth_date_str);
                    std::sort(std::begin(v), std::end(v));
                    return rn_str;
                } else {
                    random_number_str_cache_[rn_str] = vector_of_date_str{ birth_date_str };
                    return rn_str;
                }
            }
        }
        [[nodiscard]] std::string random_number_to_string(const int random_number) const noexcept {
            return fmt::format("{0:0{1}}", random_number, get_random_number_str_size());
        }
        [[nodiscard]] std::string encode_crc(const std::string& str) const noexcept {
            auto str_sum{ std::accumulate(std::cbegin(str), std::cend(str), 0,
                [pos = static_cast<int>(str.size() + 1)](auto total, unsigned char c) mutable {
                    return total + (c - '0') * pos--; }
            )};
            auto crc_modulo{ get_crc_modulo() };
            auto check_digit{ crc_modulo - (str_sum % crc_modulo) };
            return (check_digit == crc_modulo)
                ? std::to_string(0)
                : (check_digit >= 10) ? "X" : std::to_string(check_digit);
        }
    };


    class northeria_ssn_generator : public ssn_generator {
    public:
        static northeria_ssn_generator& get_instance() {
            static northeria_ssn_generator instance;
            return instance;
        }

    protected:
        [[nodiscard]] int get_sex_female_code() const noexcept override { return sex_female_code_; }
        [[nodiscard]] int get_sex_male_code() const noexcept override { return sex_male_code_; }
        [[nodiscard]] int get_random_number_max() const noexcept override { return random_number_max_; }
        [[nodiscard]] int get_random_number_str_size() const noexcept override { return random_number_str_size_; }
        [[nodiscard]] int get_crc_modulo() const noexcept override { return crc_modulo_; }

    private:
        northeria_ssn_generator() = default;

        static const int sex_female_code_{ 9 };
        static const int sex_male_code_{ 7 };
        static const int random_number_max_{ 99'999 };
        static const int random_number_str_size_{ 5 };
        static const int crc_modulo_{ 11 };
    };


    class southeria_ssn_generator : public ssn_generator {
    public:
        static southeria_ssn_generator& get_instance() {
            static southeria_ssn_generator instance;
            return instance;
        }

    protected:
        [[nodiscard]] int get_sex_female_code() const noexcept override { return sex_female_code_; }
        [[nodiscard]] int get_sex_male_code() const noexcept override { return sex_male_code_; }
        [[nodiscard]] int get_random_number_max() const noexcept override { return random_number_max_; }
        [[nodiscard]] int get_random_number_str_size() const noexcept override { return random_number_str_size_; }
        [[nodiscard]] int get_crc_modulo() const noexcept override { return crc_modulo_; }

    private:
        southeria_ssn_generator() = default;

        static const int sex_female_code_{ 1 };
        static const int sex_male_code_{ 2 };
        static const int random_number_max_{ 9'999 };
        static const int random_number_str_size_{ 4 };
        static const int crc_modulo_{ 10 };
    };
}  // namespace tmcppc::ssn


template <>
struct fmt::formatter<tmcppc::ssn::sex> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::ssn::sex& s, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", (s == tmcppc::ssn::sex::female) ? "Female" : "  Male");
    }
};

inline std::ostream& operator<<(std::ostream& os, const tmcppc::ssn::sex& s) {
    fmt::print(os, "{}", s);
    return os;
}


template <>
struct fmt::formatter<tmcppc::ssn::person> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::ssn::person& p, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "[{}, {:%Y/%b/%d}]", p.sex_, ch::sys_days(p.birth_date_));
    }
};

inline std::ostream& operator<<(std::ostream& os, const tmcppc::ssn::person& p) {
    fmt::print(os, "{}", p);
    return os;
}


void problem_69_main(std::ostream& os);
void problem_69_main();
