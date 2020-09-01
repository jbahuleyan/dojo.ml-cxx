#ifndef ML_CXX_ML_COMMON_H
#define ML_CXX_ML_COMMON_H

#include <iostream>
#include <optional>
#include <random>
#include <string>

using std::cout, std::endl, std::optional, std::string;

extern std::mt19937_64 rng;
extern std::uniform_real_distribution<double> ud;

#endif //ML_CXX_ML_COMMON_H
