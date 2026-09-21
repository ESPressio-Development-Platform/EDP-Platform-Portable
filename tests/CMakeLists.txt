cmake_minimum_required(VERSION 3.16)

project(EDPPlatformPortableTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED EDP_PLATFORM_SOURCE_DIR)
    message(FATAL_ERROR "EDP_PLATFORM_SOURCE_DIR must point at an EDP-Platform checkout")
endif()

if(NOT DEFINED EDP_SYSTEM_SOURCE_DIR)
    message(FATAL_ERROR "EDP_SYSTEM_SOURCE_DIR must point at an EDP-System checkout")
endif()

if(NOT DEFINED EDP_MEMORY_SOURCE_DIR)
    message(FATAL_ERROR "EDP_MEMORY_SOURCE_DIR must point at an EDP-Memory checkout")
endif()

find_package(Threads REQUIRED)

add_executable(portable_provider_tests PortableProviderTests.cpp)
add_executable(portable_memory_provider_tests PortableMemoryProviderTests.cpp)

foreach(target portable_provider_tests portable_memory_provider_tests)
    target_include_directories(
        ${target}
        PRIVATE
            ../src
            ${EDP_PLATFORM_SOURCE_DIR}/src
            ${EDP_SYSTEM_SOURCE_DIR}/src
            ${EDP_MEMORY_SOURCE_DIR}/src
    )

    target_link_libraries(${target} PRIVATE Threads::Threads)

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endforeach()
