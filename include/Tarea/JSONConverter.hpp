//
// Created by Giusseppe Rojas on 15-07-24.
//

#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H
#include <iostream>
#include <vector>

class JSONConverter {
public:
    void write4DMatrix(const std::vector<std::vector<std::vector<std::vector<double>>>>& vec, std::ofstream& outFile,
    const std::string& dataName);
    void writeVector(const std::vector<int>& vector, std::ofstream& outFile, const std::string& dataName);


};
#endif //JSONCONVERTER_H
