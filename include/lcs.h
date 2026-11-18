#pragma once

#include <algorithm>
#include <string>
#include <vector>

struct LcsResult {
    int length;
    std::string sequence;
};

inline LcsResult lcs_sequential(const std::string& first, const std::string& second) {
    const int row = static_cast<int>(first.size());
    const int column = static_cast<int>(second.size());

    // Create a table with an extra empty row and column for the base cases.
    std::vector<std::vector<int>> dp(row + 1, std::vector<int>(column + 1, 0));

    // Fill the table with the LCS lengths for each pair of prefixes.
    for (int current_row = 1; current_row <= row; ++current_row) {
        for (int current_column = 1; current_column <= column; ++current_column) {
            if (first[current_row - 1] == second[current_column - 1]) {
                dp[current_row][current_column] = dp[current_row - 1][current_column - 1] + 1;
            } else {
                dp[current_row][current_column] =
                    std::max(dp[current_row - 1][current_column], dp[current_row][current_column - 1]);
            }
        }
    }

    // Walk backward through the table to restore one longest common subsequence.
    std::string sequence;
    int current_row = row;
    int current_column = column;
    while (current_row > 0 && current_column > 0) {
        if (first[current_row - 1] == second[current_column - 1]) {
            sequence.push_back(first[current_row - 1]);
            --current_row;
            --current_column;
        } else if (dp[current_row - 1][current_column] >= dp[current_row][current_column - 1]) {
            --current_row;
        } else {
            --current_column;
        }
    }

    std::reverse(sequence.begin(), sequence.end());
    return {dp[row][column], sequence};
}
