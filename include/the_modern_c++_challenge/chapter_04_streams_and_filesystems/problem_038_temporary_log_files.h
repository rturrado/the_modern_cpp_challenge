#pragma once

#include <boost/uuid/random_generator.hpp>  // random_generator
#include <boost/uuid/uuid_io.hpp>  // to_string
#include <filesystem>
#include <fstream>  // ofstream
#include <ostream>


namespace rtc::logger {
    namespace {
        namespace fs = std::filesystem;
        namespace uuids = boost::uuids;
    }

    struct could_not_open_file_error : public std::runtime_error {
        could_not_open_file_error(std::string_view error) : std::runtime_error(error.data()) {}
    };

    class logger {
    public:
        logger()
            : file_path_{ fs::temp_directory_path() / fs::path{ uuids::to_string(uuids::random_generator{}()) + ".log" } } {
            open_file();
        }

        [[nodiscard]] std::string get_file_path() const noexcept {
            return file_path_.generic_string();
        }

        void log(std::string_view text) noexcept {
            file_ << text.data();
        }

        void move_file(const fs::path& new_file_path) {
            if (new_file_path != file_path_)
            {
                close_file();  // close current file stream
                fs::rename(file_path_, new_file_path);  // move current file; this operation may throw
                file_path_ = new_file_path;
                moved = true;
                reopen_file();  // reopen moved file
            }
        }

        ~logger() noexcept {
            close_file();
            if (not moved) {
                remove_file();
            }
        }

    private:
        fs::path file_path_{};
        std::ofstream file_{};
        bool moved{ false };

        void open_file(std::ios_base::openmode mode = std::ios_base::out) {
            file_.open(file_path_.string(), mode);
            if (!file_) {
                throw could_not_open_file_error{ file_path_.string() };
            }
        }
        void reopen_file() {
            open_file(std::ios_base::app);
        }
        void close_file() {
            file_.close();
        }
        void remove_file() {
            fs::remove(file_path_);
        }
    };
}

void problem_38_main(std::ostream& os);
void problem_38_main();
