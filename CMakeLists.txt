cmake_minimum_required(VERSION 3.25)
project(dining_philosophers C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(src)

add_executable(dining_philosophers main.c src/philosopher.h src/chopstick.h src/chopstick.c)
