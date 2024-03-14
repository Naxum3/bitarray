cmake_minimum_required(VERSION 3.8)

project("tests")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (tests "Tests.cpp" "../include/BitArray.h" "../scr/BitArray.cpp")

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(tests PUBLIC GTest::gtest_main)

include(GoogleTest)
add_test(TARGET tests)
gtest_discover_tests(tests)