add_library(common argparse.c log.c mtwister.c utils.c)
target_link_libraries(common PRIVATE m)