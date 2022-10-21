#include "m_vector.h"

MVector::MVector() :arr_(nullptr), size_(0), capacity_(0) { }
MVector::MVector(const size_t& size, const double& val) : size_(size), capacity_(size) {
    arr_ = new double[capacity_];
    for (size_t i = 0; i < capacity_; i++){
        arr_[i] = val;
    }
}

MVector::MVector(MVector const &other) :
                                        size_(other.size_),
                                        capacity_(other.capacity_){
    arr_ = new double[other.capacity_];
    std::copy(other.arr_, &other.arr_[other.size_ - 1] + 1, arr_);
}

MVector& MVector::operator=(const MVector& other){
    delete[] arr_;
    arr_ = new double[other.capacity_];
    capacity_ = other.capacity_;
    size_ = other.size_;
    std::copy(other.arr_, &other.arr_[other.size_ - 1] + 1, arr_);
    return *this;
}

MVector::MVector(const std::initializer_list<double>& list):
                                                        size_(list.size()),
                                                        capacity_(list.size()){
    arr_ = new double[capacity_];

    // iterate
    size_t i = 0;
    for (auto  el : list) {
        arr_[i++] = el;
    }
}

double const &MVector::operator[](const size_t& idx) const {
    if (idx >= size_) {
        throw std::runtime_error("Index out of range vector[]");
    }
    return arr_[idx];
}

double &MVector::operator[](const size_t& idx) {
    if (idx >= size_) {
        throw std::runtime_error("Index out of range vector[]");
    }
    return arr_[idx];
}

void MVector::PushBack(const double& value) {
    if (size_ == capacity_) {
        grow();
    }
    arr_[size_++] = value;
}

void MVector::Print() const {
    for (size_t i = 0; i < size_; i++){
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

MVector::~MVector() {
    delete[] arr_;
}

void MVector::grow() {
    if (!capacity_)
        capacity_++;
    else
        capacity_ *= 2;
    auto new_arr = new double [capacity_];
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

// 5
void MVector::AddValue(const double &val){
    for (size_t i = 0; i < size_; i++){
        arr_[i] += val;
    }
}
void MVector::SubValue(const double &val){
    for (size_t i = 0; i < size_; i++){
        arr_[i] += val;
    }
}

MVector operator+(const MVector &left, const double &right){
    auto sum = MVector(left.Size());
    for (size_t i = 0; i < left.Size(); ++i) {
        sum[i] = left[i] + right;
    }
    return sum;
}

MVector operator-(const MVector &left, const double &right){
    auto sub = MVector(left.Size());
    for (size_t i = 0; i < left.Size(); ++i) {
        sub[i] = left[i] + right;
    }
    return sub;
}

