#include "m_matrix.h"

MMatrix::MMatrix() : arr_(nullptr), rows_(0), cols_(0), capacity_(0) {}

MMatrix::MMatrix(const size_t& rows, const size_t& cols, const int& val)
        : rows_(rows), cols_(cols), capacity_(rows){
    arr_ = new MVector[rows_];
    for (size_t i = 0; i < rows_; ++i) {
        arr_[i] = MVector(cols_, val);
    }
}

MMatrix::MMatrix(MMatrix &other)
        : rows_(other.rows_), cols_(other.cols_), capacity_(other.capacity_) {
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
        arr_[0] = vec;
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

void MMatrix::Print() const {
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            std::cout << arr_[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
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
// 3
MMatrix operator+(const MMatrix &left, const MMatrix &right){
    if ((left.Rows() != right.Rows()) || (left.Cols() != right.Cols())) {
        throw std::runtime_error("Different sizes of matrixes operator+");
    }
    MMatrix sum(left.Rows(), left.Cols());
    for (size_t i = 0; i < left.Rows(); ++i) {
        for (size_t j = 0; j < left.Cols(); ++j) {
            sum[i][j] = left[i][j] + right[i][j];
        }
    }
    return sum;
}

MMatrix operator-(const MMatrix &left, const MMatrix &right){
    if ((left.Rows() != right.Rows()) || (left.Cols() != right.Cols())) {
        throw std::runtime_error("Different sizes of matrixes operator+");
    }
    MMatrix sub(left.Rows(), left.Cols());
    for (size_t i = 0; i < left.Rows(); ++i) {
        for (size_t j = 0; j < left.Cols(); ++j) {
            sub[i][j] = left[i][j] - right[i][j];
        }
    }
    return sub;
}
// multiply element to element  -- NOT standart matrix multiplication
// standart mul is in MatMul method
MMatrix operator*(const MMatrix &left, const MMatrix &right){
    if ((left.Rows() != right.Rows()) || (left.Cols() != right.Cols())) {
        throw std::runtime_error("Different sizes of matrixes operator+");
    }
    MMatrix mul(left.Rows(), left.Cols());
    for (size_t i = 0; i < left.Rows(); ++i) {
        for (size_t j = 0; j < left.Cols(); ++j) {
            mul[i][j] = left[i][j] * right[i][j];
        }
    }
    return mul;
}

// 4
MMatrix operator*(const double &left, const MMatrix &right){
    MMatrix mul(right.Rows(), right.Cols());
    for (size_t i = 0; i < right.Rows(); ++i) {
        for (size_t j = 0; j < right.Cols(); ++j) {
            mul[i][j] *= left;
        }
    }
    return mul;
}

MVector operator*(const MVector &left, const MMatrix &right){
    if ((left.Size() != right.Rows())) {
        throw std::runtime_error("Unsuitable sizes of vector and matrix operator*");
    }
    MVector mul(right.Rows());
    for (size_t i = 0; i < right.Rows(); ++i)
    {
        // sum of raw * col elements
        double sum = 0;
        for (size_t j = 0; j < right.Cols(); ++j) {
            sum += right[i][j] * left[j];
        }
        mul[i] = sum;
    }
    return mul;
}
MVector operator*(const MMatrix &left, const MVector &right){
    if ((left.Cols() != right.Size())) {
        throw std::runtime_error("Unsuitable sizes of matrix and vector operator*");
    }
    MVector mul(left.Cols());
    for (size_t i = 0; i < left.Rows(); ++i)
    {
        // sum of raw * col elements
        double sum = 0;
        for (size_t j = 0; j < left.Cols(); ++j) {
            sum += left[i][j] * right[j];
        }
        mul[i] = sum;
    }
    return mul;
}
MMatrix MatMul(const MMatrix &left, const MMatrix &right){
    if ((left.Cols() != right.Rows())) {
        throw std::runtime_error("Unsuitable sizes of matrix and matrix operator*");
    }
    MMatrix mul = MMatrix(left.Rows(), right.Cols());
    for (size_t i = 0; i < left.Rows(); ++i) {
        for (size_t j = 0; j < right.Cols(); ++j) {
            // sum of raw * col elements
            double sum = 0;
            for (size_t k = 0; k < right.Rows(); ++k) {
                sum += left[i][k] * right[k][j];
            }
            mul[i][j] = sum;
        }
    }
    return mul;
}

// 5
void MMatrix::AddValue(const double & val){
    for(size_t i = 0; i < rows_; i++){
        for (size_t j = 0; j < cols_; j++){
            arr_[i][j]+=val;
        }
    }
}
void MMatrix::SubValue(const double &val) {
    for(size_t i = 0; i < rows_; i++){
        for (size_t j = 0; j < cols_; j++){
            arr_[i][j]-=val;
        }
    }
}
// With choose opportunity rows/cols;
void MMatrix::AddVector(const MVector &v, size_t idx, Orientation orient) {

}
void MMatrix::SubVector(const MVector &v, size_t idx, Orientation orient){

}

MMatrix operator+(const MMatrix &left, const double &right){

}
MMatrix operator-(const MMatrix &left, const double &right){

}