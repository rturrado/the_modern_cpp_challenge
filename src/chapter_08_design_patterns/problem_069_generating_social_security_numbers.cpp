#include "chapter_08_design_patterns/problem_069_generating_social_security_numbers.h"
#include "rtc/random.h"

#include <algorithm>  // binary_search, sort
#include <chrono>
#include <format>
#include <initializer_list>
#include <iomanip>  // setfill, setw
#include <iostream>  // cout
#include <numeric>  // accumulate
#include <sstream>  // ostringstream
#include <string>  // to_string
#include <unordered_map>
#include <vector>

namespace ch = std::chrono; using namespace ch;

enum class Sex { FEMALE, MALE };

std::ostream& operator<<(std::ostream& os, const Sex& s) { return os << (s == Sex::FEMALE ? "Female" : "  Male"); }

struct Person
{
    Sex sex_{};
    ch::year_month_day birth_date_{};
};

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    return os << "{ " << p.sex_ << ", " << std::format("{:%Y/%b/%d}", p.birth_date_) << " }";
}


class SSN_Generator
{
public:
    virtual ~SSN_Generator() = default;

    template <typename Person>
    [[nodiscard]] std::string generate(Person&& p)
    {
        auto ymd{ encode_birth_date(p.birth_date_) };
        std::ostringstream oss{};
        oss << encode_sex(p.sex_) << ymd << encode_random_number(ymd) << encode_crc(oss.str());
        return oss.str();
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

    [[nodiscard]] std::string encode_sex(Sex sex) const noexcept
    {
        return (sex == Sex::FEMALE ? std::to_string(get_sex_female_code()) : std::to_string(get_sex_male_code()));
    }
    [[nodiscard]] std::string encode_birth_date(const ch::year_month_day& birth_date) const noexcept
    {
        std::ostringstream oss{};
        oss << std::format("{:%Y%m%d}", birth_date);
        return oss.str();
    }
    [[nodiscard]] std::string encode_random_number(const std::string& birth_date_str) const noexcept
    {
        rtc::random::RandomInt random_int{ 0, get_random_number_max() };

        for (;;)
        {
            const auto rn_str{ random_number_to_string(random_int()) };
            
            if (random_number_str_cache_.contains(rn_str))
            {
                auto& v{ random_number_str_cache_.find(rn_str)->second };
                if (std::binary_search(std::cbegin(v), std::cend(v), birth_date_str)) { continue; }

                v.push_back(birth_date_str);
                std::sort(std::begin(v), std::end(v));
                return rn_str;
            }
            else
            {
                random_number_str_cache_[rn_str] = vector_of_date_str{ birth_date_str };
                return rn_str;
            }
        }
    }
    [[nodiscard]] std::string random_number_to_string(const int random_number) const noexcept
    {
        std::ostringstream oss{};
        oss << std::setw(get_random_number_str_size()) << std::setfill('0') << random_number;
        return oss.str();
    }
    [[nodiscard]] std::string encode_crc(const std::string& str) const noexcept
    {
        auto str_sum{ std::accumulate(std::cbegin(str), std::cend(str), 0,
            [pos = static_cast<int>(str.size() + 1)](auto total, unsigned char c) mutable {
                return total + (c - '0') * pos--; }
        ) };
        auto crc_modulo{ get_crc_modulo() };
        auto check_digit{ crc_modulo - (str_sum % crc_modulo) };
        if (check_digit == crc_modulo) { check_digit = 0; }
        else if (check_digit >= 10) { return "X"; }
        return std::to_string(check_digit);
    }
};


class Northeria_SSN_Generator : public SSN_Generator
{
public:
    static Northeria_SSN_Generator& get_instance() { static Northeria_SSN_Generator instance; return instance; }

protected:
    [[nodiscard]] virtual int get_sex_female_code() const noexcept override { return sex_female_code_; }
    [[nodiscard]] virtual int get_sex_male_code() const noexcept override {  return sex_male_code_; }
    [[nodiscard]] virtual int get_random_number_max() const noexcept override { return random_number_max_; }
    [[nodiscard]] virtual int get_random_number_str_size() const noexcept override {  return random_number_str_size_; }
    [[nodiscard]] virtual int get_crc_modulo() const noexcept override { return crc_modulo_; }

private:
    Northeria_SSN_Generator() = default;

