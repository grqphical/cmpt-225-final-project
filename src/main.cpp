#include "benchmark.hpp"
#include "avl_tree.hpp"
#include "csv.hpp"
#include "skip_list.hpp"
#include <chrono>
#include <iostream>
#include <string>

#define BENCHMARK_RUN_COUNT 500

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

void benchmark_avl_tree_insertion(std::vector<int> data) {
  AVLTree tree;
  for (int i : data) {
    tree.Insert(i);
  }
}

int main() {
  CSVWriter<std::string> *random_insertion_writer =
      new CSVWriter<std::string>("random_insertion.csv", {"Data Structure", "Time"});

  // random insertion benchmark
  std::cout << "Running random insertion benchmark" << std::endl;
  long skipListResults[BENCHMARK_RUN_COUNT];
  long avlTreeResults[BENCHMARK_RUN_COUNT];

  std::vector<int> randomData = generateRandomArray(50000);
  for (int i = 0; i < BENCHMARK_RUN_COUNT; i++) {
    skipListResults[i] = timeFunction(benchmark_skip_list_insertion, randomData);
    avlTreeResults[i] = timeFunction(benchmark_avl_tree_insertion, randomData);
    if (i % 100 == 0) {
      std::cout << "Ran " << i << " benchmarks..." << std::endl;
    }
  }
  random_insertion_writer->WriteRow({"Skip List", std::to_string(calculate_average(skipListResults))});
  random_insertion_writer->WriteRow({"AVL Tree", std::to_string(calculate_average(avlTreeResults))});
  delete random_insertion_writer;

  // ordered insertion benchmark
  std::cout << "Running ordered insertion on Skip List..." << std::endl;
  CSVWriter<std::string> *ordered_insertion_writer =
      new CSVWriter<std::string>("ordered_insertion.csv", {"Data Structure", "Time"});

  std::vector<int> orderedData = generateSequentialArray(50000);
  for (int i = 0; i < BENCHMARK_RUN_COUNT; i++) {
    skipListResults[i] = timeFunction(benchmark_skip_list_insertion, randomData);
    avlTreeResults[i] = timeFunction(benchmark_avl_tree_insertion, randomData);
    if (i % 100 == 0) {
      std::cout << "Ran " << i << " benchmarks..." << std::endl;
    }
  }
  ordered_insertion_writer->WriteRow({"Skip List", std::to_string(calculate_average(skipListResults))});
  ordered_insertion_writer->WriteRow({"AVL Tree", std::to_string(calculate_average(avlTreeResults))});
  delete ordered_insertion_writer;

  // searching through random tree
  std::cout << "Running search for random item..." << std::endl;
  CSVWriter<std::string> *searching_writer =
      new CSVWriter<std::string>("searching.csv", {"Data Structure", "Time"});

  SkipList list;
  AVLTree tree;
  for (int i : randomData) {
    list.Insert(i);
    tree.Insert(i);
  }

  for (int i = 0; i < BENCHMARK_RUN_COUNT; i++) {
    int target = randomData[rand() % randomData.size()];
    auto start = std::chrono::high_resolution_clock::now();
    list.Search(target);
    auto end = std::chrono::high_resolution_clock::now();

    auto microseconds_elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    skipListResults[i] = static_cast<long>(microseconds_elapsed.count());

    start = std::chrono::high_resolution_clock::now();
    tree.Search(target);
    end = std::chrono::high_resolution_clock::now();

    microseconds_elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    avlTreeResults[i] = static_cast<long>(microseconds_elapsed.count());
    if (i % 100 == 0) {
      std::cout << "Ran " << i << " benchmarks..." << std::endl;
    }
  }
  searching_writer->WriteRow({"Skip List", std::to_string(calculate_average(skipListResults))});
  searching_writer->WriteRow({"AVL Tree", std::to_string(calculate_average(avlTreeResults))});
  delete searching_writer;

  std::cout << "Running deletion of random item..." << std::endl;
  CSVWriter<std::string> *deletion_writer =
      new CSVWriter<std::string>("deletion.csv", {"Data Structure", "Time"});

  for (int i = 0; i < BENCHMARK_RUN_COUNT; i++) {
    int target = randomData[rand() % randomData.size()];

     auto start = std::chrono::high_resolution_clock::now();
    list.Remove(target);
    auto end = std::chrono::high_resolution_clock::now();

    auto microseconds_elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    skipListResults[i] = static_cast<long>(microseconds_elapsed.count());

    start = std::chrono::high_resolution_clock::now();
    tree.Delete(target);
    end = std::chrono::high_resolution_clock::now();

    microseconds_elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    avlTreeResults[i] = static_cast<long>(microseconds_elapsed.count());
    if (i % 100 == 0) {
      std::cout << "Ran " << i << " benchmarks..." << std::endl;
    }
  }
  deletion_writer->WriteRow({"Skip List", std::to_string(calculate_average(skipListResults))});
  deletion_writer->WriteRow({"AVL Tree", std::to_string(calculate_average(avlTreeResults))});
  delete deletion_writer;

  return 0;
}