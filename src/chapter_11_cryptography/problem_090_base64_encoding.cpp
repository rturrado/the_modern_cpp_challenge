#include "chapter_11_cryptography/base64.h"
#include "chapter_11_cryptography/problem_090_base64_encoding.h"
#include "env.h"

#include "rtc/filesystem.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>
#include <string_view>


namespace tmcppc::problem_90 {
    using base64 = tmcppc::crypto::base64;

    void test_base_64(std::ostream& os, const base64::data_t& input_data, bool use_padding) {
        static const auto b64{ base64{} };
        const auto encoded_data{ b64.encode(input_data, use_padding) };
        const auto decoded_data{ b64.decode(encoded_data) };

        if (input_data == decoded_data) {
            fmt::print(os, "\tOK\n");
        } else {
            fmt::print(os, "\tError: the decoded data differs from the input data\n");
        }
    }
}  // namespace tmcppc::problem_90


void problem_90_main(std::ostream& os) {
    using namespace tmcppc::problem_90;

    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    const auto input_file_content{ rtc::filesystem::get_binary_file_content<base64::value_type>(input_file_path) };

    fmt::print(os, "Encoding and decoding file '{}'\n", input_file_path.generic_string());
    test_base_64(os, input_file_content);

    for (std::string_view input_data : { "", "M", "Ma", "Man", "Many", "Many ", "Many h", "Many hands make light work." }) {
        for (auto use_padding : { true, false }) {
            fmt::print(os, "Encoding and decoding text '{}'\n", input_data);
            test_base_64(os, base64::data_t{ std::cbegin(input_data), std::cend(input_data) }, use_padding);
        }
    }

    fmt::print(os, "\n");
}


// Base64 encoding and decoding
//
// Write a program that can encode and decode binary data using the base64 encoding scheme.
// You must implement the encoding and decoding functions yourself and not use a 3rd party library.
// The table used for encoding should be the one from the MIME specification.
void problem_90_main() {
    problem_90_main(std::cout);
}
