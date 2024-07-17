#include <iomanip>
#include <fstream>
#include<Tarea/JSONConverter.hpp>

void JSONConverter::writeReport(std::vector<int> M, std::vector<int> N, std::vector<int> k, std::vector<double> p, std::vector<std::vector<std::vector<std::vector<double> > > > errors, std::vector<std::vector<std::vector<std::vector<double> > > > filterTimes, std::vector<std::vector<std::vector<std::vector<double> > > > seqTimes) {
    std::ofstream file("report.json");

    file << "{\n";
    writeVectorInt(M,file,"filter_size");
    writeVectorInt(k,file,"number_of_hashes");
    writeVectorInt(N,file,"word_list_size");
    writeVectorDouble(p, file, "baby_names_proportion");
    write4DMatrix(errors,file,"error_percentages", false);
    write4DMatrix(filterTimes,file,"filtered_times",false);
    write4DMatrix(seqTimes,file,"sequential_times",true);
    file << "}";

    file.close();
}


void JSONConverter::write4DMatrix(const std::vector<std::vector<std::vector<std::vector<double>>>>& vec, std::ofstream& outFile,
    const std::string& dataName, bool last) {

    outFile <<"\"" << dataName << "\"" <<": [";
    for(int z = 0; z < vec.size(); z++) {
        auto M = vec[z];
        outFile << "[";
        for(int m = 0; m < M.size(); m++) {
            auto k = M[m];
            outFile << "[";
            for(int j  = 0; j < k.size(); j++) {
                auto N = k[j];
                outFile << "[";
                for (int i = 0; i < N.size(); i++) {
                    outFile << N[i];
                    if (i < N.size()-1)
                        outFile << ",";
                }
                outFile << "]";
                if(j < k.size() - 1) outFile << ",";
            }
            outFile << "]";
            if(m < M.size() - 1) outFile << ",";
        }
        outFile << "]";
        if(z < vec.size() - 1) outFile << ",";
    }
    outFile << "]";
    if(!last) outFile << ",";
    outFile << "\n";
}

void JSONConverter::writeVectorInt(const std::vector<int> &vector, std::ofstream &outFile, const std::string &dataName) {
    outFile <<"\"" << dataName << "\"" <<": [";
    for (int i = 0; i < vector.size(); i++) {
        outFile << vector[i];
        if (i < vector.size()-1)
            outFile << ",";
    }
    outFile << "],\n";
}

void JSONConverter::writeVectorDouble(const std::vector<double> &vector, std::ofstream &outFile, const std::string &dataName) {
    outFile <<"\"" << dataName << "\"" <<": [";
    for (int i = 0; i < vector.size(); i++) {
        outFile << vector[i];
        if (i < vector.size()-1)
            outFile << ",";
    }
    outFile << "],\n";
}