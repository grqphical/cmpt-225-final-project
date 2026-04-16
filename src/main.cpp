#include "avl_tree.hpp"
#include "csv.hpp"
#include "skip_list.hpp"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

// Higher run count for search/delete to get better averages
#define BATCH_SIZE 10000 
#define DATA_SIZE 100000

/**
 * Helper to get time in nanoseconds
 */
double get_nanos_per_op(std::chrono::high_resolution_clock::time_point start, 
                        std::chrono::high_resolution_clock::time_point end, 
                        int count) {
    auto total = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return static_cast<double>(total) / count;
}

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

int main() {
    std::vector<int> randomData = generateRandomArray(DATA_SIZE);
    std::vector<int> orderedData = generateSequentialArray(DATA_SIZE);
    
    // Pre-generate random indices for searching/deletion to avoid timing rand()
    std::vector<int> targets;
    for(int i = 0; i < BATCH_SIZE; i++) {
        targets.push_back(randomData[rand() % DATA_SIZE]);
    }

    // --- RANDOM INSERTION BENCHMARK ---
    std::cout << "Running random insertion benchmark..." << std::endl;
    CSVWriter<std::string> *random_insertion_writer = new CSVWriter<std::string>("random_insertion.csv", {"Data Structure", "Avg Time (ns)"});

    // Skip List
    auto start = std::chrono::high_resolution_clock::now();
    SkipList sl_rand;
    for (int i : randomData) sl_rand.Insert(i);
    auto end = std::chrono::high_resolution_clock::now();
    random_insertion_writer->WriteRow({"Skip List", std::to_string(get_nanos_per_op(start, end, DATA_SIZE))});

    // AVL Tree
    start = std::chrono::high_resolution_clock::now();
    AVLTree avl_rand;
    for (int i : randomData) avl_rand.Insert(i);
    end = std::chrono::high_resolution_clock::now();
    random_insertion_writer->WriteRow({"AVL Tree", std::to_string(get_nanos_per_op(start, end, DATA_SIZE))});

    delete random_insertion_writer;

    // --- ORDERED INSERTION BENCHMARK ---
    std::cout << "Running ordered insertion benchmark..." << std::endl;
    CSVWriter<std::string> *ordered_insertion_writer = new CSVWriter<std::string>("ordered_insertion.csv", {"Data Structure", "Avg Time (ns)"});
    
    start = std::chrono::high_resolution_clock::now();
    SkipList sl_ord;
    for (int i : orderedData) sl_ord.Insert(i);
    end = std::chrono::high_resolution_clock::now();
    ordered_insertion_writer->WriteRow({"Skip List", std::to_string(get_nanos_per_op(start, end, DATA_SIZE))});

    start = std::chrono::high_resolution_clock::now();
    AVLTree avl_ord;
    for (int i : orderedData) avl_ord.Insert(i);
    end = std::chrono::high_resolution_clock::now();
    ordered_insertion_writer->WriteRow({"AVL Tree", std::to_string(get_nanos_per_op(start, end, DATA_SIZE))});
    
    delete ordered_insertion_writer;

    // --- SEARCHING BENCHMARK ---
    std::cout << "Running search benchmark..." << std::endl;
    CSVWriter<std::string> *searching_writer = new CSVWriter<std::string>("searching.csv", {"Data Structure", "Avg Time (ns)"});

    start = std::chrono::high_resolution_clock::now();
    for (int target : targets) sl_rand.Search(target);
    end = std::chrono::high_resolution_clock::now();
    searching_writer->WriteRow({"Skip List", std::to_string(get_nanos_per_op(start, end, BATCH_SIZE))});

    start = std::chrono::high_resolution_clock::now();
    for (int target : targets) avl_rand.Search(target);
    end = std::chrono::high_resolution_clock::now();
    searching_writer->WriteRow({"AVL Tree", std::to_string(get_nanos_per_op(start, end, BATCH_SIZE))});
    
    delete searching_writer;

    // --- DELETION BENCHMARK ---
    std::cout << "Running deletion benchmark..." << std::endl;
    CSVWriter<std::string> *deletion_writer = new CSVWriter<std::string>("deletion.csv", {"Data Structure", "Avg Time (ns)"});

    // Benchmark Skip List Deletion
    start = std::chrono::high_resolution_clock::now();
    for (int target : targets) {
        sl_rand.Remove(target);
    }
    end = std::chrono::high_resolution_clock::now();
    deletion_writer->WriteRow({"Skip List", std::to_string(get_nanos_per_op(start, end, BATCH_SIZE))});

    // Benchmark AVL Deletion
    start = std::chrono::high_resolution_clock::now();
    for (int target : targets) {
        avl_rand.Delete(target);
    }
    end = std::chrono::high_resolution_clock::now();
    deletion_writer->WriteRow({"AVL Tree", std::to_string(get_nanos_per_op(start, end, BATCH_SIZE))});

    delete deletion_writer;
    std::cout << "Benchmarks complete. Results saved to CSV files." << std::endl;

    return 0;
}