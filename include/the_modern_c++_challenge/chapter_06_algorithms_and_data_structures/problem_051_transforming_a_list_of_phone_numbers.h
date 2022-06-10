#pragma once

#include "phone_numbers.h"

#include <iosfwd>


namespace tmcppc::problem_51 {
    using phone_numbers = tmcppc::phone::numbers;
    using country_code = tmcppc::phone::country_code;

    void format_phone_numbers(phone_numbers& ph_nos, const country_code& cc);
}  // namespace tmcppc::problem_51


void problem_51_main(std::ostream& os);
void problem_51_main();
