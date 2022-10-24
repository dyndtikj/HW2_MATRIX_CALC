#include "m_matrix.h"

#include <algorithm>

MMatrix::MMatrix() : arr_(nullptr), rows_(0), cols_(0), capacity_(0) {}

MMatrix::MMatrix(const size_t &rows, const size_t &cols, const int &val)
    : rows_(rows), cols_(cols), capacity_(rows) {
    arr_ = new MVector[rows_];
    for (size_t i = 0; i < rows_; i++) {
        arr_[i] = MVector(cols_, val);
    }
}

MMatrix::MMatrix(MMatrix &other)
    : rows_(other.rows_), cols_(other.cols_), capacity_(other.capacity_) {
    //    delete []arr_;
    arr_ = new MVector[other.rows_];
    for (size_t i = 0; i < other.rows_; i++) {
        arr_[i] = other.arr_[i];
    }
}

MMatrix &MMatrix::operator=(const MMatrix &other) {
    delete[] arr_;
    arr_ = new MVector[other.rows_];
    capacity_ = other.capacity_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    std::copy(other.arr_, &other.arr_[other.rows_ - 1] + 1, arr_);
    return *this;
}

MMatrix::MMatrix(MVector *vectors, const size_t &size)
    : arr_(vectors), rows_(size), cols_(vectors[0].Size()), capacity_(rows_) {
    for (size_t i = 0; i < size; i++){
        if( vectors[i].Size() != cols_){
            throw std::runtime_error("Cant create matrix from vectors different lengh");
        }
    }
}

// vector - row by default
MMatrix::MMatrix(const MVector &vec, Orientation orient) {
    if (orient == Orientation::Row) {
        rows_ = capacity_ = 1;
        cols_ = vec.Size();
        arr_ = new MVector[rows_];
        arr_[0] = vec;
    } else {
        cols_ = 1;
        rows_ = capacity_ = vec.Size();
        arr_ = new MVector[rows_];
        for (size_t i = 0; i < rows_; i++) {
            arr_[i] = *(new MVector(cols_));
            arr_[i][0] = vec[i];
        }
    }
}

