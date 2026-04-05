#include "benchmark.hpp"
#include <algorithm>
#include <random>

std::vector<int> generateSequentialArray(int n) {
    std::vector<int> result = std::vector<int>();
    for (int i = 0; i < n; i++) {
        result.push_back(i);
    }

    return result;
}

std::vector<int> generateRandomArray(int n) {
    std::vector<int> orderedArray = generateSequentialArray(n);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(orderedArray.begin(), orderedArray.end(), g);
    return orderedArray;
}