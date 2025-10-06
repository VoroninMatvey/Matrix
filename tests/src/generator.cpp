#include <iostream>
#include "generator.hpp"

int main(int argc, char* argv[]) {
    
    if(argc < 2) {
        std::cerr << "Not enough command line arguments" << std::endl;
        return 1;
    }

    std::size_t matrix_size, max_det, num_of_tests;
    std::cin >> matrix_size >> max_det >> num_of_tests;
    Tests::generator gen(matrix_size, max_det, num_of_tests, argv[1]);
    gen.tests_generation();
}