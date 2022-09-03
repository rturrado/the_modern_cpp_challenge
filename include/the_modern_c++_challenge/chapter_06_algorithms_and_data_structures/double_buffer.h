#pragma once

#include <algorithm>  // copy, swap
#include <mutex>  // scoped_lock
#include <vector>


namespace tmcppc::data_structures {
    template <typename T>
    class double_buffer {
    public:
        using container = std::vector<T>;
        using container_type = container;
        using const_reference = container::const_reference;
        using reference = container::reference;
        using size_type = container::size_type;
        using value_type = container::value_type;

        explicit double_buffer(size_type size)
            : buffer_write_(size), buffer_read_(size) {}

        [[nodiscard]] constexpr size_type size() const noexcept { return buffer_read_.size(); }

        constexpr void write(size_type pos, const T& t) {
            buffer_write_.at(pos) = t;
            swap_buffers();
        }
        constexpr void write(size_type pos, const container& v) {
            if (pos + v.size() > buffer_write_.size()) {
                throw std::out_of_range{ "trying to write beyond the end of the double buffer" };
            }
            std::ranges::copy(v, begin(buffer_write_) + pos);
            swap_buffers();
        }
        [[nodiscard]] constexpr T read(size_type pos) const {
            std::scoped_lock sl{ buffers_mutex };
            return buffer_read_.at(pos);
        }
        [[nodiscard]] constexpr container read(size_type pos, size_type size) const {
            if (pos + size > buffer_read_.size()) {
                throw std::out_of_range{ "trying to read beyond the end of the double buffer" };
            }
            std::scoped_lock sl{ buffers_mutex };
            container ret(size);
            std::copy(cbegin(buffer_read_) + pos, cbegin(buffer_read_) + pos + size, begin(ret));
            return ret;
        }

    private:
        constexpr void swap_buffers() noexcept {
            std::scoped_lock sl{ buffers_mutex };
            std::swap(buffer_write_, buffer_read_);
        }

        container buffer_write_{};
        container buffer_read_{};
        mutable std::mutex buffers_mutex{};
    };
}  // namespace tmcppc::data_structures
