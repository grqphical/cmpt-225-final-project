#pragma once
#include <fstream>
#include <string>
#include <vector>

// takes tabular data and outputs it to a file in CSV format
template <typename T> class CSVWriter {
public:
  CSVWriter(std::string outputFileName, std::vector<T> header) {
    outputFile.open(outputFileName);
    WriteRow(header);
  };
  ~CSVWriter() { outputFile.close(); };
  void WriteRow(std::vector<T> row) {
    for (int i = 0; i < row.size(); i++) {
        outputFile << row[i];
        if (i < row.size() - 1) {
            outputFile << ",";
        } else {
            outputFile << "\n";
        }
    }
};

private:
  std::ofstream outputFile;
};