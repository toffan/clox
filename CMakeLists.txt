cmake_minimum_required(VERSION 3.24)
project(clox VERSION 0.0.1 LANGUAGES C)


add_executable(clox src/main.c)
target_include_directories(clox PUBLIC include)
target_compile_options(clox PUBLIC
  -Wall -Wextra -pedantic)
set_target_properties(clox PROPERTIES C_STANDARD 17)

add_subdirectory(src)
