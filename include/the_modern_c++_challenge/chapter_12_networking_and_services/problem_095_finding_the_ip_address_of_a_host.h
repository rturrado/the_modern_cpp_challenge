#pragma once

#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>


namespace tmcppc::problem_95 {
    std::vector<std::string> get_host_ipv4_addresses(std::string_view host, std::string_view service);
}  // namespace tmcppc::problem_95


void problem_95_main(std::ostream& os);
void problem_95_main();
