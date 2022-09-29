#pragma once

#include "../sql/movies.h"
#include "chapter_09_data_serialization/movies.h"

#include <algorithm>  // find
#include <cstdint>  // int64_t
#include <exception>
#include <filesystem>
#include <fmt/format.h>
#include <istream>
#include <map>
#include <optional>
#include <ostream>
#include <ranges>
#include <regex>  // regex_match, smatch
#include <rtc/stream.h>  // get_unread
#include <rtc/string.h>  // to_lowercase, trim_right
#include <sstream>  // istringstream
#include <string>  // getline, stoi
#include <tuple>
#include <vector>


namespace tmcppc::movies::command_line {
    namespace fs = std::filesystem;

    enum class command_t { add, help, list, quit, remove };

    enum class subcommand_t { media, movie };

    struct command_line_options {
        std::int64_t movie_id{};
        std::int64_t media_id{};
        std::regex movie_title_regex{};
        std::filesystem::path media_file_path{};
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
    struct invalid_regex_error : public std::runtime_error {
        invalid_regex_error(const std::string& regex_str)
            : std::runtime_error{ message_ + regex_str }
        {}
    private:
        static inline std::string message_{ "invalid regex: " };
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


    void print_usage(std::ostream& os) {
        fmt::print(os, "Usage:\n");
        fmt::print(os, "\tlist movie <movie_title_regex>\n");
        fmt::print(os, "\tlist media <movie_id>\n");
        fmt::print(os, "\tadd <movie_id>, <media_file_path>, [<media_file_description>]\n");
        fmt::print(os, "\tremove <media_id>\n");
        fmt::print(os, "\thelp\n");
        fmt::print(os, "\tquit\n");
        fmt::print(os, "Where:\n");
        fmt::print(os, "\tmedia_file_description  Optional media file description.\n");
        fmt::print(os, "\tmedia_file_path         File path pointing to a media file.\n");
        fmt::print(os, "\tmedia_id                Media ID, as shown when listing a media file.\n");
        fmt::print(os, "\tmovie_id                Movie ID, as shown when listing a movie.\n");
        fmt::print(os, "\tmovie_title_regex       Regular expression for a movie title.\n");
        fmt::print(os, "Examples:\n");
        fmt::print(os, "\tlist movie .*The.*\n");
        fmt::print(os, "\tlist media 2\n");
        fmt::print(os, "\tadd 2, ./res/db/poster.png, Front cover\n");
        fmt::print(os, "\tremove 1\n");
    }


    auto read_command_line(std::istream& is, std::ostream& os) {
        fmt::print(os, "(help for usage) > ");
        std::string command_line{};
        std::getline(is, command_line);
        return command_line;
    }


    void parse_command(std::istringstream& iss, command_t& command) {
        std::string command_str{};
        iss >> command_str;
        command_str = rtc::string::to_lowercase(command_str);
        if (not string_to_command.contains(command_str)) {
            throw command_not_found_error{ command_str };
        }
        command = string_to_command[command_str];
    }


    void parse_subcommand(std::istringstream& iss, const command_t& command, subcommand_t& subcommand) {
        if (not command_to_subcommands.contains(command)) {  // this command has no subcommands
            return;
        }

        std::string subcommand_str{};
        iss >> subcommand_str;
        subcommand_str = rtc::string::to_lowercase(subcommand_str);
        if (not string_to_subcommand.contains(subcommand_str)) {  // this subcommand does not exist
            throw subcommand_not_found_error{ subcommand_str };
        }
        subcommand = string_to_subcommand[subcommand_str];

        auto& valid_subcommands{ command_to_subcommands[command] };
        if (std::ranges::find(valid_subcommands, subcommand) == std::cend(valid_subcommands)) {  // this command does not accept this subcommand
            throw invalid_subcommand_error{ command_to_string[command], subcommand_str };
        }
    }

    void parse_media_id_option(std::istringstream& iss, command_line_options& options) {
        std::string media_id_str{};
        iss >> media_id_str;
        try {
            options.media_id = std::stoi(media_id_str);
        } catch (const std::exception&) {
            throw invalid_media_id_error{ media_id_str };
        }
    }

    void parse_movie_id_option(std::istringstream& iss, command_line_options& options) {
        std::string movie_id_str{};
        iss >> movie_id_str;
        try {
            options.movie_id = std::stoi(movie_id_str);
        } catch (const std::exception&) {
            throw invalid_movie_id_error{ movie_id_str };
        }
    }

    void parse_movie_title_regex_option(std::istringstream& iss, command_line_options& options) {
        std::string movie_title_regex_str{};
        iss >> movie_title_regex_str;
        try {
            options.movie_title_regex = movie_title_regex_str;
        } catch (const std::exception&) {
            throw invalid_regex_error{ movie_title_regex_str };
        }
    }

