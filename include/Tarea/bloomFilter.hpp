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
    std::vector<bool> M;//vector para los bits
    Hashes h;

public:
    BloomFilter(int l, int k):M(l,false),h(k){} //inicializacion
    bool search(std::string name, int k); //metodo para buscar
    void add(std::string name, int k); //metodo para añadir ocupando k funciones de hash
    bool sequentialSearch(std::string name); //metodo para busqueda secuencial
};
#endif //BLOOM_FILTER_H
