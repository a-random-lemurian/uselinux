add_executable(ancientpkg dig.c package.c main.c date.c digcommon.c jsondig.c
                          digstats.c excavate.c cursedpkg.c)
target_link_libraries(ancientpkg argparse common parson)
