#include "benchmark.hpp"
#include <algorithm>
#include <random>
#include <chrono>

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

long timeFunction(Benchmark func, std::vector<int> data) {
    auto start = std::chrono::high_resolution_clock::now();
    func(data);
    auto end = std::chrono::high_resolution_clock::now();

    auto milliseconds_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return static_cast<long>(milliseconds_elapsed.count());
}