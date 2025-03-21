#include <iostream>
#include "Matrix.hpp"
#include <vector>
#include <iomanip>

template<typename T>
void reading_data(std::vector<T>& data, std::size_t sq_size) {
    for(int k = 0; k < sq_size; ++k) std::cin >> data[k];
}

int main() { 
    std::size_t size = 0;
    std::cin >> size;

    std::vector<double> vec;
    vec.resize(size*size);
    reading_data(vec, size*size);

    #ifdef gauss
        details::Matrix<double> m{size, size, vec.begin(), vec.end()};
        std::cout << std::fixed << std::setprecision(0) << m.determinant() << std::endl;
    #endif

    #ifdef bareiss 
        details::Matrix<int> m{size, size, vec.begin(), vec.end()};
        std::cout << std::fixed << std::setprecision(0) << m.determinant() << std::endl;
    #endif
}