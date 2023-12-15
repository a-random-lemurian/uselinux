include_directories(include)
add_executable(ancientpkg dig.c
                          package.c
                          main.c
                          date.c
                          digcommon.c
                          jsondig.c
                          digstats.c
                          excavate.c
                          curse.c
                          curse_diseased.c
                          curse_ancient_egypt.c
                          curse_infohazard.c
                          infohazard_amnestic.c
                          infohazard_berryman_langford.c
                          ancientpkg_utils.c
                          status.c
                          "install.c")

target_link_libraries(ancientpkg argparse common parson)
