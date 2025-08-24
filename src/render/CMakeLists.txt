cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 23)

add_library(render
    render.cpp
    sdl.cpp
    )
target_compile_options(render PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
target_link_libraries(render PUBLIC SDL2::SDL2)