MMatrix::MMatrix(
    const std::initializer_list<std::initializer_list<double>> &list)
    : rows_(list.size()), cols_(list.begin()->size()), capacity_(list.size()) {
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
size_t MMatrix::Capacity() const { return capacity_; }

void MMatrix::grow() {
    if (!capacity_)
        capacity_++;
    else
        capacity_ *= 2;
    auto new_arr = new MVector[capacity_];
    std::copy(arr_, &arr_[rows_ - 1] + 1, new_arr);
    delete[] arr_;
    arr_ = new_arr;
}

void MMatrix::PushBackR(const MVector &row) {
    if (rows_ > 0 && row.Size() != cols_) {
        throw std::runtime_error("Push back incorrect size vector as row");
    }
    if (!rows_) {
        cols_ = row.Size();
    }
    if (rows_ == capacity_) {
        grow();
    }
    arr_[rows_++] = MVector(row);
}
void MMatrix::PushBackC(const MVector &col) {
    if (rows_ > 0 && col.Size() != rows_) {
        throw std::runtime_error("Push back incorrect size vector as column");
    }
    if (!rows_) {
        rows_ = col.Size();
        capacity_ = rows_;
        arr_ = new MVector[rows_];
    }
    for (size_t i = 0; i < col.Size(); i++) {
        arr_[i].PushBack(col[i]);
    }
    cols_++;
}

MVector &MMatrix::operator[](const size_t &idx) {
    if (idx >= rows_) {
        throw std::runtime_error("Index out of range matrix[]");
    }
    return arr_[idx];
}

MVector &MMatrix::operator[](const size_t &idx) const {
    if (idx >= rows_) {
        throw std::runtime_error("Index out of range matrix[]");
    }
    return arr_[idx];
}

MVector MMatrix::GetRow(const size_t &idx) const {
    if (idx >= rows_) {
        throw std::runtime_error("Index out of range : method GetRow");
    }
    return MVector(arr_[idx]);
}
MVector MMatrix::GetCol(const size_t &idx) const {
    if (idx >= arr_[0].Size()) {
        throw std::runtime_error("Index out of range : method GetCol");
    }
    MVector col(rows_);
    for (size_t i = 0; i < rows_; i++) {
        col[i] = arr_[i][idx];
    }
    return col;
}

MVector MMatrix::GetDiag() const {
    size_t size = std::min(rows_, cols_);
    MVector diag(size);
    for (size_t i = 0; i < size; i++) {
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

// 3
MMatrix operator+(const MMatrix &left, const MMatrix &right) {
    if ((left.Rows() != right.Rows()) || (left.Cols() != right.Cols())) {
        throw std::runtime_error("Different sizes of matrixes operator+");
    }
    MMatrix sum(left.Rows(), left.Cols());
    for (size_t i = 0; i < left.Rows(); i++) {
        for (size_t j = 0; j < left.Cols(); j++) {
            sum[i][j] = left[i][j] + right[i][j];
        }
    }
    return sum;
}

MMatrix operator-(const MMatrix &left, const MMatrix &right) {
    if ((left.Rows() != right.Rows()) || (left.Cols() != right.Cols())) {
        throw std::runtime_error("Different sizes of matrixes operator+");
    }
    MMatrix sub(left.Rows(), left.Cols());
    for (size_t i = 0; i < left.Rows(); i++) {
        for (size_t j = 0; j < left.Cols(); j++) {
            sub[i][j] = left[i][j] - right[i][j];
        }
    }
    return sub;
}
// multiply element to element  -- NOT standart matrix multiplication
// standart mul is in MatMul method
MMatrix operator*(const MMatrix &left, const MMatrix &right) {
    if ((left.Rows() != right.Rows()) || (left.Cols() != right.Cols())) {
        throw std::runtime_error("Different sizes of matrixes operator+");
    }
    MMatrix mul(left.Rows(), left.Cols());
    for (size_t i = 0; i < left.Rows(); i++) {
        for (size_t j = 0; j < left.Cols(); j++) {
            mul[i][j] = left[i][j] * right[i][j];
        }
    }
    return mul;
}
MMatrix &operator+=(MMatrix &left, const MMatrix &right) {
    if ((left.Rows() != right.Rows()) || (left.Cols() != right.Cols())) {
        throw std::runtime_error("Different sizes of matrixes operator+");
    }
    for (size_t i = 0; i < left.Rows(); i++) {
        for (size_t j = 0; j < left.Cols(); j++) {
            left[i][j] += right[i][j];
        }
    }
    return left;
}

MMatrix &operator-=(MMatrix &left, const MMatrix &right) {
    if ((left.Rows() != right.Rows()) || (left.Cols() != right.Cols())) {
        throw std::runtime_error("Different sizes of matrixes operator-");
    }
    for (size_t i = 0; i < left.Rows(); i++) {
        for (size_t j = 0; j < left.Cols(); j++) {
            left[i][j] -= right[i][j];
        }
    }
    return left;
}

MMatrix &operator*=(MMatrix &left, const MMatrix &right) {
    if ((left.Rows() != right.Rows()) || (left.Cols() != right.Cols())) {
        throw std::runtime_error("Different sizes of matrixes operator*");
    }
    for (size_t i = 0; i < left.Rows(); i++) {
        for (size_t j = 0; j < left.Cols(); j++) {
            left[i][j] *= right[i][j];
        }
    }
    return left;
}

// 4
MMatrix operator*(const double &left, const MMatrix &right) {
    MMatrix mul(right.Rows(), right.Cols());
    for (size_t i = 0; i < right.Rows(); i++) {
        for (size_t j = 0; j < right.Cols(); j++) {
            mul[i][j] = left * right[i][j];
        }
    }
    return mul;
}

MVector operator*(const MMatrix &left, const MVector &right) {
    if ((left.Cols() != right.Size())) {
        throw std::runtime_error(
            "Unsuitable sizes of matrix and vector operator*");
    }
    MVector mul(left.Cols());
    for (size_t i = 0; i < left.Rows(); i++) {
        // sum of raw * col elements
        double sum = 0;
        for (size_t j = 0; j < left.Cols(); j++) {
            sum += left[i][j] * right[j];
        }
        mul[i] = sum;
    }
    return mul;
}

// Vector = [1xN]
MVector operator*(const MVector &left, const MMatrix &right) {
    if (left.Size() != right.Rows()) {
        throw std::runtime_error("Different sizes vector operator*= matrix");
    }
    MVector mul(right.Cols());

    for (size_t i = 0; i < right.Cols(); i++) {
        double sum_of_muls = 0;
        for (size_t j = 0; j < left.Size(); j++) {
            sum_of_muls += left[j] * (right.GetRow(j))[i];
        }
        mul[i] = sum_of_muls;
    }
    return mul;
}

MMatrix MatMul(const MMatrix &left, const MMatrix &right) {
    if ((left.Cols() != right.Rows())) {
        throw std::runtime_error(
            "Unsuitable sizes of matrix and matrix operator*");
    }
    MMatrix mul = MMatrix(left.Rows(), right.Cols());
    for (size_t i = 0; i < left.Rows(); i++) {
        for (size_t j = 0; j < right.Cols(); j++) {
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

MVector &operator*=(MVector &left, MMatrix &right) {
    if (left.Size() != right.Rows()) {
        throw std::runtime_error("Different sizes vector operator*= matrix");
    }
    MVector mul(right.Cols());
    for (size_t i = 0; i < right.Cols(); i++) {
        double sum_of_muls = 0;
        for (size_t j = 0; j < left.Size(); j++) {
            sum_of_muls += left[j] * (right.GetRow(j))[i];
        }
        mul[i] = sum_of_muls;
    }
    left = mul;
    return left;
}

// 5
void MMatrix::AddValue(const double &val) {
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            arr_[i][j] += val;
        }
    }
}
void MMatrix::SubValue(const double &val) {
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            arr_[i][j] -= val;
        }
    }
}
// With choose opportunity rows/cols;
void MMatrix::AddVector(const MVector &v, size_t idx, Orientation orient) {
    if (orient == Orientation::Row) {
        if ((v.Size() != cols_)) {
            throw std::runtime_error(
                "Unsuitable sizes of matrix and matrix operator*");
        }
        for (size_t i = 0; i < v.Size(); i++) {
            arr_[idx][i] += v[i];
        }
    } else {
        if ((v.Size() != rows_)) {
            throw std::runtime_error(
                "Unsuitable sizes of matrix and matrix operator*");
        }
        for (size_t i = 0; i < v.Size(); i++) {
            arr_[i][idx] += v[i];
        }
    }
}
void MMatrix::SubVector(const MVector &v, size_t idx, Orientation orient) {
    if (orient == Orientation::Row) {
        if ((v.Size() != cols_)) {
            throw std::runtime_error(
                "Unsuitable sizes of matrix and matrix operator*");
        }
        for (size_t i = 0; i < v.Size(); i++) {
            arr_[idx][i] -= v[i];
        }
    } else {
        if ((v.Size() != rows_)) {
            throw std::runtime_error(
                "Unsuitable sizes of matrix and matrix operator*");
        }
        for (size_t i = 0; i < v.Size(); i++) {
            arr_[i][idx] -= v[i];
        }
    }
}

MMatrix operator+(const MMatrix &left, const double &right) {
    MMatrix sum(left.Rows(), left.Cols());
    for (size_t i = 0; i < left.Rows(); i++) {
        for (size_t j = 0; j < left.Cols(); j++) {
            sum[i][j] = left[i][j] + right;
        }
    }
    return sum;
}
MMatrix operator-(const MMatrix &left, const double &right) {
    MMatrix sub(left.Rows(), left.Cols());
    for (size_t i = 0; i < left.Rows(); i++) {
        for (size_t j = 0; j < left.Cols(); j++) {
            sub[i][j] = left[i][j] - right;
        }
    }
    return sub;
}

void MMatrix::MulValue(const double &val) {
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            arr_[i][j] *= val;
        }
    }
}

