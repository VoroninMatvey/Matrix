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
    std::cout << "norm1_____________________________";
    std::cout << "Matrix determinant is: " << m.determinant();
    std::cout << "norm2_____________________________";

/*details::Matrix<double> m1{4, 4};
    m1.dump(std::cout);
    std::cout << std::endl;

    std::cout << m1.Gauss();
    std::cout << std::endl;*/

    /*std::vector<int> vec;
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(1);

    details::Matrix<double> m{4, 4, vec.begin(), vec.end()};
    std::cout << m << std::endl;
    std::cout << m.determinant() << std::endl;*/
    /*details::Matrix<int> m1{4, 4};
    details::Matrix<int>::iterator it = m.begin();
    std::cout <<std::endl;
    details::Matrix<int> m3 = m;
    std:: cout << (m1== m3) << "success" << std::endl;
    std::cout << m3 << std::endl;
    std::cout << m3.transpose() << std::endl;
    std::cout << m3.negate() << std::endl;*/
    //details::Matrix<int> q{4, 4};
    //std:: cout << (m == q) << "success";
    //std::cout << m << std::endl;
    //std::cout << m[2][2] << std::endl;
    //std::cout << m.Bareiss() << std::endl;

    /*details::Matrix<int> m1{3, 4, vec.begin(), vec.end()};
    std::cout << m1 << std::endl;
    std::cout << m1.transpose() << std::endl;*/


    /*details::Matrix<double> m2{4, 4, vec.begin(), vec.end()};
    m2.dump(std::cout);
    std::cout << std::endl;
    std::cout << m2.Gauss();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << m2.Bareiss() <<std::endl;

    details::Matrix<double> m3 = m2;
    m3.dump(std::cout);
    std::cout << std::endl;

    m3 = m1;
    m3.dump(std::cout);
    std::cout << std::endl;

    details::Matrix<double> m4 = std::move(m2);
    m4.dump(std::cout);
    std::cout << std::endl;

    m4 = std::move(m3);
    m4.dump(std::cout);
    std::cout << std::endl;

    details::Matrix<int> m = details::Matrix<int>::eye(15);
    m.dump(std::cout);*/

}