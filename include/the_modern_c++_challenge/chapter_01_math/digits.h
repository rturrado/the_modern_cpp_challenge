#ifndef DIGITS_H
#define DIGITS_H

#include <deque>
#include <limits>  // numeric_limits

template <typename T>
requires std::numeric_limits<T>::is_integer && (!std::numeric_limits<T>::is_signed)
class Digits
{
public:
    Digits() {}
    Digits(T n);
    size_t size() { return digits.size(); }
    Digits<T>& operator++();
    Digits<T>& operator--();
    auto cbegin() { return digits.cbegin(); }
    auto cend() { return digits.cend(); }
private:
    std::deque<T> digits{ 0 };
};

template <typename T>
requires std::numeric_limits<T>::is_integer && (!std::numeric_limits<T>::is_signed)
Digits<T>::Digits(T n)
{
    if (n == 0)
    {
        digits.push_back(0);
    }
    else
    {
        for (; n != 0; n /= 10)
        {
            digits.push_front(n % 10);
        }
    }
}

template <typename T>
requires std::numeric_limits<T>::is_integer && (!std::numeric_limits<T>::is_signed)
Digits<T>& Digits<T>::operator++()
{
    for (auto it = digits.rbegin(); it != digits.rend(); ++it)
    {
        auto& digit = *it;
        if (digit == 9)
        {
            digit = 0;
        }
        else
        {
            digit++;
            break;
        }
    }
    if (digits.size() >= 0 && digits.front() == 0)
    {
        digits.push_front(1);
    }
    return *this;
}

template <typename T>
requires std::numeric_limits<T>::is_integer && (!std::numeric_limits<T>::is_signed)
Digits<T>& Digits<T>::operator--()
{
    for (auto it = digits.rbegin(); it != digits.rend(); ++it)
    {
        auto& digit = *it;
        if (digit == 0)
        {
            digit = 9;
        }
        else
        {
            digit--;
            break;
        }
    }
    if (digits.size() > 0 && digits.front() == 0)
    {
        digits.pop_front();
    }
    return *this;
}

#endif  // DIGITS_H