MMatrix &operator+=(MMatrix &left, const double &right) {
    left.AddValue(right);
    return left;
}
MMatrix &operator-=(MMatrix &left, const double &right) {
    left.SubValue(right);
    return left;
}

// 6
MMatrix MMatrix::GetTransponsed() const {
    MMatrix res(cols_, rows_);
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            res[j][i] = arr_[i][j];
        }
    }
    return res;
}

double MMatrix::GetMinor(const size_t &row, const size_t &col) const {
    MMatrix del_i_j = DelRowCol(row, col);
    double det = del_i_j.GetDet();
    return det;
}

MMatrix MMatrix::GetAdded() const {
    MMatrix added(rows_, cols_);
    int sign = 1;
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            added[i][j] = sign * GetMinor(i, j);
            sign *= -1;
        }
    }
    return added;
}

MMatrix MMatrix::GetIverted() const {
    double det = GetDet();
    if (det == 0) {
        return MMatrix{};
    }
    MMatrix invert = (1 / det) * GetAdded().GetTransponsed();
    return invert;
}

MMatrix MMatrix::DelRowCol(const size_t &row, const size_t &col) const {
    if (!rows_ || !cols_) {
        throw std::runtime_error(
            "Cant delete Row/ Column from empty matrix method DelColRow()");
    }
    if (row >= rows_ || col >= cols_) {
        throw std::runtime_error("Index out of range method DelColRow()");
    }

    MMatrix res(rows_ - 1, cols_ - 1);
    size_t res_idx_r = 0, res_idx_c = 0;
    for (size_t i = 0; i < rows_; i++, res_idx_c = 0) {
        if (i == row) continue;
        for (size_t j = 0; j < cols_; j++) {
            if (j == col) continue;
            res[res_idx_r][res_idx_c++] = arr_[i][j];
        }
        res_idx_r++;
    }
    return res;
}

