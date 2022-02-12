add_executable(ancientpkg dig.c main.c date.c)
target_link_libraries(ancientpkg argparse common parson)
