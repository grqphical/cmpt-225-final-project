#pragma once
#include <vector>

// generates an array of integers from 0..n
std::vector<int> generateSequentialArray(int n);

// generates an array of integer from 0..n and then shuffles it so they are in a random order
std::vector<int> generateRandomArray(int n);