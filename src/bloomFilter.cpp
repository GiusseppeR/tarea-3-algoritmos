
#include "Tarea/bloomFilter.hpp"
bool BloomFilter::sequentialSearch(std::string name) {

}

bool BloomFilter::search(std::string name, int k) {
    for(int i=0; i <k; i++) {
        unsigned int hash= h.hash(name, i);//aplicar funcion
        unsigned int resize = hash % this-> M.size(); //indice a revisar
        if (!this->M[resize]) return false; //si alguna de las busquedas es 0 definitivamente no esta
    }
    return true;//si no posiblemente esta
}

void BloomFilter::add(std::string name, int k) {
    for(int i=0; i <k; i++) { //para los k hash
        unsigned int hash = h.hash(name, i);
        unsigned int resize = hash % this-> M.size(); //indice a agregar
        this ->M[resize]=true; //poner en true
    }

}

