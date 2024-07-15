#include<iostream>
#include <Tarea/parser.hpp>
#include <random>
#include <chrono>
#include <Tarea/bloomFilter.hpp>
#include <algorithm>

int main() {
    CSVParser P;
    std::vector<std::string> films = P.parse("../Film-Names.csv");
    std::vector<std::string> babies = P.parse("../Popular-Baby-Names-Final.csv");

    std::vector<int> N = {1 << 10, 1<<12, 1<<14, 1<<16};
    std::vector<double> p = {0,0.25,0.5, 0.75, 1};
    std::vector<int> hashes = {1,5,10};
    std::vector<int> M = {1<<14,1<<17,1<<20,1<<24};

    std::vector<std::vector<std::vector<std::vector<double>>>> errors(M.size());
    std::vector<std::vector<std::vector<std::vector<double>>>> filterTimes(M.size());
    std::vector<std::vector<std::vector<std::vector<double>>>> sequentialTimes(M.size());

    for(int i = 0; i < M.size(); i++) {
        errors[i].reserve(hashes.size());
        filterTimes[i].reserve(hashes.size());
        sequentialTimes[i].reserve(hashes.size());

        for(int j = 0; j < hashes.size(); j++) {
            errors[i][j].reserve(N.size());
            filterTimes[i][j].reserve(N.size());
            sequentialTimes[i][j].reserve(N.size());

            for(int k = 0; k < hashes.size(); k++) {
                errors[i][j][k].reserve(p.size());
                filterTimes[i][j][k].reserve(p.size());
                sequentialTimes[i][j][k].reserve(p.size());
            }
        }
    }

    for(int m = 0; m < M.size(); m++) {
        for(int k = 0; k < hashes.size(); k++){
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
                        auto end = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double> elapsed_seconds = end - start;
                        double time = elapsed_seconds.count();
                        bloomTimes[z] += time;

                        start = std::chrono::high_resolution_clock::now();
                        bool result2 = filter.sequentialSearch(name,babies);
                        end = std::chrono::high_resolution_clock::now();

                        elapsed_seconds = end - start;
                        time = elapsed_seconds.count();
                        seqTimes[z] += time;

                        if (result1 == true && result2 == false)
                            counters[z] += 1.0;

                    }
                    counters[z] /= N[i];

                    std::cout << "For M = " << M[m] << ", k = " << hashes[k] << ", N = " << N[i] << ", p = "<< p[z] <<":" <<std::endl;
                    std::cout << "error percentage: " << counters[z]*100 << std::endl;
                    std::cout << "Filter time: " << bloomTimes[z] << std::endl;
                    std::cout << "Seq time: " << seqTimes[z] << std::endl;
                    std::cout << "##################################################################\n";
                }
                errors[m][k][i] = counters;
                filterTimes[m][k][i] = bloomTimes;
                sequentialTimes[m][k][i] = seqTimes;
            }
        }
    }

    return 0;
}
