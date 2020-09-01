message("BLAS configure")

find_library(BLAS_LIBS openblas PATH_SUFFIXES lib64 lib PATHS /usr)
#find_library(CBLAS_LIBS cblas PATH_SUFFIXES lib64 lib PATHS /usr)
#find_library(BLAS_LIBS blis-mt PATH_SUFFIXES lib64 lib PATHS $ENV{HOME}/Apps/aocl-linux-gcc/2.2-5/amd-blis)
