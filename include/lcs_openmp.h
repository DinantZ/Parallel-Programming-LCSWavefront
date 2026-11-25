#pragma once

#include "lcs.h"
#include <string>

LcsResult lcs_openmp(const std::string& first, const std::string& second, int tile_size);
