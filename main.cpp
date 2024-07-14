#include<iostream>
#include <Tarea/hashes.hpp>

int main(){
    Hashes h(10);
    std::string s = "lol";

    for(int i = 0; i < 10; i++){
        std::cout << h.hash(s.c_str(),3,i) << std::endl;
    }
    return 0;
}
