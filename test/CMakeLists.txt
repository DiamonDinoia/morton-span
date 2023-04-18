# create a simple cmake lists for the tests
set(CATCH2_DOWNLOAD_VERSION v2.13.10)


CPMAddPackage(
        NAME Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG ${CATCH2_DOWNLOAD_VERSION}
        EXCLUDE_FROM_ALL YES
        GIT_SHALLOW YES
)

include(CTest)
enable_testing()

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2 morton-span)
# use cpm to download catch2

