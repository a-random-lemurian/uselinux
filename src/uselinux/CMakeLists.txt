add_executable(uselinux userspace.h uselinuxcommon.c main.c deskenv.c ancientpkg.c yearoflinuxdesktop.c)
target_link_libraries(uselinux PUBLIC common)