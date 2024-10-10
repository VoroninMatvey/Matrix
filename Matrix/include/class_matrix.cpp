#include <vector>
#include <iostream>

namespace details {
template <typename T> class Matrix {

        using size_type = std::size_t;
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using double_pointer = T**;
        using const_double_pointer = const T**;
        using It = typename std::vector<T>::iterator;

        double_pointer data_;
        size_type rows_; // количество строк
        size_type cols_; // количество столбцов

public:
        Matrix(size_type rows, size_type cols) : 
            rows_(rows),
            cols_(cols) {
                data_ = new pointer[rows_];
                std::size_t i = 0;
                while(i < rows_) {
                    data_[i] = new value_type[cols_]{};
                    ++i;
                }
            }

        Matrix(size_type rows, size_type cols, It beg, It end) : 
            rows_(rows),
            cols_(cols),
            data_(new pointer[rows_]) {

                //потом надо будет сделать выброс исключения
                if(std::distance(beg, end) == rows_*cols_) {
                    It it = beg;
                    std::size_t i = 0;
                    while(i < rows_) {
                        data_[i] = new value_type[cols_];
                        std::size_t j;
                        for(j = 0; j < cols_; ++j) {
                            data_[i][j] = *it;
                            ++it;
                        }
                        ++i;
                    }
                } else {
                    std::cout << "bad initialization!!!!!" << std::endl;
                    exit(0);
                } 
            }

        Matrix(const Matrix &rhs) {
            rows_ = rhs.rows_;
            cols_ = rhs.cols_;
            data_ = new pointer[rows_];

            std::size_t i = 0;
            while(i < rows_) {
                data_[i] = new value_type[cols_];
                std::size_t j;
                for(j = 0; j < cols_; ++j) {
                    data_[i][j] = rhs.data_[i][j];
                }
                ++i;
            }
        }

        Matrix& operator=(const Matrix &rhs) {
            if(this == &rhs) return *this;
            Matrix new_m = rhs;
            swap(new_m);
            return *this;    
        }

        ~Matrix() {
            std::size_t i = 0;
            while(i < rows_) {
                std::cout << "before " << i << " deletes" << std::endl; 
                delete[] data_[i];
                std::cout << "after " << i << "deletes" << std::endl;
                ++i; 
            }
           // std::cout << "before last deletes" << std::endl;
            delete[] data_;
            //std::cout << "after last deletes" << std::endl;
        }

        void print_Matrix() {
            std::size_t i = 0;
            std::size_t j = 0;

            while(i < rows_) {
                for(j = 0; j < cols_; ++j) {
                    std::cout << data_[i][j] << " ";
                }
                std::cout << std::endl;
                ++i;
            }
        }

        void swap(Matrix& m) {
            std::swap(cols_, m.cols_);
            std::swap(rows_, m.rows_);
            std::swap(data_, m.data_);
        }

}; // <-- namespace Matrix
} // <-- namespace details

int main() { 

    details::Matrix<int> s{4, 6};
    s.print_Matrix();
    std::cout << std::endl;

    std::vector<int> vec;
    for(int i = 0; i < 100; ++i) {
        vec.push_back(i);
    }
    details::Matrix<int> p{5, 20, vec.begin(), vec.end()};
    p.print_Matrix();
    std::cout << std::endl;

    details::Matrix<int> q = p;
    p.print_Matrix();

    q = s;
    q.print_Matrix();

}