#pragma once

#include <algorithm>
#include <string>
#include <vector>

struct LcsResult {
    int length;
    std::string sequence;
};

inline LcsResult lcs_sequential(const std::string& first, const std::string& second) {
    const int first_length = static_cast<int>(first.size());
    const int second_length = static_cast<int>(second.size());

    // Create a table with an extra empty row and column for the base cases.
    std::vector<std::vector<int>> dp(
        first_length + 1,
        std::vector<int>(second_length + 1, 0)
    );

    // Fill the table with the LCS lengths for each pair of prefixes.
    for (int current_row = 1; current_row <= first_length; ++current_row) {
        for (int current_column = 1; current_column <= second_length; ++current_column) {
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
    int current_row = first_length;
    int current_column = second_length;
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
    return {dp[first_length][second_length], sequence};
}
