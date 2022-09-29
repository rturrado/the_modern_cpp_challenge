#pragma once

#include <cstddef>  // ptrdiff_t
#include <fmt/format.h>
#include <pugixml.hpp>
#include <stdexcept>  // runtime_error
#include <string>


namespace tmcppc::pugixml {
    // Runtime errors
    struct attribute_error : public std::runtime_error {
        attribute_error(const std::string& name) : std::runtime_error{ message_ + name } {}
    private:
        static inline std::string message_{ "trying to access attribute " };
    };

    struct child_error : public std::runtime_error {
        child_error(const std::string& name) : std::runtime_error{ message_ + name } {}
    private:
        static inline std::string message_{ "trying to access child " };
    };

    struct append_attribute_error : public std::runtime_error {
        append_attribute_error(const std::string& name) : std::runtime_error{ message_ + name } {}
    private:
        static inline std::string message_{ "trying to append attribute " };
    };

    struct append_child_error : public std::runtime_error {
        append_child_error(const std::string& name) : std::runtime_error{ message_ + name } {}
    private:
        static inline std::string message_{ "trying to append child " };
    };

    struct load_from_error : public std::runtime_error {
        load_from_error(const std::string& description, std::ptrdiff_t offset) : std::runtime_error{ "" } {
            message_ = fmt::format("trying to load from: \"{}\", at offset {}", description, offset);
        }
        virtual const char* what() const noexcept override { return message_.c_str(); }
    private:
        static inline std::string message_{};
    };

    struct save_to_error : public std::runtime_error {
        save_to_error(const std::string& file_path) : std::runtime_error{ "" } {
            message_ = fmt::format("trying to save to: \"{}\"", file_path);
        }
        virtual const char* what() const noexcept override { return message_.c_str(); }
    private:
        static inline std::string message_{};
    };


    // pugixml function wrappers
    inline auto attribute_or_throw(const pugi::xml_node& node, const char* name) {
        if (auto ret{ node.attribute(name) }) {
            return ret;
        } else {
            throw attribute_error{ name };
        }
    }

    inline auto child_or_throw(const pugi::xml_node& node, const char* name) {
        if (auto ret{ node.child(name) }) {
            return ret;
        } else {
            throw child_error{ name };
        }
    }

    inline auto append_attribute_or_throw(pugi::xml_node& node, const char* name) {
        auto ret{ node.append_attribute(name) };
        if (ret) {
            return ret;
        } else {
            throw append_attribute_error{ name };
        }
    }

    inline auto append_child_or_throw(pugi::xml_node& root, const char* name) {
        auto ret{ root.append_child(name) };
        if (ret) {
            return ret;
        } else {
            throw append_child_error{ name };
        }
    }

    inline void load_xml_document_from_file_or_throw(pugi::xml_document& doc, const char* path) {
        auto result{ doc.load_file(path) };
        if (not result) {
            throw load_from_error{ result.description(), result.offset };
        }
    }

    inline void save_xml_document_to_file_or_throw(pugi::xml_document& doc, const char* path) {
        auto result{ doc.save_file(path) };
        if (not result) {
            throw save_to_error{ path };
        }
    }
}  // namespace tmcppc::pugixml
