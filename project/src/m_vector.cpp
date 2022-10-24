#include "m_vector.h"

#include <cmath>

MVector::MVector() : arr_(nullptr), size_(0), capacity_(0) {}
MVector::MVector(const size_t &size, const double &val)
    : size_(size), capacity_(size) {
    arr_ = new double[capacity_];
    for (size_t i = 0; i < capacity_; i++) {
        arr_[i] = val;
    }
}

MVector::MVector(const MVector &other)
    : size_(other.size_), capacity_(other.capacity_) {
    arr_ = new double[other.capacity_];
    std::copy(other.arr_, &other.arr_[other.size_ - 1] + 1, arr_);
}

MVector &MVector::operator=(const MVector &other) {
    if (arr_)
        delete[] arr_;
    arr_ = new double[other.capacity_];
    capacity_ = other.capacity_;
    size_ = other.size_;
    std::copy(other.arr_, &other.arr_[other.size_ - 1] + 1, arr_);
    return *this;
}

MVector::MVector(const std::initializer_list<double> &list)
    : size_(list.size()), capacity_(list.size()) {
    arr_ = new double[capacity_];

    // iterate
    size_t i = 0;
    for (auto el : list) {
        arr_[i++] = el;
    }
}

double const &MVector::operator[](const size_t &idx) const {
    if (idx >= size_) {
        throw std::runtime_error("Index out of range vector[]");
    }
    return arr_[idx];
}

double &MVector::operator[](const size_t &idx) {
    if (idx >= size_) {
        throw std::runtime_error("Index out of range vector[]");
    }
    return arr_[idx];
}

void MVector::PushBack(const double &value) {
    if (size_ == capacity_) {
        grow();
    }
    arr_[size_++] = value;
}

void MVector::Print() const {
    for (size_t i = 0; i < size_; i++) {
        std::cout << arr_[i] << " ";
    }
    std::cout << std::endl;
}
void MVector::PopBack() {
    if (!size_) {
        throw std::runtime_error("Empty vector PopBack ERROR");
    }
    --size_;
}

size_t MVector::Size() const { return size_; }
size_t MVector::Capacity() const { return capacity_; }

double MVector::Front() const {
    if (!size_) {
        throw std::runtime_error("Empty vector ERROR method Front");
    }
    return arr_[0];
}

double MVector::Back() const {
    if (!size_) {
        throw std::runtime_error("Empty vector ERROR method Back");
    }
    return arr_[size_ - 1];
}

MVector::~MVector() { delete[] arr_; }

void MVector::grow() {
    if (!capacity_)
        capacity_++;
    else
        capacity_ *= 2;
    auto new_arr = new double[capacity_];
    std::copy(arr_, &arr_[size_ - 1] + 1, new_arr);
    delete[] arr_;
    arr_ = new_arr;
}

// 3
MVector operator+(const MVector &left, const MVector &right) {
    if (left.Size() != right.Size()) {
        throw std::runtime_error("Different sizes of vectors operator+");
    }
    auto sum = MVector(left.Size());
    for (size_t i = 0; i < left.Size(); ++i) {
        sum[i] = left[i] + right[i];
    }
    return sum;
}

MVector operator-(const MVector &left, const MVector &right) {
    if (left.Size() != right.Size()) {
        throw std::runtime_error("Different sizes of vectors operator-");
    }
    auto sub = MVector(left.Size());
    for (size_t i = 0; i < left.Size(); ++i) {
        sub[i] = left[i] - right[i];
    }
    return sub;
}

MVector operator*(const MVector &left, const MVector &right) {
    if (left.Size() != right.Size()) {
        throw std::runtime_error("Different sizes of vectors operator*");
    }
    auto mul = MVector(left.Size());
    for (size_t i = 0; i < left.Size(); ++i) {
        mul[i] = left[i] * right[i];
    }
    return mul;
}

MVector &operator-=(MVector &left, const MVector &right) {
    if (left.Size() != right.Size()) {
        throw std::runtime_error("Different sizes of vectors operator+=");
    }
    for (size_t i = 0; i < left.Size(); ++i) {
        left[i] -= right[i];
    }
    return left;
}
MVector &operator+=(MVector &left, const MVector &right) {
    if (left.Size() != right.Size()) {
        throw std::runtime_error("Different sizes of vectors operator-=");
    }
    for (size_t i = 0; i < left.Size(); ++i) {
        left[i] += right[i];
    }
    return left;
}
MVector &operator*=(MVector &left, const MVector &right) {
    if (left.Size() != right.Size()) {
        throw std::runtime_error("Different sizes of vectors operator*=");
    }
    for (size_t i = 0; i < left.Size(); ++i) {
        left[i] *= right[i];
    }
    return left;
}

// 5
void MVector::AddValue(const double &val) {
    for (size_t i = 0; i < size_; i++) {
        arr_[i] += val;
    }
}
void MVector::SubValue(const double &val) {
    for (size_t i = 0; i < size_; i++) {
        arr_[i] -= val;
    }
}
void MVector::MulValue(const double &val) {
    for (size_t i = 0; i < size_; i++) {
        arr_[i] *= val;
    }
}

MVector operator+(const MVector &left, const double &right) {
    auto sum = MVector(left.Size());
    for (size_t i = 0; i < left.Size(); ++i) {
        sum[i] = left[i] + right;
    }
    return sum;
}

MVector operator-(const MVector &left, const double &right) {
    auto sub = MVector(left.Size());
    for (size_t i = 0; i < left.Size(); ++i) {
        sub[i] = left[i] + right;
    }
    return sub;
}

MVector operator*(const MVector &left, const double &right) {
    auto mul = MVector(left.Size());
    for (size_t i = 0; i < left.Size(); ++i) {
        mul[i] = left[i] * right;
    }
    return mul;
}

MVector &operator+=(MVector &left, const double &right) {
    left.AddValue(right);
    return left;
}
MVector &operator-=(MVector &left, const double &right) {
    left.SubValue(right);
    return left;
}

MVector &operator*=(MVector &left, const double &right) {
    left.MulValue(right);
    return left;
}

MVector MVector::operator()(const size_t &begin, const size_t &end,
                            const int &step) const {
    MVector res;
    if (begin >= size_ || end > size_) {
        throw std::runtime_error("Slice incorrect arguments");
    }
    if (step > 0) {
        for (size_t i = begin; i < end; i += step) {
            res.PushBack(arr_[i]);
        }
    } else {
        for (size_t i = end - 1; i < begin; i += step) {
            res.PushBack(arr_[i]);
        }
    }
    return res;
}

std::ostream &operator<<(std::ostream &os, const MVector &vec) {
    for (size_t i = 0; i < vec.Size(); i++) {
        os << vec[i] << " ";
    }
    os << std::endl;
    return os;
}
