#include <iomanip>
#include <fstream>
#include<Tarea/JSONConverter.hpp>

void JSONConverter::write4DMatrix(const std::vector<std::vector<std::vector<std::vector<double>>>>& vec, std::ofstream& outFile,
    const std::string& dataName) {

    outFile <<"\"" << dataName << "\"" <<": [\n";;

    for (size_t i = 0; i < vec.size(); ++i) {
        outFile << "    [\n";
        for (size_t j = 0; j < vec[i].size(); ++j) {
            outFile << "      [\n";
            for (size_t k = 0; k < vec[i][j].size(); ++k) {
                outFile << "        [";
                for (size_t l = 0; l < vec[i][j][k].size(); ++l) {
                    outFile << std::fixed << std::setprecision(2) << vec[i][j][k][l];
                    if (l < vec[i][j][k].size() - 1) outFile << ", ";
                }
                outFile << "]";
                if (k < vec[i][j].size() - 1) outFile << ",";
                outFile << "\n";
            }
            outFile << "      ]";
            if (j < vec[i].size() - 1) outFile << ",";
            outFile << "\n";
        }
        outFile << "    ]";
        if (i < vec.size() - 1) outFile << ",";
        outFile << "\n";
    }

    outFile << "  ]\n";
}

void JSONConverter::writeVector(const std::vector<int> &vector, std::ofstream &outFile, const std::string &dataName) {
    outFile <<"\"" << dataName << "\"" <<": [\n";
    for (int i = 0; i < vector.size(); i++) {
        outFile << i;
        if (i < vector.size()-1)
            outFile << ",";
        outFile << "]\n";
    }
}
