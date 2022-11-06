#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <ostream>
#include <sstream>  // ostringstream
#include <string>
#include <utility>  // move
#include <vector>


namespace tmcppc::process {
    enum class status_t : bool;
    enum class platform_t : bool;
}

// fmt formatters
template <>
struct fmt::formatter<tmcppc::process::status_t> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<tmcppc::process::platform_t> : fmt::ostream_formatter {};


namespace tmcppc::process {
    enum class status_t : bool { running, suspended };
    enum class platform_t : bool { x32, x64 };

    inline std::ostream& operator<<(std::ostream& os, const status_t& status) {
        return os << fmt::format("{}", status == status_t::running ? "Running" : "Suspended");
    }
    inline std::ostream& operator<<(std::ostream& os, const platform_t& platform) {
        return os << fmt::format("{}", platform == platform_t::x32 ? "32-bit" : "64-bit");
    }

    [[nodiscard]] inline std::string to_string(const status_t& status) {
        return fmt::format("{}", status);
    }
    [[nodiscard]] inline std::string to_string(const platform_t& platform) {
        return fmt::format("{}", platform);
    }

    class info {
    public:
        info(
            size_t id,
            std::string name,
            status_t status,
            std::string account_name,
            size_t mem_size_b,
            platform_t platform) noexcept

            : id_{ id }
            , name_{ std::move(name) }
            , status_{ status }
            , account_name_{ std::move(account_name) }
            , mem_size_b_{ mem_size_b }
            , platform_{ platform }
        {}

        info() = default;
        ~info() = default;
        info(const info& other) = default;
        info(info&& other) noexcept = default;
        info& operator=(const info& other) = default;
        info& operator=(info&& other) noexcept = default;

        [[nodiscard]] size_t id() const noexcept { return id_; }
        [[nodiscard]] std::string name() const noexcept { return name_; }
        [[nodiscard]] status_t status() const noexcept { return status_; }
        [[nodiscard]] std::string account_name() const noexcept { return account_name_; }
        [[nodiscard]] size_t mem_size_b() const noexcept { return mem_size_b_; }
        [[nodiscard]] platform_t platform() const noexcept { return platform_; }

        auto operator<=>(const info& other) const = default;

    private:
        size_t id_{};
        std::string name_{};
        status_t status_{};
        std::string account_name_{};
        size_t mem_size_b_{};
        platform_t platform_{};
    };
}  // namespace tmcppc::process


namespace tmcppc::problem_33 {
    using namespace tmcppc::process;

    void print_process_infos(std::ostream& os, std::vector<info>& infos);
}  // namespace tmcppc::problem_33


void problem_33_main(std::ostream& os);
