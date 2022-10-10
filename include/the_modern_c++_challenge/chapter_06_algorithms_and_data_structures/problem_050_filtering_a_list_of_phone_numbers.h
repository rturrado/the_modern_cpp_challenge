#pragma once

#include "phone_numbers.h"

#include <iosfwd>


namespace tmcppc::problem_50 {
    using phone_numbers = tmcppc::phone::numbers;
    using country_code = tmcppc::phone::country_code;

    phone_numbers filter_phone_numbers_by_country_code(const phone_numbers& ph_nos, const country_code& cc);
}  // namespace tmcppc::problem_50


void problem_50_main(std::ostream& os);
