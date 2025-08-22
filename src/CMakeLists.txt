cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 23)

add_executable(SFMLBuildTest sfml.cpp)
target_compile_options(SFMLBuildTest PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
set_target_properties(SFMLBuildTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")
target_link_libraries(SFMLBuildTest PRIVATE sfml-graphics sfml-window sfml-system)

