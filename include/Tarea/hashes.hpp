#ifndef TAREA3_HASHES_HPP
#define TAREA3_HASHES_HPP

#include <cstdint>
#include <cstring>
#include <vector>

class Hashes {
private:
    std::vector<uint32_t> seeds;
public:
    Hashes(int k);
    int hash(const char *key, uint32_t len, int iterator);
};


#endif