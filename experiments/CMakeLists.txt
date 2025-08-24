cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 23)

add_executable(sdl001 sdl001.cpp)
target_compile_options(sdl001 PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
set_target_properties(sdl001 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")
target_link_libraries(sdl001 PRIVATE
#SDL2::SDL2main
    dbg
    SDL2::SDL2)
