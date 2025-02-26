#include <iterator>

namespace details{
template <typename T> struct Matrix_iterator {

    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_value_type = const T;
    using const_pointer = const T*;
    using const_reference = const T&;
    using iterator_category = std::contiguous_iterator_tag;
    using difference_type = std::ptrdiff_t;

    Matrix_iterator(pointer ptr): ptr_(ptr) {}

    const_reference operator*() const {return *ptr_; }
    reference operator*() {return *ptr_; }
    Matrix_iterator& operator++() {++ptr_; return *this; }
    Matrix_iterator& operator--() {--ptr_; return *this; }

    Matrix_iterator& operator++(int) {
        auto old = ptr_;
        ++ptr_;
        return old;
    }

    Matrix_iterator& operator--(int) {
        auto old = ptr_;
        --ptr_;
        return old;
    }

    Matrix_iterator operator+(difference_type dif) { return (ptr_ + dif); }
    Matrix_iterator operator-(difference_type dif) { return (ptr_ - dif); }
    
    Matrix_iterator& operator+=(difference_type dif) {
        ptr_ += dif;
        return *this;
    }

    Matrix_iterator& operator-=(difference_type dif) {
        ptr_ -= dif;
        return *this;
    }

    friend bool operator==(const Matrix_iterator& lhs,  const Matrix_iterator& rhs) { return lhs.ptr_ == rhs.ptr_; }
    friend bool operator!=(const Matrix_iterator& lhs,  const Matrix_iterator& rhs) { return lhs.ptr_ != rhs.ptr_; }
    friend bool operator> (const Matrix_iterator& lhs,  const Matrix_iterator& rhs) { return lhs.ptr_ > rhs.ptr_; }
    friend bool operator< (const Matrix_iterator& lhs,  const Matrix_iterator& rhs) { return lhs.ptr_ < rhs.ptr_; }
    friend bool operator>=(const Matrix_iterator& lhs,  const Matrix_iterator& rhs) { return lhs.ptr_ >= rhs.ptr_; }
    friend bool operator<=(const Matrix_iterator& lhs,  const Matrix_iterator& rhs) { return lhs.ptr_ <= rhs.ptr_; }
    //friend auto operator<=>(const Matrix_iterator& /*unused*/) = default;
    friend difference_type operator-(const Matrix_iterator&lhs, const Matrix_iterator& rhs) { return rhs.ptr_ - lhs.ptr_; }

private:
    pointer ptr_;
};

}; // <-- namespace details