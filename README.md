# Playground for testing ML algorithms in C++

## Pre-requisites

- C++ compiler (gcc, LLVM)
- cmake
- make

## Build

Comment out the libraries that are not available or needed from CMakeLists.txt (these are the `find_package()` lines). 
Some of the cmake module configurations (`Find*.cmake` under `cmake/`) assume the packages are built and installed in the
home directory. Modify these as appropriate (e.g. if installed via the package manager PATHS would be `/usr`).

- [Armadillo](http://arma.sourceforge.net/) for linear algebra. 
- (Optional) install a BLAS implementation. Multi-threaded openblas is a good candidate.

OpenCL installation for using GPU involves the following steps.

- install the OpenCL library and C++ development headers.
- install an OpenCL implementation appropriate to the GPU. e.g. amdgpu-pro for Radeon cards.
- install [clblast](https://github.com/CNugteren/CLBlast/) or use the OpenCL APIs directly. Optionally run the clblast tuners
if their database doesn't contain your GPU.
