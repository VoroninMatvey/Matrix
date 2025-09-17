#include <iostream>
#include "Matrix.hpp"
#include <vector>
#include <iomanip>

template<typename T>
void reading_data(std::vector<T>& data, std::size_t size) {
    for(int k = 0; k < size; ++k) std::cin >> data[k];
}

int main() { 
    std::size_t m_size = 0;
    std::cin >> m_size;

    std::vector<double> vec;
    vec.resize(m_size*m_size);
    reading_data(vec, vec.size());

    #ifdef gauss
        details::Matrix<double> m{m_size, m_size, vec.begin(), vec.end()};
        std::cout << std::fixed << std::setprecision(0) << m.determinant() << std::endl;
    #endif

    #ifdef bareiss 
        details::Matrix<int> m{m_size, m_size, vec.begin(), vec.end()};
        std::cout << std::fixed << std::setprecision(0) << m.determinant() << std::endl;
    #endif
}