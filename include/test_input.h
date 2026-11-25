#pragma once

#include <random>
#include <string>

inline std::string generate_random_string(int length, std::mt19937& generator) {
    std::uniform_int_distribution<int> letter('A', 'Z');
    std::string text(length, 'A');

    for (char& character : text) {
        character = static_cast<char>(letter(generator));
    }

    return text;
}
