#-----------------------------------------------------------------------
# - Top Level CMakeLists.txt for AltMin Build
#-----------------------------------------------------------------------
# - Enforce an out-of-source builds before anything else
#
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(STATUS "morton-span requires an out-of-source build.")
    message(STATUS "Please remove these files from ${CMAKE_CURRENT_BINARY_DIR} first:")
    message(STATUS "CMakeCache.txt")
    message(STATUS "CMakeFiles")
    message(STATUS "Once these files are removed, create a separate directory")
    message(STATUS "and run CMake from there")
    message(FATAL_ERROR "in-source build detected")
endif ()

cmake_minimum_required(VERSION 3.14)

project(morton-span
        VERSION 0.1
        LANGUAGES CXX)

# add cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# version of the libraries to be used
set(CPM_DOWNLOAD_VERSION 0.38.1)
set(MDSPAN_DOWNLOAD_VERSION 0.6.0)
set(LIBMORTON_DOWNLOAD_VERSION 0.2.11)
include(CPMconfig)

# Create an interface library for morton-span
add_library(morton-span INTERFACE)
target_include_directories(morton-span INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

# check if c++23 is supported
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++23" MORTON_HAS_CXX23)
if (NOT MORTON_HAS_CXX23)
    target_compile_features(morton-span INTERFACE cxx_std_17)
endif ()

# if c++23 is supported then check if mdspan is supported
if (MORTON_HAS_CXX23)
    message(STATUS "C++23 is supported")
    include(CheckIncludeFileCXX)
    CHECK_INCLUDE_FILE_CXX(mdspan MORTON_HAS_MDSPAN -std=c++23)
endif ()
target_compile_definitions(morton-span INTERFACE MORTON_HAS_MDSPAN=${MORTON_HAS_MDSPAN})

# if mdspan is not supported download it
if (NOT MORTON_HAS_MDSPAN)
    message(STATUS "mdspan is not supported, downloading it")
    CPMAddPackage(
            NAME mdspan
            GITHUB_REPOSITORY kokkos/mdspan
            GIT_TAG mdspan-${MDSPAN_DOWNLOAD_VERSION}
            VERSION ${MDSPAN_DOWNLOAD_VERSION}
            OPTIONS
            "MDSPAN_ENABLE_EXAMPLES Off"
            "MDSPAN_ENABLE_TESTS Off"
            "MDSPAN_ENABLE_BENCHMARKS Off"
    )
    target_link_libraries(morton-span INTERFACE mdspan)
else ()
    target_compile_features(morton-span INTERFACE cxx_std_23)
endif ()

CPMAddPackage(
        NAME libmorton
        GITHUB_REPOSITORY Forceflow/libmorton
        GIT_TAG v${LIBMORTON_DOWNLOAD_VERSION}
        VERSION ${LIBMORTON_DOWNLOAD_VERSION}
        OPTIONS
        "BUILD_TESTING Off"
)
target_link_libraries(morton-span INTERFACE libmorton)
# option to build tests
option(MORTON_BUILD_TESTS "Build tests" ON)


# if tests include subdirectory
if (MORTON_BUILD_TESTS)
    add_subdirectory(test)
endif ()