#include <Tarea/hashes.hpp>
#include <limits>
#include <cstring>
#include <random>

Hashes::Hashes(int k){
    int min = std::numeric_limits<int>::min();
    int max = std::numeric_limits<int>::max();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distrib(min, max);

    for(int i = 0; i < k; i++){
        uint32_t seed = (uint32_t) distrib(gen);
        seeds.push_back(seed);
    }
    _k = k;
}

unsigned int Hashes::hash(std::string input, int iterator){
    const char *key = input.c_str();
    uint32_t len = input.size();
    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;
    uint32_t r1 = 15;
    uint32_t r2 = 13;
    uint32_t m = 5;
    uint32_t n = 0xe6546b64;

    uint32_t hash = seeds[iterator];

    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *)key;
    int i;
    for (i = 0; i < nblocks; i++) {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = (hash << r2) | (hash >> (32 - r2));
        hash = hash * m + n;
    }

    const uint8_t *tail = (const uint8_t *)(key + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3) {
        case 3:
            k1 ^= tail[2] << 16;
        case 2:
            k1 ^= tail[1] << 8;
        case 1:
            k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << r1) | (k1 >> (32 - r1));
            k1 *= c2;
            hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}

int Hashes::k() {
    return _k;
}