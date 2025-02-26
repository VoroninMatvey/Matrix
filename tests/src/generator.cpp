#include <iostream>
#include "generator.hpp"

int main() {

    std::size_t matrix_size, max_det, num_of_tests;
    std::cin >> matrix_size >> max_det >> num_of_tests;
    Tests::generator gen(matrix_size, max_det, num_of_tests);
    gen.tests_generation();
}