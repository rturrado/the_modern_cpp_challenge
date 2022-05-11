#pragma once

#include "phone_numbers.h"

#include <ostream>

using phone_numbers = tmcppc::phone_numbers;
using country_code = tmcppc::country_code;


void format_phone_numbers(phone_numbers& ph_nos, const country_code& cc);

void problem_51_main(std::ostream& os);
void problem_51_main();
