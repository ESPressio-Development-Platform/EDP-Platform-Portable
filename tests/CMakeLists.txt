cmake_minimum_required(VERSION 3.16)

project(EDPPlatformPortableTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Normalize caller-supplied sibling paths relative to the repository root.
if(DEFINED EDP_PLATFORM_SOURCE_DIR)
    get_filename_component(
        EDP_PLATFORM_SOURCE_DIR
        "${EDP_PLATFORM_SOURCE_DIR}"
        ABSOLUTE
        BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
endif()

if(DEFINED EDP_SYSTEM_SOURCE_DIR)
    get_filename_component(
        EDP_SYSTEM_SOURCE_DIR
        "${EDP_SYSTEM_SOURCE_DIR}"
        ABSOLUTE
        BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
endif()

if(DEFINED EDP_MEMORY_SOURCE_DIR)
    get_filename_component(
        EDP_MEMORY_SOURCE_DIR
        "${EDP_MEMORY_SOURCE_DIR}"
        ABSOLUTE
        BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
endif()

if(NOT DEFINED EDP_PLATFORM_SOURCE_DIR)
    message(FATAL_ERROR "EDP_PLATFORM_SOURCE_DIR must point at an EDP-Platform checkout")
endif()

if(NOT DEFINED EDP_SYSTEM_SOURCE_DIR)
    message(FATAL_ERROR "EDP_SYSTEM_SOURCE_DIR must point at an EDP-System checkout")
endif()

if(NOT DEFINED EDP_MEMORY_SOURCE_DIR)
    message(FATAL_ERROR "EDP_MEMORY_SOURCE_DIR must point at an EDP-Memory checkout")
endif()

if(NOT EXISTS "${EDP_PLATFORM_SOURCE_DIR}/src/ESPressio_Platform.hpp")
    message(FATAL_ERROR "EDP_PLATFORM_SOURCE_DIR does not contain src/ESPressio_Platform.hpp")
endif()

if(NOT EXISTS "${EDP_SYSTEM_SOURCE_DIR}/src/ESPressio_System.hpp")
    message(FATAL_ERROR "EDP_SYSTEM_SOURCE_DIR does not contain src/ESPressio_System.hpp")
endif()

if(NOT EXISTS "${EDP_MEMORY_SOURCE_DIR}/src/ESPressio_Memory.hpp")
    message(FATAL_ERROR "EDP_MEMORY_SOURCE_DIR does not contain src/ESPressio_Memory.hpp")
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
