#pragma once

#include <algorithm>  // sort
#include <cmath>  // sqrt
#include <vector>


namespace rtc::math
{
    // Check if a number is prime or not
    template <typename T>
    bool is_prime(const T n)
    {
        for (T i = 2; i < n; ++i) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }


    // Return the list of prime factors of a given number
    template <typename T>
    auto prime_factors(T n)
    {
        std::vector<T> ret{ 1 };
        while (n > 1) {
            T i = 2;
            for (; i < n; ++i) {
                if ((n % i == 0) && is_prime(i)) {
                    break;
                }
            }
            ret.push_back(i);
            n /= i;
        }
        return ret;
    }


    // Return the list of divisors of a given number
    template <typename T>
    auto divisors(const T n)
    {
        std::vector<T> ret{ 1 };
        for (T i = 2; i <= std::sqrt(n); ++i) {
            if (n % i == 0) {
                T j{ n / i };
                ret.push_back(i);
                if (i != j) {
                    ret.push_back(j);
                }
            }
        }
        std::sort(ret.begin(), ret.end());
        return ret;
    }


    // Return the sum of the divisors of a given number
    template <typename T>
    T divisors_sum(const T n)
    {
        T ret{ 1 };
        for (T i = 2; i <= std::sqrt(n); ++i) {
            if (n % i == 0) {
                T j{ n / i };
                ret += (i == j) ? i : (i + j);
            }
        }
        return ret;
    }
}  // namespace rtc::math


namespace rtc::math::tmp
{
    // I couldn't use the more efficient version of divisors starting from sqrt(N) and adding j=N/I when I!=j
    // <--- std::sqrt is not constexpr

    template <size_t N, size_t I>
    struct divisors_sum_helper
    {
    public:
        static constexpr size_t value = ((N % I == 0) ? I : 0) + divisors_sum_helper<N, I - 1>::value;
    };
    template <size_t N>
    struct divisors_sum_helper<N, 1>
    {
        static constexpr size_t value = 1;
    };
    template <size_t N>
    struct divisors_sum : divisors_sum_helper<N, N / 2> {};

    template <size_t N>
    struct amicable
    {
    private:
        static constexpr size_t m = divisors_sum<N>::value;
        static constexpr size_t p = divisors_sum<m>::value;
    public:
        static constexpr bool has_amicable = (N == p);
        static constexpr size_t value = m;
    };
}  // namespace rtc::math::tmp
