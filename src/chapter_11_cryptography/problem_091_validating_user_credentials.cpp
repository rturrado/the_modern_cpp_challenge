#include "chapter_11_cryptography.h"

#include "rtc/console.h"

#include <iostream>  // cout
#include <stdexcept>  // runtime_error
#include <string>

#include "cryptocpp/cryptlib.h"
#include "cryptocpp/sha.h"


class Login
{
private:
    using username_t = std::string;
    using password_t = std::string;
    static inline std::map<username_t, password_t> login_info_{};

    static inline std::string SHA1HashString(const std::string& text)
    {
        static CryptoPP::byte digest[CryptoPP::SHA1::DIGESTSIZE];
        CryptoPP::SHA1{}.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(text.data()), text.size());
        return std::string{ std::cbegin(digest), std::cend(digest) };
    }

public:
    struct UserExistsError : std::runtime_error
    {
        UserExistsError(const std::string& username) : std::runtime_error{ message_ + username } {}
    private:
        static inline std::string message_{ "Error: user already exits: " };
    };

    static inline void add_user(const std::string& username, const std::string& password) {
        if (exists_user(username)) {
            throw UserExistsError{ username };
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


class LoginSimulator
{
private:
    LoginSimulator()
    {
        Login::add_user("marcos", "zuck3rb3rg!");
        Login::add_user("bill", "w1ndoze&g4tes");
        Login::add_user("samantha", "f0xxx");
        Login::add_user("michelle", "fail4her");
    }

public:
    static LoginSimulator& get_instance()
    {
        static LoginSimulator instance;
        return instance;
    }

    void run()
    {
        for (;;)
        {
            std::cout << "Please enter username ('quit' for exiting): ";
            std::string username{};
            std::getline(std::cin, username);

            if (username == "quit") {
                break;
            }
            if (not Login::exists_user(username)) {
                std::cout << "\tError: username not found\n";
                continue;
            }

            std::cout << "Please enter password: ";
            std::string password{};
            std::getline(std::cin, password);
            if (Login::is_valid_password(username, password)) {
                std::cout << "\tError: incorrect password\n";
                continue;
            }
            else {
                std::cout << "\tOK: access granted\n";
            }
        }
    }
};


// Validating user credentials
//
// Write a program that simulates the way users authenticate to a secured system.
// In order to log in, a user must be already registered with the system.
// The user enters a username and a password and the program checks if it matches any of its registered users;
// if it does, the user is granted access, otherwise, the operation fails.
// For security reasons, the system must not record the password but use an SHA hash instead.
void problem_91_main()
{
    LoginSimulator::get_instance().run();
    std::cout << "\n";
}
