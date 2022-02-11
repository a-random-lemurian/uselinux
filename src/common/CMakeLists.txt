add_library(common argparse.c log.c mtwister.c utils.c)
add_library(csvreader csv.c fread_csv_line.c split.c)
add_library(opener opener.c detect_os.c)
target_link_libraries(common PRIVATE m)