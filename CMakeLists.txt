cmake_minimum_required(VERSION 3.18)
project(uselinux)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-O3 -Werror -flto -funroll-loops)

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
