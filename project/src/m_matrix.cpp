#include "m_matrix.h"

MMatrix::MMatrix() : arr_(nullptr), raws_(0), cols_(0), capacity_(0) {}

MMatrix::MMatrix(const size_t& rows, const size_t& cols, const int& val)
        : arr_(nullptr), raws_(rows), cols_(cols), capacity_(rows){
    arr_ = new MVector[raws_];
    for (size_t i = 0; i < raws_; ++i) {
        arr_[i] = MVector(cols_, val);
    }
}

MMatrix::MMatrix(MMatrix &other)
        : arr_(nullptr), raws_(other.raws_), cols_(other.cols_), capacity_(other.capacity_) {
    arr_ = new MVector[other.raws_];
    for (size_t i = 0; i < other.raws_; ++i) {
        arr_[i] = other.arr_[i];
    }
}

MMatrix::MMatrix( const std::initializer_list<std::initializer_list<double>> &list) :
                                                            raws_(list.size()),
                                                            cols_(list.begin()->size()),
                                                            capacity_(list.size()) {
    arr_ = new MVector[raws_];

    // iterate
    size_t i = 0;
    for (auto el : list) {
        arr_[i++] = MVector(el);
    }
}

MMatrix::~MMatrix() { delete[] arr_; }

size_t MMatrix::Rows() const { return raws_; }
size_t MMatrix::Cols() const { return cols_; }
size_t MMatrix::Capacity() const {return  capacity_; }

MVector &MMatrix::operator[](const size_t& idx) {
    if (idx >= raws_) {
        throw std::runtime_error("Index out of range matrix[]");
    }
    return arr_[idx];
}

MVector &MMatrix::operator[](const size_t& idx) const {
    if (idx >= raws_) {
        throw std::runtime_error("Index out of range matrix[]");
    }
    return arr_[idx];
}

void MMatrix::grow()
{
    if (!capacity_)
        capacity_++;
    else
        capacity_ *= 2;
    auto new_arr = new MVector[capacity_];
    std::copy(arr_, &arr_[raws_ - 1] + 1, new_arr);
    delete[] arr_;
    arr_ = new_arr;
}
