message("CLBlast configure")

set(CLBLAST_PATHS "/home/jb/Apps/CLBlast/")

find_library(CLBLAST_LIBS clblast PATH_SUFFIXES lib64 lib PATHS ${CLBLAST_PATHS})
find_path(CLBLAST_INCLUDE_DIR clblast.h PATH_SUFFIXES include PATHS ${CLBLAST_PATHS})
