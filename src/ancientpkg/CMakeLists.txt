include_directories(include)
add_executable(ancientpkg dig.c
                          package.c
                          main.c
                          date.c
                          digcommon.c
                          jsondig.c
                          digstats.c
                          excavate.c
                          "install.c"
                          curse/cursedpkg.c
                          curse/infohazard.c
                          curse/ae-curse.c)

target_link_libraries(ancientpkg argparse common parson)
