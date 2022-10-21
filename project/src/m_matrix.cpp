#include "m_matrix.h"

MMatrix::MMatrix() : arr_(nullptr), rows_(0), cols_(0), capacity_(0) {}

MMatrix::MMatrix(const size_t& rows, const size_t& cols, const int& val)
        : arr_(nullptr), rows_(rows), cols_(cols), capacity_(rows){
    arr_ = new MVector[rows_];
    for (size_t i = 0; i < rows_; ++i) {
        arr_[i] = MVector(cols_, val);
    }
}

MMatrix::MMatrix(MMatrix &other)
        : arr_(nullptr), rows_(other.rows_), cols_(other.cols_), capacity_(other.capacity_) {
    arr_ = new MVector[other.rows_];
    for (size_t i = 0; i < other.rows_; ++i) {
        arr_[i] = other.arr_[i];
    }
}

MMatrix::MMatrix(MVector *vectors, const size_t& size) :
                                    arr_(vectors), rows_(size),
                                    cols_(vectors[0].Size()), capacity_(rows_){}

// vector - row by default
MMatrix::MMatrix(const MVector &vec, Orientation orient){
    if (orient == Orientation::Row){
        rows_ = capacity_ = 1;
        cols_ = vec.Size();
        arr_ = new MVector[rows_];
        arr_[0] = MVector({1, 2, 4, 5});
//        arr_[0] = vec;
//        for (size_t i = 0; i < rows_; i++){
//            arr_[i] = new
////            arr_[i] = *(new MVector(cols_));
////            arr_[0][i] = vec[i];
//        }
    } else {
        cols_ = 1;
        rows_ = capacity_ = vec.Size();
        arr_ = new MVector[rows_];
        for (size_t i = 0; i < rows_; i++){
            arr_[i] = *(new MVector(cols_));
            arr_[i][0] = vec[i];
        }
    }
}

MMatrix::MMatrix( const std::initializer_list<std::initializer_list<double>> &list) :
                                                            rows_(list.size()),
                                                            cols_(list.begin()->size()),
                                                            capacity_(list.size()) {
    arr_ = new MVector[rows_];

    // iterate
    size_t i = 0;
    for (auto el : list) {
        arr_[i++] = MVector(el);
    }
}

MMatrix::~MMatrix() { delete[] arr_; }

size_t MMatrix::Rows() const { return rows_; }
size_t MMatrix::Cols() const { return cols_; }
size_t MMatrix::Capacity() const {return  capacity_; }

MVector &MMatrix::operator[](const size_t& idx) {
    if (idx >= rows_) {
        throw std::runtime_error("Index out of range matrix[]");
    }
    return arr_[idx];
}

MVector &MMatrix::operator[](const size_t& idx) const {
    if (idx >= rows_) {
        throw std::runtime_error("Index out of range matrix[]");
    }
    return arr_[idx];
}

MVector MMatrix::GetRow(const size_t& idx) const {
    if (idx >= rows_) {
        throw std::runtime_error("Index out of range : method GetRow");
    }
    return MVector(arr_[idx]);
}
MVector MMatrix::GetCol(const size_t& idx) const {
    if (idx >= arr_[0].Size()) {
        throw std::runtime_error("Index out of range : method GetCol");
    }
    MVector col(rows_);
    for (size_t i = 0; i < rows_; ++i) {
        col[i] = arr_[i][idx];
    }
    return col;
}

MVector MMatrix::GetDiag() const {
    size_t size = std::min(rows_, cols_);
    MVector diag(size);
    for (size_t i = 0; i < size; ++i) {
        diag[i] = arr_[i][i];
    }
    return diag;
}


void MMatrix::grow()
{
    if (!capacity_)
        capacity_++;
    else
        capacity_ *= 2;
    auto new_arr = new MVector[capacity_];
    std::copy(arr_, &arr_[rows_ - 1] + 1, new_arr);
    delete[] arr_;
    arr_ = new_arr;
}
