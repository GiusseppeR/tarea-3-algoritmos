#include<iostream>
#include <Tarea/parser.hpp>
#include <random>
#include <chrono>
#include <Tarea/bloomFilter.hpp>
#include <algorithm>

#include "Tarea/JSONConverter.hpp"

int main() {
    CSVParser P;
    JSONConverter reportGenerator;
    std::vector<std::string> films = P.parse("../Film-Names.csv");
    std::vector<std::string> babies = P.parse("../Popular-Baby-Names-Final.csv");

    std::vector<int> N = {1 << 10, 1 << 12, 1 << 14, 1 << 16};
    std::vector<double> p = {0, 0.25, 0.5, 0.75, 1};
    std::vector<int> hashes = {1, 5, 10};
    std::vector<int> M = {1 << 14, 1 << 17, 1 << 20, 1 << 24};

    std::vector<std::vector<std::vector<std::vector<double>>>> errors;
    std::vector<std::vector<std::vector<std::vector<double>>>> filterTimes;
    std::vector<std::vector<std::vector<std::vector<double>>>> sequentialTimes;

    for(int m = 0; m < M.size(); m++) {
        std::vector<std::vector<std::vector<double>>> counters_m;
        std::vector<std::vector<std::vector<double>>> bloomTimes_m;
        std::vector<std::vector<std::vector<double>>> seqTimes_m;
        for(int k = 0; k < hashes.size(); k++){
            std::vector<std::vector<double>> counters_k;
            std::vector<std::vector<double>> bloomTimes_k;
            std::vector<std::vector<double>> seqTimes_k;

            std::vector<std::vector<std::string>> inputs(20, std::vector<std::string>());

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> filmDistrib(0, films.size()-1);
            std::uniform_int_distribution<int> babiesDistrib(0, babies.size()-1);

            BloomFilter filter(M[m],hashes[k]);

            for(const auto& baby : babies){
                filter.add(baby);
            }

            for(int j = 0; j < N.size(); j++){
                int size = N[j];

                std::vector<int> nBabies;
                nBabies.reserve(p.size());
                for(double i : p){
                    nBabies.push_back(size*i);
                }

                for (int n = 0; n < nBabies.size(); n++){
                    auto *input = &inputs[nBabies.size()*j + n];
                    int nBaby = nBabies[n];
                    for (int i = 0; i < nBaby; i++){
                        std::string name = babies[babiesDistrib(gen)];
                        input->push_back(name);
                    }
                    for(int i = 0; i < size - nBaby; i++){
                        std::string name = films[filmDistrib(gen)];
                        input->push_back(name);
                    }
                    std::shuffle(input->begin(), input->end(), gen);
                }
            }
            std::vector<double> counters(p.size(),0);
            std::vector<double> bloomTimes(p.size(),0);
            std::vector<double> seqTimes(p.size(),0);

            for(int i = 0; i < N.size(); i++){
                for (int z = 0; z < p.size(); z++){
                    for(int j = 0; j < N[i]; j++){
                        auto name = inputs[i*p.size() + z][j];

                        auto start = std::chrono::high_resolution_clock::now();
                        bool result1 = filter.search(name);

                        if (result1) {
                            bool result2 = filter.sequentialSearch(name,babies);
                            if (result1 != result2)
                                counters[z] += 1;
                        }
                        auto end = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double> elapsed_seconds = end - start;
                        double time = elapsed_seconds.count();
                        bloomTimes[z] += time;

                        start = std::chrono::high_resolution_clock::now();
                        filter.sequentialSearch(name,babies);
                        end = std::chrono::high_resolution_clock::now();

                        elapsed_seconds = end - start;
                        time = elapsed_seconds.count();
                        seqTimes[z] += time;

                    }
                    counters[z] /= N[i];

                    std::cout << "For M = " << M[m] << ", k = " << hashes[k] << ", N = " << N[i] << ", p = "<< p[z] <<":" <<std::endl;
                    std::cout << "error percentage: " << counters[z]*100 << std::endl;
                    std::cout << "Filter time: " << bloomTimes[z] << std::endl;
                    std::cout << "Seq time: " << seqTimes[z] << std::endl;
                    std::cout << "##################################################################\n";
                }
                counters_k.push_back(counters);
                bloomTimes_k.push_back(bloomTimes);
                seqTimes_k.push_back(seqTimes);
            }
            counters_m.push_back(counters_k);
            bloomTimes_m.push_back(bloomTimes_k);
            seqTimes_m.push_back(seqTimes_k);
        }
        errors.push_back(counters_m);
        filterTimes.push_back(bloomTimes_m);
        sequentialTimes.push_back(seqTimes_m);
    }
    JSONConverter::writeReport(M,N,hashes,p,errors,filterTimes,sequentialTimes);

    return 0;
}
