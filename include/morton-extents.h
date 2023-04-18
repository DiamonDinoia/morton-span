//
// Created by mbarbone on 4/18/23.
//

#ifndef MORTON_SPAN_MORTON_EXTENTS_H
#define MORTON_SPAN_MORTON_EXTENTS_H

#ifndef MORTON_HAS_MDSPAN
#error "MORTON_HAS_MDSPAN must be defined"
#elif (~MORTON_HAS_MDSPAN + 1) == 1
#include <mdspan>
#else
#include <experimental/mdspan>
#endif

#include <libmorton/morton.h>

struct MortonExtents {
    template <class Extents>
    struct mapping {
        using extents_type = Extents;
        using size_type    = unsigned long int;

        constexpr mapping(const extents_type& extents) noexcept : m_extents(extents) {
            static_assert(extents_type::rank() == 2 || extents_type::rank() == 3,
                          "Morton mapping requires 2D or 3D extents");
        }
        constexpr mapping(const mapping&) noexcept                       = default;
        constexpr mapping(mapping&&) noexcept                            = default;
        constexpr mapping&            operator=(const mapping&) noexcept = default;
        constexpr mapping&            operator=(mapping&&) noexcept      = default;
        constexpr const extents_type& extents() const noexcept { return m_extents; }
        //
        template <std::size_t RANK = Extents::rank(), typename std::enable_if<RANK == 2>::type* = nullptr>
        inline constexpr size_type operator()(size_type i, size_type j) const noexcept {
            return libmorton::morton2D_64_encode(i, j);
        }
        //
        template <std::size_t RANK = Extents::rank(), typename std::enable_if<RANK == 3>::type* = nullptr>
        inline constexpr size_type operator()(size_type i, size_type j, size_type k) const noexcept {
            return libmorton::morton3D_64_encode(i, j, k);
        }
        //
        static constexpr bool is_always_unique() noexcept { return true; }
        static constexpr bool is_always_exhaustive() noexcept { return true; }
        static constexpr bool is_always_strided() noexcept { return false; }
        //
        constexpr bool is_unique() const noexcept { return true; }
        constexpr bool is_exhaustive() const noexcept { return true; }
        constexpr bool is_strided() const noexcept { return false; }

       private:
        extents_type m_extents;
    };
};

#endif  // MORTON_SPAN_MORTON_EXTENTS_H
