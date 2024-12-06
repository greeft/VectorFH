cmake_minimum_required(VERSION 3.10)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(vectorTest vectorTest.cpp)
target_link_libraries(vectorTest
    PUBLIC vectorlib
    PUBLIC gtest_main
)
gtest_discover_tests(vectorTest)

add_executable(vectorTest2 vectorTest2.cpp)
target_link_libraries(vectorTest2
    PUBLIC vectorlib
    PUBLIC gtest_main
)
gtest_discover_tests(vectorTest2)
