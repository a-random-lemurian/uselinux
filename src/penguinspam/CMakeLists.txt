add_library(penguinspam penguinspam.c)
add_executable(penguinspammer penguinspamcli.c)

target_link_libraries(penguinspam PUBLIC common)
target_link_libraries(penguinspammer PUBLIC common)
target_link_libraries(penguinspammer PUBLIC penguinspam)
