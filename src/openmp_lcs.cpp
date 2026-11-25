#include "lcs_openmp.h"
#include <algorithm>
#include <vector>

LcsResult lcs_openmp(const std::string& first, const std::string& second, int tile_size) {
    const int first_length = static_cast<int>(first.size());
    const int second_length = static_cast<int>(second.size());
    std::vector<std::vector<int>> dp(
        first_length + 1,
        std::vector<int>(second_length + 1, 0)
    );

    const int tile_rows = (first_length + tile_size - 1) / tile_size;
    const int tile_columns = (second_length + tile_size - 1) / tile_size;

    for (int wave = 0; wave < tile_rows + tile_columns - 1; ++wave) {
        #pragma omp parallel for schedule(static)
        for (int tile_row = 0; tile_row < tile_rows; ++tile_row) {
            const int tile_column = wave - tile_row;
            if (tile_column < 0 || tile_column >= tile_columns) {
                continue;
            }

            const int last_row = std::min(first_length, (tile_row + 1) * tile_size);
            const int last_column = std::min(second_length, (tile_column + 1) * tile_size);

            for (int row = tile_row * tile_size + 1; row <= last_row; ++row) {
                for (int column = tile_column * tile_size + 1; column <= last_column; ++column) {
                    if (first[row - 1] == second[column - 1]) {
                        dp[row][column] = dp[row - 1][column - 1] + 1;
                    } else {
                        dp[row][column] = std::max(dp[row - 1][column], dp[row][column - 1]);
                    }
                }
            }
        }
    }

    std::string sequence;
    int row = first_length;
    int column = second_length;
    while (row > 0 && column > 0) {
        if (first[row - 1] == second[column - 1]) {
            sequence.push_back(first[row - 1]);
            --row;
            --column;
        } else if (dp[row - 1][column] >= dp[row][column - 1]) {
            --row;
        } else {
            --column;
        }
    }

    std::reverse(sequence.begin(), sequence.end());
    return {dp[first_length][second_length], sequence};
}
