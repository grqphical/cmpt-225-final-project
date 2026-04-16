#include "benchmark.hpp"
#include "csv.hpp"
#include "skip_list.hpp"
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

  for (int i = 0; i < BENCHMARK_RUN_COUNT; i++) {
    std::vector<int> randomData = generateRandomArray(10000);
    results[i] = timeFunction(benchmark_skip_list_insertion, randomData);
    if (i % 100 == 0) {
      std::cout << "Ran " << i << " benchmarks..." << std::endl;
    }
  }
  long averageRunTime = calculate_average(results);
  writer->WriteRow({"Random Insertion", std::to_string(averageRunTime)});

  delete writer;

  return 0;
}