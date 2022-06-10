#pragma once

#include <fmt/ostream.h>
#include <istream>
#include <ostream>
#include <stdexcept>  // runtime_error
#include <string>  // getline

#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"


namespace tmcppc::crypto {
    class login {
    private:
        using username_t = std::string;
        using password_t = std::string;
        static inline std::map<username_t, password_t> login_info_{};

        static inline std::string SHA1HashString(const std::string& text) {
            static CryptoPP::byte digest[CryptoPP::SHA1::DIGESTSIZE];
            CryptoPP::SHA1{}.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(text.data()), text.size());
            return std::string{ std::cbegin(digest), std::cend(digest) };
        }

    public:
        struct user_exists_error : std::runtime_error {
            user_exists_error(const std::string& username) : std::runtime_error{ message_ + username } {}
        private:
            static inline std::string message_{ "Error: user already exits: " };
        };

        static inline void add_user(const std::string& username, const std::string& password) {
            if (exists_user(username)) {
                throw user_exists_error{ username };
            }
            login_info_[username] = SHA1HashString(password);
        };
        [[nodiscard]] static inline bool exists_user(const std::string& username) {
            return login_info_.contains(username);
        }
        [[nodiscard]] static inline bool is_valid_password(const std::string& username, const std::string& password) {
            return login_info_.contains(username) and login_info_[username] != SHA1HashString(password);
        }
    };


    class login_simulator {
    private:
        login_simulator(std::istream& is, std::ostream& os)
            : is_{ is }, os_{ os } {
            
            login::add_user("marcos", "zuck3rb3rg!");
            login::add_user("bill", "w1ndoze&g4tes");
            login::add_user("samantha", "f0xxx");
            login::add_user("michelle", "fail4her");
        }

    public:
        static login_simulator& get_instance(std::istream& is, std::ostream& os) {
            static login_simulator instance{ is, os };
            return instance;
        }

        void run() {
            for (;;) {
                fmt::print(os_, "Please enter username ('quit' for exiting): ");
                std::string username{};
                std::getline(is_, username);

                if (username == "quit") {
                    break;
                }
                if (not login::exists_user(username)) {
                    fmt::print(os_, "\tError: username not found\n");
                    continue;
                }

                fmt::print(os_, "Please enter password: ");
                std::string password{};
                std::getline(is_, password);
                if (login::is_valid_password(username, password)) {
                    fmt::print(os_, "\tError: incorrect password\n");
                    continue;
                } else {
                    fmt::print(os_, "\tOK: access granted\n");
                }
            }
        }
    private:
        std::istream& is_;
        std::ostream& os_;
    };
}  // namespace tmcppc::crypto


void problem_91_main(std::istream& is, std::ostream& os);
void problem_91_main();
