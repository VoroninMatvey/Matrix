#include <iostream>
#include "Matrix.hpp"

int main() { 

    details::Matrix<double> m1{4, 4};
    m1.print_Matrix();
    std::cout << std::endl;

    std::cout << m1.Gauss();
    std::cout << std::endl;

    std::vector<double> vec;
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




    details::Matrix<double> m2{4, 4, vec.begin(), vec.end()};
    m2.print_Matrix();
    std::cout << std::endl;
    std::cout << m2.Gauss();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << m2.Bareiss();

   /* details::Matrix<int> m3 = m2;
    m3.print_Matrix();
    std::cout << std::endl;

    m3 = m1;
    m3.print_Matrix();
    std::cout << std::endl;

    details::Matrix<int> m4 = std::move(m2);
    m4.print_Matrix();
    std::cout << std::endl;

    m4 = std::move(m3);
    m4.print_Matrix();

    details::Matrix<int> m = details::Matrix<int>::eye(15);
    m.print_Matrix();*/

}