set(HPP_LIST "${PROJECT_SOURCE_DIR}/include/Tarea/bloomFilter.hpp"
        "${PROJECT_SOURCE_DIR}/include/Tarea/hashes.hpp"
        "${PROJECT_SOURCE_DIR}/include/Tarea/parser.hpp")

set(CPP_LIST
        hashes.cpp
        bloomFilter.cpp
        parser.cpp
        JSONConverter.cpp)

add_library(tarea  ${CPP_LIST} ${HPP_LIST})
target_include_directories(tarea PUBLIC ../include)