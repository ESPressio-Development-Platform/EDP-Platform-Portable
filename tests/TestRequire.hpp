#pragma once

#include <cstdio>
#include <cstdlib>

// Deliberately survives NDEBUG: provider test calls must execute in both
// Debug and Release builds, with every failure reported and fail-closed.
#define EDP_PORTABLE_TEST_REQUIRE(expression) \
    do { \
        if (!(expression)) { \
            std::fprintf( \
                stderr, \
                "EDP-Platform-Portable test failed at %s:%d: %s\\n", \
                __FILE__, \
                __LINE__, \
                #expression \
            ); \
            std::abort(); \
        } \
    } while (false)
