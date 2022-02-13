add_executable(rmbloat rmbloat-csv.c rmbloat-rm.c rmbloat.c rmbloatapi.c)
target_link_libraries(rmbloat common csvreader argparse)