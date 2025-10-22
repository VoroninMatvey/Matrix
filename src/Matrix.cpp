#include "Matrix.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

namespace {
template <typename T>
void reading_data(std::vector<T> &data, std::size_t size) {
  for (int k = 0; k < size; ++k)
    std::cin >> data[k];
}
} // namespace

int main() {
  std::size_t m_size = 0;
  std::cin >> m_size;

#ifdef INT_MATRIX
  std::vector<long long> vec(m_size * m_size);
  reading_data(vec, vec.size());
  details::Matrix<long long> m{m_size, m_size, vec.begin(), vec.end()};
#else
  std::vector<long double> vec(m_size * m_size);
  reading_data(vec, vec.size());
  details::Matrix<long double> m{m_size, m_size, vec.begin(), vec.end()};
#endif
  std::cout << m.determinant() << std::endl;
}