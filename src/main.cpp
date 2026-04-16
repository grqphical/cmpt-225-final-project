#include "benchmark.hpp"
#include "csv.hpp"
#include "skip_list.hpp"
#include <chrono>
#include <iostream>
#include <string>

#define BENCHMARK_RUN_COUNT 1000

long calculate_average(long data[]) {
  long sum = 0;
  for (int i = 0; i < BENCHMARK_RUN_COUNT; i++) {
    sum += data[i];
  }
  return sum / BENCHMARK_RUN_COUNT;
}

void benchmark_skip_list_insertion(std::vector<int> data) {
  SkipList list;
  for (int i : data) {
    list.Insert(i);
  }
}

int main() {
  CSVWriter<std::string> *writer =
      new CSVWriter<std::string>("output.csv", {"Name", "Skip List"});

  // random insertion benchmark
  std::cout << "Running random insertion on Skip List..." << std::endl;
  long results[BENCHMARK_RUN_COUNT];

  std::vector<int> randomData = generateRandomArray(10000);
  for (int i = 0; i < BENCHMARK_RUN_COUNT; i++) {

    results[i] = timeFunction(benchmark_skip_list_insertion, randomData);
    if (i % 100 == 0) {
      std::cout << "Ran " << i << " benchmarks..." << std::endl;
    }
  }
  long averageRunTime = calculate_average(results);
  writer->WriteRow({"Random Insertion", std::to_string(averageRunTime)});

  // ordered insertion benchmark
  std::cout << "Running ordered insertion on Skip List..." << std::endl;

  std::vector<int> orderedData = generateSequentialArray(10000);
  for (int i = 0; i < BENCHMARK_RUN_COUNT; i++) {

    results[i] = timeFunction(benchmark_skip_list_insertion, orderedData);
    if (i % 100 == 0) {
      std::cout << "Ran " << i << " benchmarks..." << std::endl;
    }
  }
  averageRunTime = calculate_average(results);
  writer->WriteRow({"Ordered Insertion", std::to_string(averageRunTime)});

  // searching through random tree
  std::cout << "Running search for random item on Skip List..." << std::endl;
  SkipList list;
  for (int i : randomData) {
    list.Insert(i);
  }

  for (int i = 0; i < BENCHMARK_RUN_COUNT; i++) {
    int target = randomData[rand() % randomData.size()];
    auto start = std::chrono::high_resolution_clock::now();
    list.Search(target);
    auto end = std::chrono::high_resolution_clock::now();

    auto milliseconds_elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    results[i] = static_cast<long>(milliseconds_elapsed.count());
    if (i % 100 == 0) {
      std::cout << "Ran " << i << " benchmarks..." << std::endl;
    }
  }
  averageRunTime = calculate_average(results);
  writer->WriteRow(
      {"Searching For Random Item", std::to_string(averageRunTime)});

  delete writer;

  return 0;
}