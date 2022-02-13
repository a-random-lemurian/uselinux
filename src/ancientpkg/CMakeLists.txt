add_executable(ancientpkg dig.c main.c date.c digcommon.c jsondig.c)
target_link_libraries(ancientpkg argparse common parson)
