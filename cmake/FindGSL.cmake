message("GSL configure")

find_path(GSL_INCLUDE_DIR gsl_version.h PATH_SUFFIXES include/gsl PATHS /usr)
find_library(GSL_LIBS gsl PATH_SUFFIXES lib64 lib PATHS /usr)
