cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 23)

add_library(event
    event.cpp
    functor.cpp
    trigger.cpp
    entity_event.cpp
    event_vector.cpp
    )
target_compile_options(event PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
