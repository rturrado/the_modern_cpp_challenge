#pragma once

#include "chapter_11_cryptography/base64.h"

#include <iosfwd>
#include <vector>


namespace tmcppc::problem_90 {
    using base64 = tmcppc::crypto::base64;

    void test_base_64(std::ostream& os, const std::vector<base64::value_type>& input_data, bool use_padding = true);
}  // namespace tmcppc::problem_90


void problem_90_main(std::ostream& os);
