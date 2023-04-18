# morton-span

This repository implements a morton transform for mdspan

## Motivation

In Monte Carlo simulations is oftem nore efficent a morton transform of the particle positions to a morton index. This
is because the morton index is a contiguous index and thus can be used to access the particles in a cache friendly way.

## Usage
It is reccomended to use cpm to include this library in your project. To do so add the following to your CMakeLists.txt

```cmake
CPMAddPackage(
  NAME morton-span
  GITHUB_REPOSITORY diamondinoia/morton-span
  GIT_TAG main
)
```

Then in your code you can use the morton transform as follows for 2d and 3d.
c++23 example:
```cpp
#include <morton_span.h>
    // 2D CASE
    std::mdspan<int, std::dextents<int, 2>
           morton::MortonExtents> morton_span_2d;
    // 3D CASE
    std::mdspan<int, std::dextents<int, 3>,
              morton::MortonExtents> morton_span_3d;
```
c++ < 23 example:
```cpp
#include <morton_span.h>
    // 2D CASE
    std::experimental::mdspan<int, std::experimental::extents<std::size_t, std::experimental::dynamic_extent,
        std::experimental::dynamic_extent>, morton::MortonExtents> morton_span_2d;
    // 3D CASE
    std::experimental::mdspan<int, std::experimental::extents<std::size_t, std::experimental::dynamic_extent,
        std::experimental::dynamic_extent, std::experimental::dynamic_extent>, morton::MortonExtents> morton_span_3d;
```

## limitations
- The morton transform is only implemented for 2d and 3d
- The morton transform is only implemented for geometries of euqal side lengths (i.e. a cube or a square)
- The morton transform is only implemented for dimensions that are a power of 2

## Acknowledgements
- [mdspan](https://github.com/kokkos/mdspan)  
- [libmorton](https://github.com/Forceflow/libmorton)
