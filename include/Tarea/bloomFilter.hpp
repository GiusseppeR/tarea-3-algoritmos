//
// Created by javiera romero orrego on 14-07-24.
//

#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H
#include <vector>
#include <iostream>
#include <string>

#include "hashes.hpp"

class BloomFilter {
private:
    Hashes h;

public:
    std::vector<bool> M;//vector para los bits
    BloomFilter(int l, int k):M(l,false),h(k){} //inicializacion
    bool search(std::string name); //metodo para buscar
    void add(std::string name); //metodo para añadir ocupando k funciones de hash
    bool sequentialSearch(std::string name, std::vector<std::string> domain); //metodo para busqueda secuencial
};
#endif //BLOOM_FILTER_H
