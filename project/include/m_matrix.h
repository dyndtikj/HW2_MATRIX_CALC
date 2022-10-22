#pragma once

#include "m_vector.h"
#include <initializer_list>
#include <stdexcept>
#include <exception>
#include <utility>

enum class Orientation{
    Row = 0,
    Col = 1
};

class MMatrix {
private:
    MVector *arr_;
    size_t rows_;
    size_t cols_;
    size_t capacity_;

private:
    void grow();
public:
    MMatrix();
    // 2
    MMatrix(const size_t& rows, const size_t& cols, const int& val = 0);
    MMatrix(MVector *vectors, const size_t& rows);
    // vector - row by default
    MMatrix(const MVector &vec, Orientation orient = Orientation::Row);
    MMatrix(MMatrix &other);
    MMatrix(const std::initializer_list<std::initializer_list<double>>& list);
    ~MMatrix();

    size_t Rows() const;
    size_t Cols() const;
    size_t Capacity() const;

    // 1
    MVector &operator[](const size_t& idx);
    MVector &operator[](const size_t& idx) const;
    MVector GetRow(const size_t& idx) const;
    MVector GetCol(const size_t& idx) const;
    MVector GetDiag() const;

    //5
    void AddValue(const double & val);
    void SubValue(const double & val);
    // With choose opportunity rows/cols;
    void AddVector(const MVector &v, size_t idx,
                            Orientation orient = Orientation::Row);
    void SubVector(const MVector &v, size_t idx,
                            Orientation orient = Orientation::Row);
    // 6
    MMatrix GetTransponsed() const;
    MMatrix GetIverted() const;
    MMatrix GetAdded() const;
    double GetMinor(const size_t& row, const size_t& col) const;
    MMatrix DelRowCol(const size_t& row, const size_t& col) const;

    // 7
    double GetDet() const;

    void Print() const;
};

// 3
MMatrix operator+(const MMatrix &left, const MMatrix &right);
MMatrix operator-(const MMatrix &left, const MMatrix &right);
// multiply element to element  -- NOT standart matrix multiplication
// standart mul is in MatMul method
MMatrix operator*(const MMatrix &left, const MMatrix &right);

// 4
MMatrix operator*(const double &left, const MMatrix &right);
MVector operator*(const MVector &left, const MMatrix &right);
MVector operator*(const MMatrix &left, const MVector &right);
MMatrix MatMul(const MMatrix &left, const MMatrix &right);

//5
MMatrix operator+(const MMatrix &left, const double &right);
MMatrix operator-(const MMatrix &left, const double &right);