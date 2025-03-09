#include <iostream>
#include "Matrix.hpp"
#include <vector>

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

    details::Matrix<double> m{size, size, vec.begin(), vec.end()};
    std::cout << "Matrix determinant is: " << m.determinant() << std::endl;

}