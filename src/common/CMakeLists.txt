add_library(common log.c mtwister.c utils.c)
target_link_libraries(common PRIVATE m)