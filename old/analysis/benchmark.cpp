#include "lcs.h"
#include <chrono>
#include <iostream>
#include <random>
#include <string>

int main() {
    const int size = 2000;
    std::mt19937 generator(29);
    std::uniform_int_distribution<int> symbol('A', 'Z');
    std::string x(size, 'A'), y(size, 'A');
    for (char& c : x) c = static_cast<char>(symbol(generator));
    for (char& c : y) c = static_cast<char>(symbol(generator));

    const auto start = std::chrono::steady_clock::now();
    const LcsResult result = lcs_sequential(x, y);
    const auto stop = std::chrono::steady_clock::now();
    const double seconds = std::chrono::duration<double>(stop - start).count();
    std::cout << "Input length: " << size << "\nLCS length: " << result.length
              << "\nSequential time: " << seconds << " s\n";
}