    void parse_add_options(std::istringstream& iss, command_line_options& options) {
        std::string line{ rtc::stream::get_unread(iss) };
        std::smatch matches{};
        const std::regex pattern{ R"(\s*([\d]+)\s*,\s*([^,]+)(?:,\s*(.*))?)" };
        if (std::regex_match(line, matches, pattern)) {
            options.movie_id = std::stoll(matches[1].str());
            options.media_file_path = rtc::string::trim_right(matches[2].str());
            if (matches.size() == 4) {
                options.media_file_description = rtc::string::trim_right(matches[3].str());
            }
        }
    }

    void parse_list_media_options(std::istringstream& iss, command_line_options& options) {
        parse_movie_id_option(iss, options);
    }

    void parse_list_movie_options(std::istringstream& iss, command_line_options& options) {
        parse_movie_title_regex_option(iss, options);
    }

    void parse_remove_options(std::istringstream& iss, command_line_options& options) {
        parse_media_id_option(iss, options);
    }

    auto parse_command_line(std::string command_line) {
        std::istringstream iss{ command_line };

        command_t command{}; parse_command(iss, command);
        subcommand_t subcommand{}; parse_subcommand(iss, command, subcommand);

        command_line_options options{};
        switch (command) {
            case command_t::add: {
                parse_add_options(iss, options);
                break;
            }
            case command_t::help: break;
            case command_t::list: {
                switch (subcommand) {
                    case subcommand_t::media: {
                        parse_list_media_options(iss, options);
                        break;
                    }
                    case subcommand_t::movie: {
                        parse_list_movie_options(iss, options);
                        break;
                    }
                    default: break;
                };
                break;
            }
            case command_t::quit: break;
            case command_t::remove: {
                parse_remove_options(iss, options);
                break;
            }
            default: break;
        }

        return std::tuple<command_t, subcommand_t, command_line_options>{ command, subcommand, options };
    }


    void add_media(std::ostream& os, tmcppc::movies::sql::database& movies_db,
        std::int64_t movie_id, const fs::path& media_file_path, std::optional<std::string> media_file_description) {

        if (not fs::exists(media_file_path)) {
            fmt::print(os, "Error: media file not found: {}\n", media_file_path.generic_string());
            return;
        }

        try {
            auto media_file{ tmcppc::movies::media_file{ movie_id, media_file_path, media_file_description } };
            movies_db.insert_media_file(movie_id, media_file);
            fmt::print(os, "{}\n", movies_db);
        } catch (const tmcppc::movies::sql::movie_id_not_found_error& ex) {
            fmt::print(os, "Error: {}\n", ex.what());
        }
    }

    void delete_media(std::ostream& os, tmcppc::movies::sql::database& movies_db, std::int64_t media_id) {
        try {
            movies_db.delete_media_file(media_id);
            fmt::print(os, "{}\n", movies_db);
        } catch (const tmcppc::movies::sql::media_file_id_not_found_error& ex) {
            fmt::print(os, "Error: {}\n", ex.what());
        }
    }

    void list_media(std::ostream& os, const tmcppc::movies::sql::database& movies_db, std::int64_t movie_id) {
        try {
            fmt::print(os, "{}\n", movies_db.get_media_files(movie_id));
        } catch (const tmcppc::movies::sql::movie_id_not_found_error& ex) {
            fmt::print(os, "Error: {}\n", ex.what());
        }
    }

    void list_movies(std::ostream& os, const tmcppc::movies::sql::database& movies_db, const std::regex& pattern) {
        fmt::print(os, "{}\n", movies_db.get_movies(pattern));
    }

    void execute_command(std::ostream& os, tmcppc::movies::sql::database& movies_db,
        const command_t command, const subcommand_t subcommand, const command_line_options& options) {

        switch (command) {
            case command_t::add: {
                add_media(os, movies_db, options.movie_id, options.media_file_path, options.media_file_description);
                break;
            }
            case command_t::help: {
                print_usage(os);
                break;
            }
            case command_t::list:
                switch (subcommand) {
                    case subcommand_t::media: {
                        list_media(os, movies_db, options.movie_id);
                        break;
                    }
                    case subcommand_t::movie: {
                        list_movies(os, movies_db, options.movie_title_regex);
                        break;
                    }
                    default: break;
                };
                break;
            case command_t::remove: {
                delete_media(os, movies_db, options.media_id);
                break;
            }
            default: break;
        }
    }


    void menu(std::istream& is, std::ostream& os, tmcppc::movies::sql::database& movies_db) {
        for (;;) {
            try {
                auto command_line{ read_command_line(is, os) };

                auto [command, subcommand, options] = parse_command_line(command_line);

                if (command == command_t::quit) {
                    break;
                }

                execute_command(os, movies_db, command, subcommand, options);

                fmt::print(os, "\n");
            } catch (const std::exception& ex) {
                fmt::print(os, "Error: {}\n\n", ex.what());
            }
        }
    }
}  // namespace tmcppc::movies::command_line
