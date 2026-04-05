#pragma once
#include <vector>
#include <functional>
#include <string>

typedef std::function<void(std::vector<int>)> Benchmark;

// generates an array of integers from 0..n
std::vector<int> generateSequentialArray(int n);

// generates an array of integer from 0..n and then shuffles it so they are in a random order
std::vector<int> generateRandomArray(int n);

// times how long a function takes to run and prints the result
void timeFunction(Benchmark func, std::vector<int> data, std::string funcName);