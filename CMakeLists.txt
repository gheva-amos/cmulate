cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME CMulation)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

#yum install -y cmake gdb python3-devel mesa-libGL-devel mesa-libGLU-devel libudev-devel libXrandr-devel libX11-devel libXcursor-devel freetype-devel

include_directories(include)

include(FetchContent)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
      SFML
      GIT_REPOSITORY https://github.com/SFML/SFML.git
      GIT_TAG 2.6.1
    )
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/master.zip
    )

FetchContent_MakeAvailable(googletest)

set(SDL_X11 ON  CACHE BOOL "" FORCE)
set(SDL_WAYLAND OFF CACHE BOOL "" FORCE)
set(SDL_OPENGL   OFF CACHE BOOL "" FORCE)
set(SDL_OPENGLES OFF CACHE BOOL "" FORCE)
set(SDL_ALSA ON CACHE BOOL "" FORCE)
set(SDL_PULSEAUDIO OFF CACHE BOOL "" FORCE)
set(SDL_PIPEWIRE OFF CACHE BOOL "" FORCE)
set(HAVE_RPI OFF CACHE BOOL "" FORCE)
set(SDL_RPI  OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.3
    )
FetchContent_MakeAvailable(SDL2)

add_subdirectory(src)
add_subdirectory(experiments)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()
set(PROJECT_TEST_NAME test_${PROJECT_NAME})

file(GLOB_RECURSE TEST_SRC_FILES "${PROJECT_SOURCE_DIR}/tests/*.cpp")
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
#target_include_directories(${PROJECT_TEST_NAME} PRIVATE ${boost_SOURCE_DIR}/libs/math/include)
target_compile_options(${PROJECT_TEST_NAME} PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
target_link_libraries(${PROJECT_TEST_NAME} GTest::gtest_main cmulate)
include(GoogleTest)
gtest_discover_tests(${PROJECT_TEST_NAME})
