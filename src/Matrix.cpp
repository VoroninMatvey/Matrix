#include <iostream>
#include "Matrix.hpp"
#include <vector>

int main() { 

/*details::Matrix<double> m1{4, 4};
    m1.dump(std::cout);
    std::cout << std::endl;

    std::cout << m1.Gauss();
    std::cout << std::endl;*/

    std::vector<int> vec;
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

    details::Matrix<int> m{4, 4, vec.begin(), vec.end()};
    details::Matrix<int>::iterator it = m.begin();
    while(it != m.end()) {
        std:: cout << *it << " ";
        ++it;
    }
    std::cout <<std::endl;
    details::Matrix<int> m3 = m;
    std:: cout << (m == m3) << "success";
    //details::Matrix<int> q{4, 4};
    //std:: cout << (m == q) << "success";
    //std::cout << m << std::endl;
    //std::cout << m[2][2] << std::endl;
    //std::cout << m.Bareiss() << std::endl;



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