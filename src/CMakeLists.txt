set(HPP_LIST "${PROJECT_SOURCE_DIR}/include/Tarea/test.hpp")
set(CPP_LIST
        test.cpp
        hashes.cpp)

add_library(tarea  ${CPP_LIST} ${HPP_LIST})
target_include_directories(tarea PUBLIC ../include)