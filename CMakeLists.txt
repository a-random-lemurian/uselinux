cmake_minimum_required(VERSION 3.18)
project(uselinux)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)