#include "lcs.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <omp.h>

LcsResult lcs_openmp(const std::string& x, const std::string& y, int tile_size) {
    const int m = static_cast<int>(x.size());
    const int n = static_cast<int>(y.size());
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    // Calculate how many tiles cover the table in each dimension.
    const int tile_rows = (m + tile_size - 1) / tile_size;
    const int tile_cols = (n + tile_size - 1) / tile_size;

    // Traverse the tile grid along anti-diagonals so dependencies are ready.
    for (int wave = 0; wave < tile_rows + tile_cols - 1; ++wave) {
        // Process the tiles on this anti-diagonal in parallel.
        #pragma omp parallel for schedule(static)
        for (int tile_i = 0; tile_i < tile_rows; ++tile_i) {
            const int tile_j = wave - tile_i;
            if (tile_j < 0 || tile_j >= tile_cols) {
                continue;
            }

            const int row_end = std::min(m, (tile_i + 1) * tile_size);
            const int col_end = std::min(n, (tile_j + 1) * tile_size);
            for (int i = tile_i * tile_size + 1; i <= row_end; ++i) {
                for (int j = tile_j * tile_size + 1; j <= col_end; ++j) {
                    if (x[i - 1] == y[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }
        }
    }

    // Walk backward through the completed table to restore one LCS.
    std::string sequence;
    int i = m;
    int j = n;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            sequence.push_back(x[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    std::reverse(sequence.begin(), sequence.end());
    return {dp[m][n], sequence};
}

int main() {
    const std::string x = "ABCBDAB";
    const std::string y = "BDCABA";
    const int tile_size = 64;
    const double start = omp_get_wtime();
    const LcsResult result = lcs_openmp(x, y, tile_size);
    std::cout << "LCS length: " << result.length << '\n' << "LCS: " << result.sequence
              << '\n' << "Time: " << omp_get_wtime() - start << " s\n";
}
