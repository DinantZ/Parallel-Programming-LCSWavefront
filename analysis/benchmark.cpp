#include "lcs.h"
#include "lcs_openmp.h"
#include "test_input.h"
#include <chrono>
#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

int main() {
    const int input_length = 2000;
    std::mt19937 generator(29);
    const std::string first = generate_random_string(input_length, generator);
    const std::string second = generate_random_string(input_length, generator);
    const std::vector<int> tile_sizes = {16, 32, 64, 128, 256};

    const auto sequential_start = std::chrono::steady_clock::now();
    const LcsResult sequential_result = lcs_sequential(first, second);
    const auto sequential_end = std::chrono::steady_clock::now();
    const double sequential_time = std::chrono::duration<double>(
        sequential_end - sequential_start
    ).count();

    std::cout << "Input length: " << input_length << '\n'
              << "OpenMP threads: " << omp_get_max_threads() << '\n'
              << "Sequential time: " << sequential_time << " s\n"
              << "Sequential LCS length: " << sequential_result.length << "\n\n";

    for (int tile_size : tile_sizes) {
        const double start = omp_get_wtime();
        const LcsResult result = lcs_openmp(first, second, tile_size);
        const double seconds = omp_get_wtime() - start;

        std::cout << "Tile size: " << tile_size
                  << " | Time: " << seconds << " s"
                  << " | LCS length: " << result.length << '\n';
    }
}
