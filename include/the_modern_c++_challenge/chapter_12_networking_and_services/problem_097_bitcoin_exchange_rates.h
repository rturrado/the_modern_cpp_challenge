#pragma once

#include "chapter_12_networking_and_services/bitcoin.h"

#include <iosfwd>


namespace tmcppc::problem_97 {
    tmcppc::bitcoin::exchange_rates get_current_exchange_rates();
}  // namespace tmcppc::problem_97


void problem_97_main(std::ostream& os);
void problem_97_main();
