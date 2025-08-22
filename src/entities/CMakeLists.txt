cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 23)

add_library(entities
    entity_manager.cpp
    )
target_compile_options(entities PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
