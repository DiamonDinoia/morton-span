//
// Created by mbarbone on 4/18/23.
//

#define CATCH_CONFIG_MAIN
#include <morton-extents.h>

#include <catch2/catch.hpp>

#ifndef MORTON_HAS_MDSPAN
#error "MORTON_HAS_MDSPAN must be defined"
#elif (~MORTON_HAS_MDSPAN + 1) == 1
#else
using namespace std::experimental;
#endif
using namespace std;

TEST_CASE("2D case") {
    const auto  x = 64, y = 64, size = x * y;
    vector<int> v(size);
    mdspan<int, extents<std::size_t, dynamic_extent, dynamic_extent>,
           morton::MortonExtents>
        test_m(v.data(), x, y);
    for (auto i = 0; i < x; ++i) {
        for (auto j = 0; j < y; ++j) { test_m(i, j)++; }
    }
    for (const auto& e : v) { REQUIRE(e == 1); }
}

TEST_CASE("3D case") {
    const auto  x = 64, y = 64, z = 64, size = x * y * z;
    vector<int> v(size);
    mdspan<int,
           extents<std::size_t, dynamic_extent, dynamic_extent, dynamic_extent>,
           morton::MortonExtents>
        test_m(v.data(), x, y, z);
    for (auto i = 0; i < x; ++i) {
        for (auto j = 0; j < y; ++j) {
            for (auto k = 0; k < z; ++k) { test_m(i, j, k)++; }
        }
    }
    for (const auto& e : v) { REQUIRE(e == 1); }
}