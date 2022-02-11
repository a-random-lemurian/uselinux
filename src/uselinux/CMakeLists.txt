add_executable(uselinux userspace.h uselinuxcommon.c main.c deskenv.c ancientpkg.c yearoflinuxdesktop.c)
add_executable(antisnap antisnap.c uselinuxcommon.c)
target_link_libraries(antisnap PUBLIC common)
target_link_libraries(uselinux PUBLIC common)