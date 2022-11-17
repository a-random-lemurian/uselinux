add_executable(uselinux uselinuxcommon.c userspace.c main.c
               deskenv.c yearoflinuxdesktop.c)
add_executable(antisnap antisnap.c uselinuxcommon.c)
target_link_libraries(antisnap PUBLIC common argparse)
target_link_libraries(uselinux PUBLIC common argparse)