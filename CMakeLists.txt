cmake_minimum_required(VERSION 3.18)
project(uselinux)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(modules)
include_directories(src)
add_subdirectory(modules)
add_subdirectory(src)
install(
    TARGETS
        penguinspammer
        rmbloat
        stackov
        uselinux
    DESTINATION
        bin)
