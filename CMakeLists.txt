cmake_minimum_required(VERSION 4.0.0)
set (CMAKE_CXX_STANDARD 23)

project(yubi)

add_executable(yubi)
target_sources(yubi
    PRIVATE
    src/main.cpp
)