    static const int sex_female_code_{ 9 };
    static const int sex_male_code_{ 7 };
    static const int random_number_max_{ 99'999 };
    static const int random_number_str_size_{ 5 };
    static const int crc_modulo_{ 11 };
};


class Southeria_SSN_Generator : public SSN_Generator
{
public:
    static Southeria_SSN_Generator& get_instance() { static Southeria_SSN_Generator instance; return instance; }

protected:
    [[nodiscard]] virtual int get_sex_female_code() const noexcept override { return sex_female_code_; }
    [[nodiscard]] virtual int get_sex_male_code() const noexcept override { return sex_male_code_; }
    [[nodiscard]] virtual int get_random_number_max() const noexcept override { return random_number_max_; }
    [[nodiscard]] virtual int get_random_number_str_size() const noexcept override { return random_number_str_size_; }
    [[nodiscard]] virtual int get_crc_modulo() const noexcept override { return crc_modulo_; }

private:
    Southeria_SSN_Generator() = default;

    static const int sex_female_code_{ 1 };
    static const int sex_male_code_{ 2 };
    static const int random_number_max_{ 9'999 };
    static const int random_number_str_size_{ 4 };
    static const int crc_modulo_{ 10 };
};


// Generating social security numbers
//
// Write a program that can generate social security numbers for two countries, Northeria and Southeria,
// that have different but similar formats for the numbers:
//
// - In Northeria, the numbers have the format SYYYYMMDDNNNNNC, where
//   S is a digit representing the sex, 9 for females and 7 for males,
//   YYYYMMDD is the birth date,
//   NNNNN is a five-digit random number, unique for a day
//   (meaning that the same number can appear twice for two different dates, but not the same date), and
//   C is a digit picked so that the checksum computed as described later is a multiple of 11.
//
// - In Southeria, the numbers have the format SYYYYMMDDNNNNC, where
//   S is a digit representing the sex, 1 for females and 2 for males,
//   YYYYMMDD is the birth date,
//   NNNN is a four-digit random number, unique for a day, and
//   C is a digit picked so that the checksum computed as described below is a multiple of 10.
//
// The checksum in both cases is a sum of all the digits, each multiplied by its weight
// (the position from the most significant digit to the least).
// For example, the checksum for the Southerian number 12017120134895 is computed as follows:
//
//   crc = 14*1 + 13*2 + 12*0 + 11*1 + 10*7 + 9*1 + 8*2 + 7*0 + 6*1 + 5*3 + 4*4 + 3*8 + 2*9 + 1*5 = 230 = 23*10
void problem_69_main()
{
    using namespace std::chrono_literals;

    auto ng{ Northeria_SSN_Generator::get_instance() };
    auto sg{ Southeria_SSN_Generator::get_instance() };

    for (auto&& p : std::initializer_list<Person>{
        { Sex::FEMALE, 1970y / January / 1 },
        { Sex::FEMALE, 1976y / February / 3 },
        { Sex::FEMALE, 1982y / March / 5 },
        { Sex::FEMALE, 1988y / May / 8 },
        { Sex::FEMALE, 1994y / July / 11 },
        { Sex::MALE, 2000y / August / 14 },
        { Sex::MALE, 2006y / September / 18 },
        { Sex::MALE, 2012y / October / 22 },
        { Sex::MALE, 2018y / November / 26 },
        { Sex::MALE, 2021y / December / 31 } })
    {
        std::cout << "SSNs for " << p << ": Northerian = " << ng.generate(p) << ", and Southerian = " << sg.generate(p) << "\n";
    }

    std::cout << "\n";
}
