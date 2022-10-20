#pragma once

#include "m_vector.h"
#include <initializer_list>
#include <stdexcept>
#include <exception>
#include <utility>

class MMatrix {
private:
    MVector *arr_;
    size_t raws_;
    size_t cols_;
    size_t capacity_;
private:
    void grow();
public:
    MMatrix();
    MMatrix(const size_t& rows, const size_t& cols, const int& val = 0);
    MMatrix(MMatrix &other);
    MMatrix(const std::initializer_list<std::initializer_list<double>>& list);
    ~MMatrix();

    size_t Rows() const;
    size_t Cols() const;
    size_t Capacity() const;

    MVector &operator[](const size_t& idx);
    MVector &operator[](const size_t& idx) const;
};