cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(utils)
add_subdirectory(components)
add_library(cmulate
    entity_manager.cpp
    game_loop.cpp
    location_system.cpp
    grid.cpp
    tile.cpp
    world.cpp
    )
target_compile_options(cmulate PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
target_link_libraries(cmulate PUBLIC utils components)

add_executable(SFMLBuildTest sfml.cpp)
target_compile_options(SFMLBuildTest PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
set_target_properties(SFMLBuildTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")
target_link_libraries(SFMLBuildTest PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(c-mulate cmulate.cpp)
target_compile_options(c-mulate PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
set_target_properties(c-mulate PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")
target_link_libraries(c-mulate PRIVATE cmulate)
