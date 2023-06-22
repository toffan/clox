cmake_minimum_required(VERSION 3.24)
project(clox VERSION 0.0.1 LANGUAGES C)

SET(CMAKE_EXPORT_COMPILE_COMMANDS true)


add_executable(clox src/main.c)
target_include_directories(clox PUBLIC include)
add_subdirectory(src)
