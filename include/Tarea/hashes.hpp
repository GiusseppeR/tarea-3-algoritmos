#ifndef TAREA3_HASHES_HPP
#define TAREA3_HASHES_HPP

#include <cstdint>
#include <vector>
#include <iostream>

class Hashes {
private:
    std::vector<uint32_t> seeds;
    int _k;
public:
    Hashes(int k);
    int k();
    unsigned int hash(std::string input, int iterator);
};


#endif