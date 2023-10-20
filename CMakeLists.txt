cmake_minimum_required(VERSION 3.1)
project(palladium LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(static_analyzers)

find_package(raylib CONFIG REQUIRED)
find_package(FMT CONFIG REQUIRED)

set(palladium_ExternalLibraries
    raylib
    fmt::fmt
)

add_subdirectory(palladium)
