
#include "Tarea/bloomFilter.hpp"
bool BloomFilter::sequentialSearch(std::string name, std::vector<std::string> domain) {
    for(auto s : domain){
        if(std::equal(name.begin(), name.end(),s.begin(),s.end())){
            return true;
        }
    }
    return false;
}

bool BloomFilter::search(std::string name) {
    for(int i=0; i <h.k(); i++) {
        unsigned int hash= h.hash(name, i);//aplicar funcion
        unsigned int resize = hash % this-> M.size(); //indice a revisar
        if (!this->M[resize]) return false; //si alguna de las busquedas es 0 definitivamente no esta
    }
    return true;//si no posiblemente esta
}

void BloomFilter::add(std::string name) {
    for(int i=0; i <h.k(); i++) { //para los k hash
        unsigned int hash = h.hash(name, i);
        unsigned int resize = hash % this-> M.size(); //indice a agregar
        this ->M[resize]=true; //poner en true
    }

}

