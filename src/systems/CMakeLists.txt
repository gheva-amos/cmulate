cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 23)

add_library(systems
    location_system.cpp
    physics_system.cpp
    )
target_compile_options(systems PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
