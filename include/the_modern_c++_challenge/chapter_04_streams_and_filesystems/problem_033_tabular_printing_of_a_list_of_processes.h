#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <ostream>
#include <sstream>  // ostringstream
#include <string>
#include <vector>


namespace tmcppc::process {
    enum class status_t : bool { running, suspended };
    enum class platform_t : bool { x32, x64 };

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
            , name_{ name }
            , status_{ status }
            , account_name_{ account_name }
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


template <>
struct fmt::formatter<tmcppc::process::status_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::process::status_t& status, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", status == tmcppc::process::status_t::running ? "Running" : "Suspended");
    }
};

inline std::ostream& operator<<(std::ostream& os, const tmcppc::process::status_t& status) {
    fmt::print(os, "{}", status);
    return os;
}

inline std::string to_string(const tmcppc::process::status_t& status) {
    return fmt::format("{}", status);
}


template <>
struct fmt::formatter<tmcppc::process::platform_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::process::platform_t& platform, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", platform == tmcppc::process::platform_t::x32 ? "32-bit" : "64-bit");
    }
};

inline std::ostream& operator<<(std::ostream& os, const tmcppc::process::platform_t& platform) {
    fmt::print(os, "{}", platform);
    return os;
}

inline std::string to_string(const tmcppc::process::platform_t& platform) {
    return fmt::format("{}", platform);
}


namespace tmcppc::problem_33 {
    using namespace tmcppc::process;

    void print_process_infos(std::ostream& os, std::vector<info>& infos);
}  // namespace tmcppc::problem_33


void problem_33_main(std::ostream& os);
void problem_33_main();
