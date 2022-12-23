#pragma once

#include <filesystem>


namespace tmcppc {
    class env {
    public:
        [[nodiscard]] static env& get_instance() {
            static env instance;
            return instance;
        }
        [[nodiscard]] auto get_resource_folder_path() {
            return resource_folder_path_;
        }
        void set_resource_folder_path(const std::filesystem::path& p) {
            resource_folder_path_ = p;
        }
    private:
        env() = default;
        std::filesystem::path resource_folder_path_{};
    };
}  // namespace tmcppc
