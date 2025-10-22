#include "Matrix_iterator.hpp"
#include <algorithm>
#include <concepts>
#include <iostream>
#include <memory>
#include <utility>

namespace details {

template <typename T> void construct(T *p, const T &rhs) { new (p) T(rhs); }
template <typename T> void destroy(T *p) noexcept { p->~T(); }
template <typename Iter> void destroy(Iter first, Iter last) noexcept {
  while (first != last) {
    destroy(std::addressof(*first++));
  }
}

template <typename T> class ExtraBuffer {
protected:
  T **data_ = nullptr;
  std::size_t rows_ = 0;

  ExtraBuffer(const ExtraBuffer &) = delete;
  ExtraBuffer &operator=(const ExtraBuffer &) = delete;
  ExtraBuffer(ExtraBuffer &&rhs) noexcept
      : data_(std::exchange(rhs.data_, nullptr)),
        rows_(std::exchange(rhs.rows_, 0)) {}

  ExtraBuffer &operator=(ExtraBuffer &&rhs) noexcept {
    if (this != std::addressof(rhs)) {
      std::swap(data_, rhs.data_);
      std::swap(rows_, rhs.rows_);
    }
    return *this;
  }

  explicit ExtraBuffer(std::size_t size)
      : data_((size == 0)
                  ? nullptr
                  : static_cast<T **>(::operator new(size * sizeof(T *)))),
        rows_(size) {}

  ~ExtraBuffer() { ::operator delete(data_); }
}; // <-- class ExtraBuffer

template <typename T> class MatrixBuffer : protected ExtraBuffer<T> {
protected:
  using ExtraBuffer<T>::data_;
  using ExtraBuffer<T>::rows_;

  T *matrix_ptr_ = nullptr;
  std::size_t cols_, used_ = 0;

  MatrixBuffer(const MatrixBuffer &) = delete;
  MatrixBuffer &operator=(const MatrixBuffer &) = delete;
  MatrixBuffer(MatrixBuffer &&rhs) noexcept
      : ExtraBuffer<T>(std::move(rhs)),
        matrix_ptr_(std::exchange(rhs.matrix_ptr_, nullptr)),
        cols_(std::exchange(rhs.cols_, 0)), used_(std::exchange(rhs.used_, 0)) {
  }

  MatrixBuffer &operator=(MatrixBuffer &&rhs) noexcept {
    if (this != std::addressof(rhs)) {
      ExtraBuffer<T>::operator=(std::move(rhs));
      std::swap(matrix_ptr_, rhs.matrix_ptr_);
      std::swap(cols_, rhs.cols_);
      std::swap(used_, rhs.used_);
    }
    return *this;
  }

  MatrixBuffer(std::size_t rows = 0, std::size_t cols = 0)
      : ExtraBuffer<T>(rows),
        matrix_ptr_((rows * cols == 0) ? nullptr
                                       : static_cast<T *>(::operator new(
                                             sizeof(T) * rows * cols))),
        cols_(cols) {
    for (std::size_t i = 0; i < rows_; ++i) {
      data_[i] = matrix_ptr_ + i * cols_;
    }
  }

  ~MatrixBuffer() {
    destroy(matrix_ptr_, matrix_ptr_ + used_);
    ::operator delete(matrix_ptr_);
  }
}; // <-- MatrixBuffer

template <typename T> class Matrix : private MatrixBuffer<T> {

  using size_type = std::size_t;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using double_pointer = T **;
  using const_double_pointer = const T **;
  using iterator = Matrix_iterator<T>;
  using const_iterator = Matrix_iterator<const T>;
  using reverse_iterator = std::reverse_iterator<iterator>;

  using MatrixBuffer<T>::data_;
  using MatrixBuffer<T>::matrix_ptr_;
  using MatrixBuffer<T>::rows_;
  using MatrixBuffer<T>::cols_;
  using MatrixBuffer<T>::used_;

  struct ProxyRow {
    pointer row_;

    ProxyRow(pointer ptr) : row_(ptr) {}
    reference operator[](int n) { return row_[n]; }
    const_reference operator[](int n) const { return row_[n]; }
  };

public:
  ProxyRow operator[](int n) const { return ProxyRow{data_[n]}; }

  Matrix(size_type rows = 0, size_type cols = 0) : MatrixBuffer<T>(rows, cols) {
    value_type temp{};
    while (used_ < rows * cols) {
      construct(matrix_ptr_ + used_, temp);
      ++used_;
    }
  }

  template <typename It>
  Matrix(size_type rows, size_type cols, It beg, It end)
      : MatrixBuffer<T>(rows, cols) {
    if (std::distance(beg, end) != rows_ * cols_) {
      throw std::runtime_error("Mismatch of sizes");
    }
    while (used_ < rows * cols) {
      construct(matrix_ptr_ + used_, *beg);
      ++beg;
      ++used_;
    }
  }

  Matrix(Matrix &&rhs) noexcept = default;
  Matrix &operator=(Matrix &&rhs) noexcept = default;
  Matrix(const Matrix &rhs) : MatrixBuffer<T>(rhs.rows_, rhs.cols_) {
    while (used_ < rhs.used_) {
      construct(matrix_ptr_ + used_, rhs.matrix_ptr_[used_]);
      ++used_;
    }
  }

  Matrix &operator=(const Matrix &rhs) {
    if (this != std::addressof(rhs)) {
      Matrix tmp = rhs;
      swap(tmp);
    }
    return *this;
  }

  static Matrix eye(std::size_t n) {
    Matrix m{n, n};
    for (size_type i = 0; i < n; ++i) {
      m.data_[i][i] = 1;
    }
    return m;
  }

  void swap(Matrix &m) noexcept {
    std::swap(data_, m.data_);
    std::swap(matrix_ptr_, m.matrix_ptr_);
    std::swap(rows_, m.rows_);
    std::swap(cols_, m.cols_);
    std::swap(used_, m.used_);
  }

  size_type nrows() const noexcept { return rows_; }

  size_type ncols() const noexcept { return cols_; }

  value_type trace() const noexcept {
    value_type trace = 0;
    for (size_type k = 0; k < cols_; ++k) {
      trace += data_[k][k];
    }
    return trace;
  }

  Matrix &negate() &noexcept {
    for (auto &elem : *this) {
      elem *= -1;
    }
    return *this;
  }

  Matrix &transpose() & {
    if (cols_ == rows_)
      return square_matrix_transpose();

    Matrix &cur = *this;
    Matrix temp{cols_, rows_};
    for (size_type i = 0; i < temp.rows_; ++i) {
      for (size_type j = 0; j < temp.cols_; ++j) {
        temp[i][j] = cur[j][i];
      }
    }
    cur.swap(temp);
    return *this;
  }

  Matrix &square_matrix_transpose() & {
    auto &temp = *this;
    for (size_type i = 0; i < rows_ - 1; ++i) {
      for (size_type j = i + 1; j < cols_; ++j) {
        std::swap(temp[i][j], temp[j][i]);
      }
    }
    return *this;
  }

private:
  // Find for a row with a non-zero element at position [k][i], k > i. Return 0
  // if there is none
  int find_needed_row(int i) const noexcept {
    int k = i, row_num = 0;
    value_type max = 0;

    while (k != rows_) {
      if (std::abs(data_[k][i]) > max) {
        max = std::abs(data_[k][i]);
        row_num = k;
      }
      ++k;
    }
    return row_num;
  }

  // transforms the matrix to the desired form at loop iteration i before
  // running the algorithms, if necessary return 0, if temp[j][k] == 0 for all k
  // from j to rows_, else return 1
  int Gauss_transform(int j, Matrix &temp, value_type &det_sign) const noexcept {
    int num = temp.find_needed_row(j);

    if (num == 0)
      return 0;

    if (num != j) {
      std::swap(temp.data_[j], temp.data_[num]);
      det_sign *= -1;
    }
    return 1;
  }

  int Bareiss_transform(int j, Matrix& temp, int &det_sign) const noexcept {
    if(temp[j][j] != 0) return 1;
    int num = temp.find_needed_row(j);
    
    if(num != 0) {
        std::swap(temp.data_[j], temp.data_[num]);
        det_sign *= -1;
        return 1;
    } else return 0;
}

  // converting first row to zero element at position col_num using second row
  // with Gauss alghoritm
  void Gauss_convert_row(int row_num1, int row_num2, int col_num) {
    value_type coef = data_[row_num1][col_num] /
                      data_[row_num2][col_num]; // data_[row_num2][col_num] != 0
    for (size_type i = col_num; i < cols_; ++i) {
      data_[row_num1][i] -= coef * data_[row_num2][i];
    }
  }

  // converting first row to zero element at position col_num using second row
  // with Bareiss alghoritm
  void Bareiss_convert_row(int row_num1, int row_num2, int col_num,
                           value_type &denominator) noexcept {
    value_type row1_k = data_[row_num1][col_num];
    value_type row2_k = data_[row_num2][col_num];
    for (size_type i = col_num; i < cols_; ++i) {
      data_[row_num1][i] =
          (row2_k * data_[row_num1][i] - row1_k * data_[row_num2][i]) /
          denominator;
    }
  }

  value_type Gauss() const;
  value_type Bareiss() const;

public:
  value_type determinant() const {
    if (rows_ != cols_)
      throw std::runtime_error("The matrix is ​​not square");
    if constexpr (!std::signed_integral<T>) {
      return Gauss();
    } else {
      return Bareiss();
    }
  }

  iterator begin() const noexcept { return *data_; }
  iterator end() const noexcept { return *data_ + cols_ * rows_; }
  const_iterator cbegin() const noexcept { return *data_; }
  const_iterator cend() const noexcept { return *data_ + cols_ * rows_; }
}; // <-- Matrix

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &obj) {
  for (std::size_t i = 0, Rows = obj.nrows(); i < Rows; ++i) {
    for (std::size_t j = 0, Cols = obj.ncols(); j < Cols; ++j) {
      os << obj[i][j] << " ";
    }
    os << std::endl;
  }
  os << std::endl;
  return os;
}

