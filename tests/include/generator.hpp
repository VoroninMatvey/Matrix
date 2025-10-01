#include <cstdlib>
#include <random>
#include <vector>
#include <fstream>
#include <filesystem>

namespace Tests {

        using size_t = std::size_t;

class Matrix final {

private:
        size_t m_size_;
        size_t max_det_;
        int det_;
        std::vector<int> matrix_;

public:
        Matrix(size_t m_size, size_t max_det, int det = {}, std::vector<int> vec = {}) :
            m_size_(m_size), 
            max_det_(max_det),
            det_(det),
            matrix_(vec) {
                matrix_.resize(m_size*m_size);
            }

        int get_elem(size_t n) const noexcept {
            return matrix_[n];
        }

        int determination() const noexcept {
            return det_;
        }
private:
        int random(int min_val, int max_val) const {
            std::random_device rd;
            std::uniform_int_distribution<int> dist(min_val, max_val);
            return dist(rd);
}

        void triangular_matrix() {
            //setting the numbers on the diagonal of the matrix
            int rand_numb = 0, cur_det = 1;

            for(int i = 0; i < m_size_; ++i) {
                rand_numb = random(-10, 10);    
                if(rand_numb == 0) ++rand_numb; 

                if(abs(cur_det * rand_numb) < max_det_) {
                        matrix_[i * (m_size_ + 1)] = rand_numb;
                        cur_det *= rand_numb;
                } else matrix_[i * (m_size_ + 1)] = 1;
            }
            det_ = cur_det;

            //transformation into an upper-triangular matrix
            for(int el_row = 0; el_row < m_size_ - 1; ++el_row) {
                for(int el_col = el_row + 1; el_col < m_size_; ++el_col) {
                    matrix_[el_row * m_size_ + el_col] = random(-10, 10);
                }
            }
        }

        void transf_to_non_triangular() {
            int sign;
            for(int i = 0; i < m_size_; ++i) {
                for(int j = 0; j < m_size_; ++j) {
                    if(i == j) continue;
                    sign = random(0, 1) == 0 ? 1 : -1;
                    adding_strings(j, i, sign);
                }
            }
        }

        //adds coef*row2 to row1
        void adding_strings(int row1, int row2, int coef) noexcept {
            for(int i = 0; i < m_size_; ++i) {
                matrix_[m_size_ * row1 + i] += (coef * matrix_[m_size_ * row2 + i]);
            }
        }
public:
         void create() {
            triangular_matrix();
            transf_to_non_triangular();
        }
}; // <-- class Matrix

class generator final {

public:
        generator(size_t m_size, size_t max_det, size_t  numb_of_tests): 
            M_size_(m_size),
            Max_det_(max_det),
            Numb_of_tests_(numb_of_tests) {}

private:
        size_t M_size_;
        size_t Max_det_;
        size_t Numb_of_tests_;

public:
        void tests_generation() const {
            namespace fs = std::filesystem;
            fs::path tdata_dir = "../../tests/matrix_data";

            if(!fs::exists(tdata_dir)) {
                fs::create_directory(tdata_dir);
                fs::create_directory(tdata_dir/"tests");
                fs::create_directory(tdata_dir/"answers");
            } else {
                fs::remove_all(tdata_dir/"tests");
                fs::remove_all(tdata_dir/"answers");
                fs::create_directory(tdata_dir/"tests");
                fs::create_directory(tdata_dir/"answers");
            }
            
            for(int i = 0; i < Numb_of_tests_; ++i) {
                Matrix temp(M_size_, Max_det_);
                temp.create();

                std::ofstream file_test(tdata_dir/"tests"/("test" + std::to_string(i + 1) + ".txt"));
                std::ofstream file_answ(tdata_dir/"answers"/("answer" + std::to_string(i + 1) + ".txt"));
                file_test << M_size_ << " ";
                for(int j = 0; j < M_size_*M_size_; ++j) {
                    file_test << temp.get_elem(j) << " ";
                }
                file_answ << temp.determination();
            }
        }

};

}  // <-- namespace Tests