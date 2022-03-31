#ifndef DIGITS_H
#define DIGITS_H

#include <deque>
#include <limits>  // numeric_limits


namespace rtc::math
{
    template <typename T>
    requires std::numeric_limits<T>::is_integer && (!std::numeric_limits<T>::is_signed)
    class digits
    {
    public:
        digits() {}

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

        size_t size() { return data_.size(); }

        digits<T>& operator++()
        {
            for (auto it = data_.rbegin(); it != data_.rend(); ++it) {
                auto& digit = *it;
                if (digit == 9) {
                    digit = 0;
                }
                else {
                    digit++;
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
            for (auto it = data_.rbegin(); it != data_.rend(); ++it) {
                auto& digit = *it;
                if (digit == 0) {
                    digit = 9;
                }
                else {
                    digit--;
                    break;
                }
            }
            if (data_.size() > 0 && data_.front() == 0) {
                data_.pop_front();
            }
            return *this;
        }

        auto cbegin() { return data_.cbegin(); }
        auto cend() { return data_.cend(); }

    private:
        std::deque<T> data_{ 0 };
    };

}  // namespace rtc::math


#endif  // DIGITS_H
