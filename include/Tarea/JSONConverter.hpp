//
// Created by Giusseppe Rojas on 15-07-24.
//

#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H
#include <iostream>
#include <vector>

class JSONConverter {
public:
    static void writeReport(std::vector<int> M, std::vector<int> N, std::vector<int> k, std::vector<double> p,
        std::vector<std::vector<std::vector<std::vector<double>>>> errors,
        std::vector<std::vector<std::vector<std::vector<double>>>> filterTimes,
        std::vector<std::vector<std::vector<std::vector<double>>>> seqTimes);
    static void write4DMatrix(const std::vector<std::vector<std::vector<std::vector<double>>>>& vec, std::ofstream& outFile,
    const std::string& dataName, bool last);
    static void writeVectorInt(const std::vector<int>& vector, std::ofstream& outFile, const std::string& dataName);
    static void writeVectorDouble(const std::vector<double> &vector, std::ofstream& outFile, const std::string& dataName);


};
#endif //JSONCONVERTER_H
