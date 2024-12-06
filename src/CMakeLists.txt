cmake_minimum_required(VERSION 3.10)

project(VectorProject LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(vectorlib) 

add_subdirectory(tests)

enable_testing()

add_test (NAME vectorTest COMMAND vectorTest)
add_test (NAME vectorTest2 COMMAND vectorTest2)