#pragma once

#include <algorithm>
#include <string>
#include <vector>

struct LcsResult {
    int length;
    std::string sequence;
};

inline LcsResult lcs_sequential(const std::string& x, const std::string& y) {
    const int m = static_cast<int>(x.size());
    const int n = static_cast<int>(y.size());
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (x[i - 1] == y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    std::string sequence;
    int i = m, j = n;
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
