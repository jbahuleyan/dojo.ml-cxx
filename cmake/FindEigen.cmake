set(EIGEN_PATHS $ENV{HOME}/Apps/eigen)

message("Eigen configure")

add_compile_definitions(EIGEN_USE_BLAS)
add_compile_definitions(EIGEN_USE_LAPACKE)
find_path(Eigen_INCLUDE_DIR signature_of_eigen3_matrix_library PATH_SUFFIXES include/eigen3 PATHS ${EIGEN_PATHS})
find_library(Eigen_LIBS lapacke3 blas PATH_SUFFIXES lib64 lib PATHS /usr)
