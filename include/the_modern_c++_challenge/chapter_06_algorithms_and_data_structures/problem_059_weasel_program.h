#pragma once

#include "rtc/random.h"

#include <algorithm>  // copy
#include <functional>  // plus
#include <iosfwd>
#include <iterator>  // ostream_iterator
#include <numeric>  // transform_reduce
#include <sstream>  // ostringstream
#include <string>


class weasel_sequence {
public:
    // Fill data_ randomly
    weasel_sequence(const std::string& target)
        : target_{ target }, data_(target.size(), '\0') {

        for (char& c : data_) {
            c = get_random_letter();
        }
    }

    // Choose one element of data_ randomly
    // Fill that element randomly
    void mutate() noexcept {
        data_[get_random_index()] = get_random_letter();
    }

    [[nodiscard]] constexpr size_t size() const noexcept {
        return target_.size();
    }

    // Return number of characters that are equal to the target string
    [[nodiscard]] size_t score() const noexcept {
        return std::transform_reduce(
            std::cbegin(data_), std::end(data_), std::cbegin(target_),
            static_cast<size_t>(0),
            std::plus<>{},
            [](char c, char t) { return (c == t) ? 1 : 0; });
    }

    [[nodiscard]] bool end() const noexcept {
        return score() == size();
    }

    [[nodiscard]] std::string str() const noexcept {
        std::ostringstream oss{};
        std::copy(std::cbegin(data_), std::cend(data_), std::ostream_iterator<char>(oss));
        return oss.str();
    }

private:
    std::string target_{};
    std::string data_{};

    size_t get_random_index() {
        return get_random_int(0, static_cast<int>(size()) - 1);
    }

    static char get_random_letter() {
        static rtc::random::random_letter random_letter_{};
        return random_letter_();
    }
    static size_t get_random_int(int low, int high) {
        static rtc::random::random_int random_int_{ low, high };
        return random_int_();
    }
};


void problem_59_main(std::ostream& os);
void problem_59_main();
