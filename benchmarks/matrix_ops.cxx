#include <armadillo>
#include <clblast.h>
#include <CL/cl2.hpp>

#include <chrono>
#include <vector>

#include "ml_common.h"

using std::vector;

namespace chrono = std::chrono;

const size_t Z = 1000000;
const size_t N = 100;

int benchmark_matrix_cpu() {
	arma::rowvec a_a(Z);
	arma::colvec a_b(Z);
	double c = ud(rng);

	a_a.randu();
	a_b.randu();

	optional<double> dp;
	uint64_t deltas(0);
	for (auto i = 0;i < N;i++) {
		auto t0 = chrono::system_clock::now();
		auto v = arma::as_scalar(a_a * a_b) + c;

		auto t1 = chrono::system_clock::now();
		if (!dp.has_value()) {
			dp = v;
		} else if (dp.value() != v) {
			cout << "Dot products do not match " << v << "!=" << dp.value() << endl;
			break;
		}
		auto delta = chrono::duration_cast<chrono::microseconds >(t1 - t0);
		deltas += delta.count();
	}

	cout << "C=" << c << ", Z=" << dp.value() << endl;
	cout << "Avg dt = " << (1.0*deltas)/N/1000 << " ms. Total time = " << deltas/1000.0 << "ms" << endl;

	return 0;
}

int benchmark_matrix_gpu() {
	vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	cl::Platform plat;
	for (auto &p : platforms) {
		string platver = p.getInfo<CL_PLATFORM_VERSION>();
		if (platver.find("OpenCL 2.") != std::string::npos) {
			plat = p;
		}
		cout << p.getInfo<CL_PLATFORM_NAME>() << endl;
	}

	double c = ud(rng);

	cl_int clErr;
	auto defaultCtx = cl::Context::getDefault(&clErr);
	auto defaultCQ = cl::CommandQueue::getDefault(&clErr);
	cout << "Device: " << defaultCtx.getInfo<CL_CONTEXT_DEVICES>()[0].getInfo<CL_DEVICE_NAME>() << endl;

	arma::rowvec a_a(Z);
	arma::colvec a_b(Z);
	a_a.randu();
	a_b.randu();

	cl::Buffer x_buff(defaultCtx, a_a.begin(), a_a.end(), true, false);
	cl::Buffer y_buff(defaultCtx, a_b.begin(), a_b.end(), true,false);
	cl::Buffer d_buff(defaultCtx, CL_MEM_READ_WRITE, sizeof(double));

#if 0
	cout << "A=" << a_a << endl;
	cout << "B=" << a_b << endl;

	double a_buff[4], b_buff[4];
	cl::enqueueReadBuffer(x_buff, true, 0, sizeof(a_buff), a_buff);
	cl::enqueueReadBuffer(y_buff, true, 0, sizeof(b_buff), b_buff);
	cout << "A[GPU.0/" << x_buff.getInfo<CL_MEM_SIZE>()/sizeof(double) << "]=" << a_buff[0] << endl;
	cout << "B[GPU.0/" << y_buff.getInfo<CL_MEM_SIZE>()/sizeof(double) << "]=" << b_buff[0] << endl;
#endif

	cout << "CPU dot=" << arma::as_scalar(a_a * a_b) + c << endl;

	optional<double> dp;
	uint64_t deltas(0);
	for(int i = 0;i < N;++i) {
		auto t0 = chrono::system_clock::now();
		auto clOpStatus = clblast::Dot<double>(Z, d_buff(), 0, x_buff(), 0, 1, y_buff(), 0, 1, &defaultCQ());
		double result(0.0);
		auto t1 = chrono::system_clock::now();
		cl::enqueueReadBuffer(d_buff, true, 0, sizeof(result), &result);
		result += c;

		if (clOpStatus != clblast::StatusCode::kSuccess) {
			cout << (int) clOpStatus << endl;
			break;
		} else if (!dp.has_value()) {
			dp = result;
		} else if (dp.value() != result) {
			cout << "Dot products do not match " << result << "!=" << dp.value() << endl;
			break;
		}

		auto delta = chrono::duration_cast<chrono::microseconds >(t1 - t0);
		deltas += delta.count();
	}

	cout << "C=" << c << ", Z=" << dp.value() << endl;
	cout << "Avg dt = " << (1.0*deltas)/N/1000 << " ms. Total time = " << deltas/1000.0 << "ms" << endl;

	return 0;
}
