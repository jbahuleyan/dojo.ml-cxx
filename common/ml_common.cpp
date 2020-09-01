#include "ml_common.h"

namespace {
	std::random_device rng_dev;
}

std::mt19937_64 rng(rng_dev());
std::uniform_real_distribution<double> ud;
