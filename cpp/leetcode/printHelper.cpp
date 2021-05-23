#include "printHelper.hpp"

#include <iostream>
#include <vector>

void printVectorVector(std::vector<std::vector<int>> vec) {
    int i = 0, j = 0;
    std::cout << "[" << std::endl;
    for (i = 0; i < vec.size(); i++) {
        std::cout << "  [";
        for (j = 0; j < vec[i].size() - 1; j++) {
            std::cout << vec[i][j] << ",";
        }
        std::cout << vec[i][j];
        std::cout << "]," << std::endl;
    }
    std::cout << "]" << std::endl;
}

void printVector(std::vector<int> vec) {
    std::cout << "[";
    int len = vec.size();
    if (len > 0) {
        for (int i = 0; i < len - 1; i++) {
            std::cout << vec[i] << ",";
        }
        std::cout << vec[len - 1];
    }
    std::cout << "]" << std::endl;
}
