#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <concepts>
#include "Matrix_iterator.hpp"

namespace details {

template <typename T> class Matrix final {

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

private:
        struct ProxyRow {
            pointer row_;

            ProxyRow(pointer ptr): row_(ptr) {}
            reference operator[](int n) { return row_[n]; }
            const_reference operator[](int n) const {return row_[n]; }
        };
    
public:
        ProxyRow operator[](int n) const {
            return ProxyRow{data_[n]};
        }

        Matrix(size_type rows, size_type cols):
            data_(new pointer[rows]),
            rows_(rows),
            cols_(cols) {
                pointer matrix_ptr = new value_type[rows_*cols_]{};
                filling_data_field(matrix_ptr);
            }

        template<typename It>
        Matrix(size_type rows, size_type cols, It beg, It end) :
            data_(new pointer[rows]), rows_(rows), cols_(cols) { //сделать выброс исключеняи
            if(std::distance(beg, end) != rows_*cols_) {
                std::cout << "bad initialization!!!!!" << std::endl;
                exit(0);
            }   
            pointer matrix_ptr = new value_type[rows*cols];
            filling_data_field(matrix_ptr);
            std::copy(beg, end, data_[0]);     
        }

        Matrix(const Matrix &rhs): data_(new pointer[rhs.rows_]), rows_(rhs.rows_), cols_(rhs.cols_) {
            pointer matrix_ptr = new value_type[rows_*cols_];
            filling_data_field(matrix_ptr);
            std::copy(rhs.data_[0], rhs.data_[0] + cols_*rows_, data_[0]);
        }

        Matrix& operator=(const Matrix &rhs) {
            if(this == std::addressof(rhs)) return *this;
            Matrix new_m = rhs;
            swap(new_m);
            return *this;
        }

        Matrix(Matrix&& rhs) noexcept :
            data_(std::exchange(rhs.data_, nullptr)),
            rows_(std::exchange(rhs.rows_, 0)),
            cols_(std::exchange(rhs.cols_, 0)) 
        {}

        Matrix& operator=(Matrix&& rhs) noexcept {
            if(this == std::addressof(rhs)) return *this;
            Matrix m = std::move(rhs);
            swap(m);
            return *this;
        }

        ~Matrix() {
            std::cout<< "apak1" << std::endl;
            if(data_) {
                std::cout<< "apak121" << std::endl;
                delete[] *data_;
            }
            std::cout<< "apak2" << std::endl;
            delete[] data_;
            std::cout<< "apak3" << std::endl;
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

        size_type ncols() const {
            return cols_;
        }

        size_type nrows() const {
            return rows_;
        }

        value_type trace() const {
            value_type trace = 0;
            for(int k = 0; k < cols_; ++k) {
                trace += data_[k][k];
            }
            return trace;
        }

        Matrix& negate() & {
            for(auto &elem : *this) {
                elem *= -1;
            } 
            return *this;
        }

        Matrix& transpose() & {
            if(cols_ == rows_) return square_matrix_transpose();

            Matrix& cur = *this;
            Matrix temp{cols_, rows_};
            for(int i = 0; i < temp.rows_; ++i) {
                for(int j = 0; j < temp.cols_; ++j) {
                    temp[i][j] = cur[j][i];
                }
            }
            cur.swap(temp);
            return *this;
        }

        Matrix& square_matrix_transpose() & {
            auto& temp = *this;
            for(int i = 0; i < rows_ - 1; ++i) {
                for(int j = i + 1; j < cols_; ++j) {
                    std::swap(temp[i][j], temp[j][i]);
                }
            }
            return *this;
        }

private:
        void filling_data_field(pointer ptr) {
            for(int i = 0; i < rows_; ++i) {
                data_[i] = ptr + i*cols_;
            }
        }

        //Find for a row with a non-zero element at position [k][i], k > i. Return 0 if there is none
        int find_needed_row(int i) const {
            int k = i + 1;
            while(k != rows_) {
                /*std::cout << "raws: " << rows_ << std::endl;
                std::cout << "k = " << k << std::endl;
                std::cout << "i = " << i << std::endl;
                std::cout << "as" << data_[k][i] << std::endl;
                std::cout << "sa" << data_[k][i + 1] << std::endl;
                std::cout << "sah" << data_[k][i + 2] << std::endl;*/
                if(data_[k][i] != 0) return k;
                ++k;
            }
            //std::cout << "final" << std::endl;
            return 0;
        }

        //transforms the matrix to the desired form at loop iteration i before running the algorithms, if necessary
        //return 0, if temp[j][k] == 0 for all k from j to rows_, else return 1
        int transform(int j, Matrix& temp, double &det_sign) const {
            //if(temp[j][j] == 0) std::cout << "transform" << std::endl;
            if(temp[j][j] != 0) return 1;
            int num = temp.find_needed_row(j);
            //std::cout << "find_nedeed_row: " << temp.find_needed_row(j) << std::endl;
            if(num != 0) {
                //std::cout << temp;
                std::swap(temp.data_[j], temp.data_[num]);
                det_sign *= -1;
                //std::cout << temp;
                return 1;
            } else return 0;
        }

        //converting first row to zero element at position col_num using second row with Gauss alghoritm
        void Gauss_convert_row(int row_num1, int row_num2, int col_num) {
            //std::cout << "Gauss convert row: " << std::endl;
            //std::cout << "I convert " << row_num1 << " string, starting for " << col_num << " element, using string number " << row_num2 << std::endl;
            if(data_[row_num2][col_num] == 0) std::cout << "I find it" << std::endl;
            value_type coef = data_[row_num1][col_num] / data_[row_num2][col_num];
            for(int i = col_num; i < cols_; ++i) {
                data_[row_num1][i] -= coef*data_[row_num2][i];
            }
        }

        //converting first row to zero element at position col_num using second row with Bareiss alghoritm
        void Bareiss_convert_row(int row_num1, int row_num2, int col_num, value_type& denominator) {
            value_type row1_k = data_[row_num1][col_num];
            value_type row2_k = data_[row_num2][col_num];
            for(int i = col_num; i < cols_; ++i) {
                data_[row_num1][i] = (row2_k*data_[row_num1][i] - row1_k*data_[row_num2][i])/denominator;
            }
        }

        value_type Gauss() const;
        value_type Bareiss() const;
    
public:   
        value_type determinant() const {
            if constexpr (!std::signed_integral<T>) {
                std::cout << "Gauss!" << std::endl;
                Matrix<double> temp = *this;
                std::cout << "norm4_____________________________";
                std::cout << "djsklcsknl1" << temp.Gauss() << "djsklcsknl2";
                return 1;
            } else {
                std::cout << "Bareiss!" << std::endl;
                return Bareiss();
            }
        }

        iterator begin() const { return *data_; }
        iterator end() const { return *data_ + cols_*rows_; }
        const_iterator cbegin() const { return *data_; }
        const_iterator cend() const { return *data_ + cols_*rows_; }

private:
        double_pointer data_;
        size_type rows_; // количество строк
        size_type cols_; // количество столбцов

}; // <-- namespace Matrix

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& obj) {
    for(int i = 0, Rows = obj.nrows(); i < Rows; ++i) {
        for(int j = 0, Cols = obj.ncols(); j < Cols; ++j) {
            os << obj[i][j] << " ";
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

template<typename T>
inline bool operator==(const details::Matrix<T>& lhs, const details::Matrix<T>& rhs) {
    if(lhs.nrows() != rhs.nrows() || lhs.ncols() != rhs.ncols()) return false;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
typename Matrix<T>::value_type Matrix<T>::Gauss() const {
    auto temp = *this;
    double det_sign = 1;
    for(int i = 0; i < temp.rows_ - 1; ++i) {
        //std::cout << "row number: " <<i << std::endl;
        transform(i, temp, det_sign);
        if(temp[i][i] == 0) return 0;
        for(int j = i + 1; j < temp.rows_; ++j) {
            temp.Gauss_convert_row(j, i, i);
            //std::cout << temp;
        }
    }

    std::cout << temp;
    //std::cout << "kk " <<det_sign << std::endl;
    for(int i = 0; i < temp.cols_; ++i) det_sign *= temp[i][i];
    std::cout << det_sign << "ghopap" << std::endl;
    return det_sign;
}

template<typename T>
typename Matrix<T>::value_type Matrix<T>::Bareiss() const {
    auto temp = *this;
    value_type denominator = 1;
    for(int i = 0; i < temp.rows_ - 1; ++i) {
        for(int j = i + 1; j < temp.rows_; ++j) {
            temp.Bareiss_convert_row(j, i, i, denominator);
        }
        denominator = temp[i][i];
        if(!denominator) return 0;
    }

    return temp[temp.rows_ - 1][temp.cols_ - 1];
}
} // <-- namespace details