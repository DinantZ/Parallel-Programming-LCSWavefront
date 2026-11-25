#include "lcs_openmp.h"
#include <iostream>
#include <omp.h>

int main() {
    const std::string first = "ABCBDAB";
    const std::string second = "BDCABA";
    const int tile_size = 64;

    const double start = omp_get_wtime();
    const LcsResult result = lcs_openmp(first, second, tile_size);

    std::cout << "LCS length: " << result.length << '\n'
              << "LCS: " << result.sequence << '\n'
              << "Time: " << omp_get_wtime() - start << " s\n";
}
