#include <Tarea/parser.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

CSVParser::CSVParser() = default;

std::vector<std::string> CSVParser::parse(const std::string &filename) {
    std::vector<std::string> result;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return result;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::string row;

        while (getline(lineStream, cell, ',')) {
            if (!row.empty()) {
                row += ",";
            }
            row += cell;
        }

        result.push_back(row);
    }

    file.close();
    return result;
}