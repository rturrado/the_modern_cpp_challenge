#pragma once

#include "phone_numbers.h"

#include <ostream>


phone_numbers filter_phone_numbers_by_country_code(const phone_numbers& ph_nos, const country_code& cc);

void problem_50_main(std::ostream& os);
void problem_50_main();
