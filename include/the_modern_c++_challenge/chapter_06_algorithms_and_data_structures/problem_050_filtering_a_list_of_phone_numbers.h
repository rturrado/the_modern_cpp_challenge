#pragma once

#include "phone_numbers.h"

#include <iosfwd>

using phone_numbers = tmcppc::phone_numbers;
using country_code = tmcppc::country_code;


phone_numbers filter_phone_numbers_by_country_code(const phone_numbers& ph_nos, const country_code& cc);

void problem_50_main(std::ostream& os);
void problem_50_main();
