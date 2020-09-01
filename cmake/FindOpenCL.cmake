message("OpenCL configure")

find_library(OPENCL_LIBS OpenCL PATH_SUFFIXES lib64 lib PATHS /usr)
find_path(OPENCL_INCLUDE_DIR CL/cl2.hpp PATH_SUFFIXES include PATHS /usr)
