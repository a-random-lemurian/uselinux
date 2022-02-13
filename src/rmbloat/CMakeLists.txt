add_executable(rmbloat rmbloat-from-file.c rmbloat-rm.c rmbloat.c rmbloatapi.c)
target_link_libraries(rmbloat common argparse)