#include <iostream>
#include <iterator>
#include <utility>
#include <algorithm>
#include "Matrix_iterator.hpp"

namespace details {
template <typename T> class Matrix {
    public:

        using size_type = std::size_t;
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using double_pointer = T**;
        using const_double_pointer = const T**;
        using iterator = Matrix_iterator<T>;
        using const_iterator = Matrix_iterator<const T>;
        using reverse_iterator = std::reverse_iterator<iterator>;

        struct ProxyRow {
            pointer row_;

            ProxyRow(pointer ptr): row_(ptr) {}
            reference operator[](int n) { return row_[n]; }
            const_reference operator[](int n) const {return row_[n]; }
        };

        Matrix(size_type rows, size_type cols) : data_(new pointer[rows]), rows_(rows), cols_(cols) {
            pointer matrix_ptr = new value_type[rows_*cols_]{};
            filling_data_field(matrix_ptr);
        }

        template<typename It>
        Matrix(size_type rows, size_type cols, It beg, It end) : data_(new pointer[rows]), rows_(rows), cols_(cols) { //сделать выброс исключеняи
            if(std::distance(beg, end) == rows_*cols_) {
                pointer matrix_ptr = new value_type[rows*cols];
                filling_data_field(matrix_ptr);
                std::copy(beg, end, data_[0]);
            } else {
                std::cout << "bad initialization!!!!!" << std::endl;
                exit(0);
            } 
        }

        Matrix(const Matrix &rhs): data_(new pointer[rhs.rows_]), rows_(rhs.rows_), cols_(rhs.cols_) {
            pointer matrix_ptr = new value_type[rows_*cols_];
            filling_data_field(matrix_ptr);
            std::copy(rhs.data_[0], rhs.data_[0] + cols_*rows_, data_[0]);
        }

        Matrix& operator=(const Matrix &rhs) {
            if(this == &rhs) return *this;
            Matrix new_m = rhs;
            swap(new_m);
            return *this;    
        }

        Matrix(Matrix&& rhs) noexcept :
            data_(std::exchange(rhs.data_, nullptr)),
            rows_(std::exchange(rhs.rows_, 0)),
            cols_(std::exchange(rhs.cols_, 0)) 
        {}

        Matrix& operator= (Matrix&& rhs) noexcept {
            if(this == &rhs) return *this;
            Matrix m = std::move(rhs);
            swap(m);
            return *this;
        }

        ~Matrix() {
            if(data_) delete[] *data_;
            delete[] data_;
        }

        static Matrix eye(std::size_t n) {
            Matrix m{n, n};
            for(int i = 0; i < n; ++i)  {
                m.data_[i][i] = 1;
            }
            return m;
        }

        void swap(Matrix& m) {
            std::swap(cols_, m.cols_);
            std::swap(rows_, m.rows_);
            std::swap(data_, m.data_);
        }

        iterator begin() const {
            return *data_;
        }

        iterator end() const {
            return *data_ + cols_*rows_;
        }

        size_type ncols() const {
            return cols_;
        }

        size_type nrows() const {
            return rows_;
        }

        value_type trace() const {
            T trace = 1;
            for(int k = 0; k < cols_; ++k) {
                trace *= data_[k][k];
            }
            return trace;
        }

        void filling_data_field(pointer ptr) {
            for(int i = 0; i < rows_; ++i) {
                data_[i] = ptr + i*cols_;
            }
        }

        ProxyRow operator[](int n) const {
            return ProxyRow{data_[n]};
        } 

        //Find for a row with a non-zero element at position [k][i], k > i. Return 0 if there is none
        int find_needed_row(int i) const {
            int k = ++i;
            while(k != rows_) {
                if(data_[k][i] != 0) return k;
                ++k;
            }
            return 0;
        }

        //converting first row to zero element at position col_num using second row with Gauss alghoritm
        void Gauss_convert_row(int row_num1, int row_num2, int col_num) {
            double coef = data_[row_num1][col_num] / data_[row_num2][col_num]; //double?
            for(int i = col_num; i < cols_; ++i) {
                data_[row_num1][i] -= coef*data_[row_num2][i];
            }
        }

        value_type denominator_ = 1;
        //converting first row to zero element at position col_num using second row with Bareiss alghoritm
        void Bareiss_convert_row(int row_num1, int row_num2, int col_num) {
            value_type row1_k = data_[row_num1][col_num];
            value_type row2_k = data_[row_num2][col_num];
            for(int i = col_num; i < cols_; ++i) {
                data_[row_num1][i] = (row2_k*data_[row_num1][i] - row1_k*data_[row_num2][i]) / denominator_;
            }
        }

        value_type Gauss() const;
        value_type Bareiss() const;

private:
        double_pointer data_;
        size_type rows_; // количество строк
        size_type cols_; // количество столбцов

}; // <-- namespace Matrix

template<typename T>
typename Matrix<T>::value_type Matrix<T>::Gauss() const { //why typename
    auto m = *this;
    int def_sign = 1;
    for(int i = 0; i < m.rows_ - 1; ++i) {
        if(m.data_[i][i] == 0) {
            int num = m.find_needed_row(i);
            if(num != 0) {
                std::swap(m.data_[i], m.data_[num]);
                def_sign *= -1;
            } else continue;
        }

        for(int j = i + 1; j < m.rows_; ++j) {
            m.Gauss_convert_row(j, i, i);
            std::cout << m << std::endl;
        }
    }

    value_type det = 1;
    for(int i = 0; i < m.rows_; ++i) {
        det *= m.data_[i][i];
    }
    return det*def_sign;
}

template<typename T>
typename Matrix<T>::value_type Matrix<T>::Bareiss() const {
    auto m = *this;
    int def_sign = 1;
    for(int i = 0; i < m.rows_ - 1; ++i) {
        if(m.data_[i][i] == 0) {
            int num = m.find_needed_row(i);
            if(num != 0) {
                std::swap(m.data_[i], m.data_[num]);
                def_sign *= -1;
            } else continue;
        }

        for(int j = i + 1; j < m.rows_; ++j) {
            m.Bareiss_convert_row(j, i, i);
            std::cout << m << std::endl;
        }
        m.denominator_ = m.data_[i][i];
    }
    return m.data_[m.rows_ - 1][m.cols_ - 1]*def_sign;
}
} // <-- namespace details

/*template<typename T>
inline bool operator==(const details::Matrix<T>& lhs, const details::Matrix<T>& rhs) {
    if(lhs.nrows() != rhs.nrows() || lhs.ncols() != rhs.ncols()) return false;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const details::Matrix<T>& obj) {
    for(int i = 0, Rows = obj.nrows(); i < Rows; ++i) {
        for(int j = 0, Cols = obj.ncols(); j < Cols; ++j) {
            os << obj[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}