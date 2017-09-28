#pragma once
#include <iostream>

namespace AuxLib {

	inline float RandomBinomial() { return ((float)rand() / (RAND_MAX)) - ((float)rand() / (RAND_MAX)); }
}
