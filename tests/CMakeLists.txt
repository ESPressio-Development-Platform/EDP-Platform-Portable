cmake_minimum_required(VERSION 3.16)

project(EDPPlatformPortableTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED EDP_PLATFORM_SOURCE_DIR)
    message(FATAL_ERROR "EDP_PLATFORM_SOURCE_DIR must point at an EDP-Platform checkout")
endif()

if(NOT DEFINED EDP_SYSTEM_SOURCE_DIR)
    message(FATAL_ERROR "EDP_SYSTEM_SOURCE_DIR must point at an EDP-System checkout")
endif()

find_package(Threads REQUIRED)

add_executable(
    portable_provider_tests
    PortableProviderTests.cpp
)

target_include_directories(
    portable_provider_tests
    PRIVATE
        ../src
        ${EDP_PLATFORM_SOURCE_DIR}/src
        ${EDP_SYSTEM_SOURCE_DIR}/src
)

target_link_libraries(
    portable_provider_tests
    PRIVATE
        Threads::Threads
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
        portable_provider_tests
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Werror
    )
endif()