template <typename T>
inline bool operator==(const details::Matrix<T> &lhs,
                       const details::Matrix<T> &rhs) {
  if (lhs.nrows() != rhs.nrows() || lhs.ncols() != rhs.ncols())
    return false;
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T> typename Matrix<T>::value_type Matrix<T>::Gauss() const {
  auto temp = *this;
  value_type det_sign = 1;
  for (std::size_t i = 0; i < temp.rows_ - 1; ++i) {
    Gauss_transform(i, temp, det_sign);
    if (temp[i][i] == 0)
      return 0;
    for (std::size_t j = i + 1; j < temp.rows_; ++j) {
      temp.Gauss_convert_row(j, i, i);
    }
  }

  for (std::size_t i = 0; i < temp.cols_; ++i)
    det_sign *= temp[i][i];
  return det_sign;
}

template <typename T>
typename Matrix<T>::value_type Matrix<T>::Bareiss() const {
  auto temp = *this;
  int det_sign = 1;
  value_type denominator = 1;
  for (std::size_t i = 0; i < temp.rows_ - 1; ++i) {
    Bareiss_transform(i, temp, det_sign);
    if (temp[i][i] == 0)
      return 0;
    for (std::size_t j = i + 1; j < temp.rows_; ++j) {
      temp.Bareiss_convert_row(j, i, i, denominator);
    }
    denominator = temp[i][i];
    if (!denominator)
      return 0;
  }

  return temp[temp.rows_ - 1][temp.cols_ - 1] * det_sign;
}
} // namespace details