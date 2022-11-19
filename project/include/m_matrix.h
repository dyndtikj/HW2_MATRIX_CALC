#pragma once

#include <exception>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "m_vector.h"
#include "slice.h"

enum class Orientation { Row = 0, Col = 1 };

class MMatrix {
   private:
    MVector *arr_;
    size_t rows_;
    size_t cols_;
    size_t capacity_;

    void grow();

   public:
    MMatrix();
    // 2
    MMatrix(const size_t &rows, const size_t &cols, const int &val = 0);
    MMatrix(MVector *vectors, const size_t &rows);
    // vector - row by default
    MMatrix(const MVector &vec, Orientation orient = Orientation::Row);
    MMatrix(MMatrix &other);
    MMatrix &operator=(const MMatrix &other);
    MMatrix(const std::initializer_list<std::initializer_list<double>> &list);
    ~MMatrix();

    size_t Rows() const;
    size_t Cols() const;
    size_t Capacity() const;

    void PushBackR(const MVector &row);
    void PushBackC(const MVector &col);

    // 1
    MVector &operator[](const size_t &idx);
    MVector &operator[](const size_t &idx) const;
    MVector GetRow(const size_t &idx) const;
    MVector GetCol(const size_t &idx) const;
    MVector GetDiag() const;

    // 5
    void AddValue(const double &val);
    void SubValue(const double &val);
    void MulValue(const double &val);
    // With choose opportunity rows/cols;
    void AddVector(const MVector &v, size_t idx,
                   Orientation orient = Orientation::Row);
    void SubVector(const MVector &v, size_t idx,
                   Orientation orient = Orientation::Row);

    // 6
    MMatrix GetTransponsed() const;
    MMatrix GetIverted() const;
    MMatrix GetAdded() const;
    double GetMinor(const size_t &row, const size_t &col) const;
    MMatrix DelRowCol(const size_t &row, const size_t &col) const;

    // 7
    double GetDet() const;

    // extra (1)
    MMatrix operator()(const size_t &begin, const size_t &end,
                       const int &step = 1,
                       Orientation orient = Orientation::Row) const;
    // mat({{1, 10, 1}, {2, 5, 2}})
    MMatrix operator()(const Slice &row_slice, const Slice &col_slice) const;
    MMatrix SliceR(const size_t &begin, const size_t &end,
                   const int &step = 1) const;
    MMatrix SliceC(const size_t &begin, const size_t &end,
                   const int &step = 1) const;

    void Print() const;
};

// 3
MMatrix operator+(const MMatrix &left, const MMatrix &right);
MMatrix operator-(const MMatrix &left, const MMatrix &right);
// multiply element to element  -- NOT standart matrix multiplication
// standart mul is in MatMul method
MMatrix operator*(const MMatrix &left, const MMatrix &right);

MMatrix &operator+=(MMatrix &left, const MMatrix &right);
MMatrix &operator-=(MMatrix &left, const MMatrix &right);
MMatrix &operator*=(MMatrix &left, const MMatrix &right);

// 4
MMatrix operator*(const double &left, const MMatrix &right);
MVector operator*(const MMatrix &left, const MVector &right);
MVector operator*(const MVector &left, const MMatrix &right);

MMatrix MatMul(const MMatrix &left, const MMatrix &right);

MVector &operator*=(MVector &left, MMatrix &right);

// 5
MMatrix operator+(const MMatrix &left, const double &right);
MMatrix operator-(const MMatrix &left, const double &right);

MMatrix &operator+=(MMatrix &left, const double &right);
MMatrix &operator-=(MMatrix &left, const double &right);

bool operator==(const MMatrix &l_mat, const MMatrix &r_mat);
bool operator==(const MMatrix &mat,
                std::initializer_list<std::initializer_list<double>> il);
bool CmpMat(const MMatrix &mat,
            std::initializer_list<std::initializer_list<double>> il);