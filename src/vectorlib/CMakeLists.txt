cmake_minimum_required(VERSION 3.10)
project(vectorlib LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(vectorlib STATIC vector.c)
target_include_directories(vectorlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

