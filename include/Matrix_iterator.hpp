#include <iterator>

namespace details{
template <typename T> struct Matrix_iterator final {

    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_value_type = const T;
    using const_pointer = const T*;
    using const_reference = const T&;
    using iterator_category = std::contiguous_iterator_tag;
    using difference_type = std::ptrdiff_t;

    Matrix_iterator(pointer ptr) noexcept : ptr_(ptr) {}

    const_reference operator*() const noexcept {return *ptr_; }
    reference operator*() noexcept {return *ptr_; }
    const_pointer operator->() const noexcept {return ptr_; }
    pointer operator->() noexcept {return ptr_; }
    Matrix_iterator& operator++() noexcept {++ptr_; return *this; }
    Matrix_iterator& operator--() noexcept {--ptr_; return *this; }

    Matrix_iterator operator++(int) noexcept {
        auto old = ptr_;
        ++ptr_;
        return old;
    }

    Matrix_iterator operator--(int) noexcept {
        auto old = ptr_;
        --ptr_;
        return old;
    }

    Matrix_iterator operator+(difference_type dif) const noexcept { return (ptr_ + dif); }
    friend Matrix_iterator operator+(difference_type dif, const Matrix_iterator& it) noexcept {
        return it + dif;  
    }

    Matrix_iterator operator-(difference_type dif) const noexcept { return (ptr_ - dif); }
    
    Matrix_iterator& operator+=(difference_type dif) noexcept {
        ptr_ += dif;
        return *this;
    }

    Matrix_iterator& operator-=(difference_type dif) noexcept {
        ptr_ -= dif;
        return *this;
    }

    auto operator<=>(const Matrix_iterator& rhs) const noexcept = default;
    difference_type operator-(const Matrix_iterator& rhs) const noexcept { return ptr_ - rhs.ptr_; }

private:
    pointer ptr_;
};
}; // <-- namespace details