cmake_minimum_required(VERSION 3.18)
project(uselinux)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

option(FSF_TERMINOLOGY "Use FSF terminology (e.g GNU/Linux and not Linux)")

if(FSF_TERMINOLOGY)
     add_compile_definitions(FSF_TERMINOLOGY)
endif()

if(DEBUG)
    add_compile_options(-g3)
endif()

add_compile_options(-O3 -flto -funroll-loops)

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
