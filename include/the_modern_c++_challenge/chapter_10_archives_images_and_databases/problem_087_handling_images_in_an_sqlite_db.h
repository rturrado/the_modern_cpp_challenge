#pragma once

#include <filesystem>
#include <fmt/format.h>
#include <iosfwd>
#include <map>
#include <optional>
#include <regex>
#include <stdexcept>  // runtime_error
#include <string>
#include <vector>


namespace tmcppc::movies::command_line {
    namespace fs = std::filesystem;

    enum class command_t { add, help, list, quit, remove };
    enum class subcommand_t { media, movie };

    inline std::map<command_t, std::string> command_to_string{
        { command_t::add, "add" },
        { command_t::help, "help" },
        { command_t::list, "list" },
        { command_t::quit, "quit" },
        { command_t::remove, "remove" }
    };
    inline std::map<std::string, command_t> string_to_command{
        { "add", command_t::add },
        { "help", command_t::help },
        { "list", command_t::list },
        { "quit", command_t::quit},
        { "remove", command_t::remove }
    };
    inline std::map<subcommand_t, std::string> subcommmand_to_string{
        { subcommand_t::media, "media" },
        { subcommand_t::movie, "movie" }
    };
    inline std::map<std::string, subcommand_t> string_to_subcommand{
        { "media", subcommand_t::media },
        { "movie", subcommand_t::movie }
    };
    inline std::map<command_t, std::vector<subcommand_t>> command_to_subcommands{
        { command_t::list, { subcommand_t::media, subcommand_t::movie } }
    };


    struct command_line_options{
        int movie_id{};
        int media_id{};
        std::regex movie_title_regex{};
        fs::path media_file_path{};
        std::optional<std::string> media_file_description{};
    };


    struct command_not_found_error : public std::runtime_error {
        command_not_found_error(const std::string& command)
            : std::runtime_error{ message_ + command }
        {}
    private:
        static inline std::string message_{ "command not found: " };
    };
    struct subcommand_not_found_error : public std::runtime_error {
        subcommand_not_found_error(const std::string& subcommand)
            : std::runtime_error{ message_ + subcommand }
        {}
    private:
        static inline std::string message_{ "subcommand not found: " };
    };
    struct invalid_media_id_error : public std::runtime_error {
        invalid_media_id_error(const std::string& media_id_str)
            : std::runtime_error{ message_ + media_id_str }
        {}
    private:
        static inline std::string message_{ "invalid media ID: " };
    };
    struct invalid_movie_id_error : public std::runtime_error {
        invalid_movie_id_error(const std::string& movie_id_str)
            : std::runtime_error{ message_ + movie_id_str }
        {}
    private:
        static inline std::string message_{ "invalid movie ID: " };
    };
    struct invalid_subcommand_error : public std::runtime_error {
        invalid_subcommand_error(const std::string& command_str, const std::string& subcommand_str)
            : std::runtime_error{ "" }  {

            message_ = fmt::format("invalid subcommand '{}' for command '{}'", command_str, subcommand_str);
        }
        virtual const char* what() const noexcept override { return message_.c_str(); }
    private:
        std::string message_{};
    };
}  // namespace tmcppc::movies::command_line


void problem_87_main(std::istream& is, std::ostream& os);
void problem_87_main();
