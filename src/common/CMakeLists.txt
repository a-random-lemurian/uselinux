add_library(common log.c mtwister.c utils.c)
add_library(argparse argparse.c)
add_library(opener opener.c detect_os.c)
target_link_libraries(common PRIVATE m)