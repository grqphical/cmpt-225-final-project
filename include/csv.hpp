#pragma once
#include <string>
#include <vector>
#include <fstream> 

// takes tabular data and outputs it to a file in CSV format
class CSVWriter {
public:
    CSVWriter(std::string outputFileName, std::vector<std::string> header);
    ~CSVWriter();
    void WriteRow(std::vector<std::string>);
private:
    std::ofstream outputFile;
    std::vector<std::vector<std::string>> table;
};