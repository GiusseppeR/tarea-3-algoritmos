#include<iostream>
#include <Tarea/hashes.hpp>
#include <Tarea/parser.hpp>
#include <random>
#include <chrono>
#include <Tarea/bloomFilter.hpp>
#include <algorithm>

int main(){
    CSVParser P;
    std::vector<std::string> films = P.parse("Film-Names.csv");
    std::vector<std::string> babies = P.parse("Popular-Baby-Names-Final.csv");

    std::vector<int> N = {1 << 10, 1<<12, 1<<14, 1<<16};
    std::vector<double> p = {0,0.25,0.5, 0.75, 1};
    std::vector<int> hashes = {1,5,10};
    std::vector<std::vector<double>> errors;
    std::vector<std::vector<double>> filterTimes;
    std::vector<std::vector<double>> sequentialTimes;

    for(auto k : hashes){
        std::vector<std::vector<std::string>> inputs(20, std::vector<std::string>());

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> filmDistrib(0, films.size()-1);
        std::uniform_int_distribution<int> babiesDistrib(0, babies.size()-1);

        BloomFilter filter(1000000,k);

        for(auto baby : babies){
            filter.add(baby);
        }

        for(int j = 0; j < N.size(); j++){
            int size = N[j];
            std::vector<int> nBabies;
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

        std::vector<double> counters(N.size()*p.size(),0);
        std::vector<double> bloomTimes(N.size()*p.size(),0);
        std::vector<double> seqTimes(N.size()*p.size(),0);

        for(int i = 0; i < N.size(); i++){
            for (int z = 0; z < p.size(); z++){
                for(int j = 0; j < N[i]; j++){
                    auto name = inputs[i*p.size() + z][j];

                    auto start = std::chrono::high_resolution_clock::now();
                    bool result1 = filter.search(name);
                    auto end = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> elapsed_seconds = end - start;
                    double time = elapsed_seconds.count();
                    bloomTimes[i*p.size() + z] += time;

                    if (result1){
                        bool result2 = filter.sequentialSearch(name,babies);
                        if (!(result1 && result2)) counters[i * p.size() + z] += 1.0;
                    }

                    start = std::chrono::high_resolution_clock::now();
                    filter.sequentialSearch(name,babies);
                    end = std::chrono::high_resolution_clock::now();

                    elapsed_seconds = end - start;
                    time = elapsed_seconds.count();
                    seqTimes[i*p.size() + z] += time;
                }
                counters[i*p.size() + z] /= N[i];
                std::cout << "For N = " << N[i] << ", k = " << k << ", p = "<< p[z] <<":" <<std::endl;
                std::cout << "error: " << (double)counters[i*p.size() + z]*100 << std::endl;
                std::cout << "Filter time: " << bloomTimes[i*p.size() + z] << std::endl;
                std::cout << "Seq time: " << seqTimes[i*p.size() + z] << std::endl;
                std::cout << "##################################################################\n";
            }
        }

        errors.push_back(counters);
        filterTimes.push_back(bloomTimes);
        sequentialTimes.push_back(seqTimes);

    }

    return 0;
}
