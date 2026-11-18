#include "lcs.h"
#include <chrono>
#include <iostream>
#include <random>
#include <string>

std::string generate_random_string(int length, std::mt19937& generator) {
    std::uniform_int_distribution<int> symbol('A', 'Z');
    std::string value(length, 'A');
    for (char& character : value) {
        character = static_cast<char>(symbol(generator));
    }
    return value;
}

int main() {
    const int size = 2000;
    std::mt19937 generator(29);

    // Create the input strings.
    const std::string x = generate_random_string(size, generator);
    const std::string y = generate_random_string(size, generator);

    // Measure the sequential LCS run.
    const auto start = std::chrono::steady_clock::now();
    const LcsResult result = lcs_sequential(x, y);
    const auto stop = std::chrono::steady_clock::now();
    const double seconds = std::chrono::duration<double>(stop - start).count();

    // Print the result.
    std::cout << "Input length: " << size << "\nLCS length: " << result.length
              << "\nSequential time: " << seconds << " s\n";
}
