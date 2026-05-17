cmake_minimum_required(VERSION 4.0.0)
set (CMAKE_CXX_STANDARD 23)

project(yubi)
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

add_executable(yubi)

target_sources(yubi
    PRIVATE
    src/main.cpp

    src/engine/threads/audio.h
    src/engine/threads/audio.cpp

    src/engine/os/filesystem.h
    src/engine/os/hints.h
    src/engine/os/filesystem.cpp
    src/engine/os/hints.cpp
)

target_link_libraries(yubi
    PRIVATE
    SDL3::SDL3
)
