#include "lcs.h"
#include <iostream>

int main() {
    const std::string x = "ABCBDAB";
    const std::string y = "BDCABA";
    const LcsResult result = lcs_sequential(x, y);
    std::cout << "LCS length: " << result.length << '\n'
              << "LCS: " << result.sequence << '\n';
}
