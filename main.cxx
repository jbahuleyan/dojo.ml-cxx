extern int benchmark_matrix_cpu();
extern int benchmark_matrix_gpu();

#include <ml_common.h>

#include <CL/cl2.hpp>


int main() {
	benchmark_matrix_cpu();
	benchmark_matrix_gpu();

	return 0;
}