// 7
double MMatrix::GetDet() const {
    if (cols_ != rows_) {
        throw std::runtime_error("Determinant requires NxN matrixes");
    }
    if (rows_ == 2) {
        return arr_[0][0] * arr_[1][1] - arr_[0][1] * arr_[1][0];
    }
    int sign = 1;
    double det = 0;
    for (size_t i = 0; i < cols_; i++) {
        det += sign * arr_[0][i] * GetMinor(0, i);
        sign *= -1;
    }
    return det;
}
MMatrix MMatrix::operator()(const size_t &begin, const size_t &end,
                            const int &step, Orientation orient) const {
    if (orient == Orientation::Row) {
        MMatrix res;
        if (begin >= rows_ || end > rows_) {
            throw std::runtime_error("Slice incorrect arguments");
        }
        if (step > 0) {
            for (size_t i = begin; i < end; i += step) {
                res.PushBackR(GetRow(i));
            }
        } else {
            for (size_t i = end - 1; i < begin; i += step) {
                res.PushBackR(GetRow(i));
            }
        }
        return res;
    } else {
        MMatrix res;
        if (begin >= cols_ || end > cols_) {
            throw std::runtime_error("Slice incorrect arguments");
        }
        if (step > 0) {
            for (size_t i = begin; i < end; i += step) {
                res.PushBackC(GetCol(i));
            }
        } else {
            for (size_t i = end - 1; i < begin; i += step) {
                res.PushBackC(GetCol(i));
            }
        }
        return res;
    }
}
// mat({{1, 10, 1}, {2, 5, 2}})
MMatrix MMatrix::operator()(const Slice &row_slice,
                            const Slice &col_slice) const {
    MMatrix res =
        this->operator()(row_slice.Begin(), row_slice.End(), row_slice.Step());
    res = res(col_slice.Begin(), col_slice.End(), col_slice.Step(),
              Orientation::Col);
    return res;
}

MMatrix MMatrix::SliceR(const size_t &begin, const size_t &end,
                        const int &step) const {
    return this->operator()(begin, end, step, Orientation::Row);
}
MMatrix MMatrix::SliceC(const size_t &begin, const size_t &end,
                        const int &step) const {
    return this->operator()(begin, end, step, Orientation::Col);
}
