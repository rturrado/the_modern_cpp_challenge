#pragma once

#include <algorithm>  // transform
#include <deque>
#include <limits>  // numeric_limits
#include <string>


namespace rtc::math
{
    template <typename T>
    requires std::numeric_limits<T>::is_integer && (!std::numeric_limits<T>::is_signed)
    class digits
    {
    public:
        digits() : data_{0} {}

        digits(T n)
        {
            if (n == 0) {
                data_.push_back(0);
            }
            else {
                for (; n != 0; n /= 10) {
                    data_.push_front(n % 10);
                }
            }
        }

        [[nodiscard]] size_t size() const { return data_.size(); }

        [[nodiscard]] std::string to_string() const
        {
            std::string ret(data_.size(), '0');
            std::transform(data_.cbegin(), data_.cend(), ret.begin(),
                [](const auto& n) { return static_cast<char>(n) + '0'; });
            return ret;
        }

        digits<T>& operator++()
        {
            for (auto it = data_.rbegin(); it != data_.rend(); ++it) {
                auto& digit = *it;
                if (digit == 9) {
                    digit = 0;
                }
                else {
                    ++digit;
                    break;
                }
            }
            if (data_.size() >= 0 && data_.front() == 0) {
                data_.push_front(1);
            }
            return *this;
        }

        digits<T>& operator--()
        {
            if (data_.size() == 1 and data_.front() == 0) {
                return *this;
            }
            for (auto it = data_.rbegin(); it != data_.rend(); ++it) {
                auto& digit = *it;
                if (digit == 0) {
                    digit = 9;
                }
                else {
                    --digit;
                    break;
                }
            }
            if (data_.size() > 0 and data_.front() == 0) {
                data_.pop_front();
            }
            return *this;
        }

        [[nodiscard]] auto cbegin() const { return data_.cbegin(); }
        [[nodiscard]] auto cend() const { return data_.cend(); }

    private:
        std::deque<T> data_{};
    };

}  // namespace rtc::math
