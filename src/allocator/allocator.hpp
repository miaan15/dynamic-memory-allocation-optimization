#ifndef DMAO_ALLOCATOR_HPP
#define DMAO_ALLOCATOR_HPP

#include <algorithm>
#include <cstddef>
#include <memory>
#include <new>
#include <optional>
#include <type_traits>
#include <vector>

#include "allocator/allocator-params.hpp"

namespace dmao {

template <typename T>
class allocator {
public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = std::ptrdiff_t;

    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_copy_assignment = std::true_type;
    using is_always_equal                        = std::false_type;

    template <typename U>
    struct rebind {
        using other = allocator<U>;
    };

public:
    explicit allocator(allocator_strategy strat = {})
      : pool(std::make_shared<pool_type>()), strategy(strat) {}

    allocator(const allocator &)     = default;
    allocator(allocator &&) noexcept = default;

    auto operator=(const allocator &) -> allocator &     = default;
    auto operator=(allocator &&) noexcept -> allocator & = default;

    template <class U>
    allocator(const allocator<U> &other)
      : pool(other.pool), strategy(other.strategy) {}

    template <class U>
    allocator(allocator<U> &&other) noexcept
      : pool(std::move(other.pool)), strategy(std::move(other.strategy)) {}

public:
    [[nodiscard]] auto allocate(size_t n) -> value_type * {
        const size_t bytes = n * sizeof(value_type);
        const size_t align = alignof(value_type);

        if (pool->empty()) {
            pool->emplace_back(block{std::vector(DEFAULT_BLOCK_SIZE, std::byte{0})});
        }

        if (auto p = try_from_block(pool->back(), bytes, align)) {
            return static_cast<value_type *>(*p);
        }

        const size_t block_bytes = std::max(DEFAULT_BLOCK_SIZE, padded_size(bytes, align));
        pool->emplace_back(block{std::vector(block_bytes, std::byte{0})});

        auto p = try_from_block(pool->back(), bytes, align);
        if (!p) throw std::bad_alloc();
        return static_cast<value_type *>(*p);
    }

    void deallocate(value_type * /*p*/, size_t /*n*/) noexcept {}

    template <typename U, typename... Args>
    void construct(U *p, Args &&...args) {
        ::new (static_cast<void *>(p)) U(std::forward<Args>(args)...);
    }
    template <typename U>
    void destroy(U *p) noexcept {
        p->~U();
    }

    friend auto operator==(const allocator &a, const allocator &b) noexcept -> bool {
        return a.pool.get() == b.pool.get();
    }
    friend auto operator!=(const allocator &a, const allocator &b) noexcept -> bool {
        return !(a == b);
    }

private:
    static constexpr size_t DEFAULT_BLOCK_SIZE = 1024;

    struct block {
        std::vector<std::byte> data;
        size_t                 offset{0};
    };
    using pool_type = std::vector<block>;

    std::shared_ptr<std::vector<block>> pool;
    allocator_strategy                  strategy;

    static auto padded_size(size_t bytes, size_t alignment) -> size_t {
        return bytes + (alignment - 1U);
    }

    static auto try_from_block(block &b, size_t bytes, size_t alignment) -> std::optional<void *> {
        std::byte *base  = b.data.data();
        size_t     space = b.data.size() - b.offset;
        void      *p     = base + b.offset;
        if (std::align(alignment, bytes, p, space) != nullptr) {
            auto *aligned = static_cast<std::byte *>(p);
            b.offset      = static_cast<size_t>(aligned - base) + bytes;
            return aligned;
        }
        return std::nullopt;
    }

    template <typename>
    friend class allocator;
};

} // namespace dmao

#endif // DMAO_ALLOCATOR_HPP
