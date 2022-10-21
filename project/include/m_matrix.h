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
};