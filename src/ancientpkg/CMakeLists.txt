include_directories(include)
add_executable(ancientpkg dig.c
                          package.c
                          main.c
                          date.c
                          digcommon.c
                          jsondig.c
                          digstats.c
                          excavate.c
                          infohazard.c
                          cursedpkg.c
                          ae-curse.c
                          ancientpkg_utils.c
                          status.c
                          "install.c")

target_link_libraries(ancientpkg argparse common parson)
