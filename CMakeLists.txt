cmake_minimum_required(VERSION 3.8)

project("bitArray")

# Добавьте источник в исполняемый файл этого проекта.
add_executable(bitArray "scr/main.cpp" "scr/BitArray.cpp" "include/BitArray.h")

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_subdirectory("tests")
