message("Armadillo configure")

set(Armadillo_PATHS $ENV{HOME}/Apps/armadillo)

find_path(Armadillo_INCLUDE_DIR armadillo PATH_SUFFIXES include PATHS ${Armadillo_PATHS} NO_DEFAULT_PATH)
find_library(Armadillo_LIBS armadillo PATH_SUFFIXES lib64 lib PATHS ${Armadillo_PATHS} NO_DEFAULT_PATH)
