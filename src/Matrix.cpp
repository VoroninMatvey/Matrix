#include "Matrix.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace {
template <typename T>
void reading_data(std::vector<T> &data, std::size_t size) {
  for (int k = 0; k < size; ++k)
    std::cin >> data[k];
}

bool need_to_round(const long double &determinant) {
  long double det_round = std::round(determinant);
  return std::abs(determinant - det_round) < 1e-2L;
}

} // namespace

int main() {
  std::size_t m_size = 0;
  std::cin >> m_size;

#ifdef INT_MATRIX
  std::vector<long long> vec(m_size * m_size);
  reading_data(vec, vec.size());
  details::Matrix<long long> m{m_size, m_size, vec.begin(), vec.end()};
  std::cout << m.determinant() << std::endl;
#else
  std::vector<long double> vec(m_size * m_size);
  reading_data(vec, vec.size());
  details::Matrix<long double> m{m_size, m_size, vec.begin(), vec.end()};
  long double determinant = m.determinant();

  if (need_to_round(determinant)) {
    std::cout << std::fixed << std::setprecision(0) << determinant << std::endl;
  } else {
    std::cout << std::fixed << determinant << std::endl;
  }
#endif
}