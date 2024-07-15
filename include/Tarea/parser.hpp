//
// Created by giuss on 14-07-2024.
//

#ifndef TAREA3_PARSER_HPP
#define TAREA3_PARSER_HPP
#include <iostream>
#include <vector>
class CSVParser{
public:
    CSVParser();
    std::vector<std::string> parse(const std::string& filename);
};

#endif //TAREA3_PARSER_HPP
