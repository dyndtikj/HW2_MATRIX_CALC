#pragma once

#include <initializer_list>
#include <cstddef>
#include <iostream>
#include <exception>

// type of data - double
// not template implementation
class MVector {
private:
    double *arr_;
    size_t size_;
    size_t capacity_;
private:    
    void grow();

public:
    MVector();
    MVector(const size_t& size, const double& val = 0);
    MVector(MVector const &other);
    MVector &operator=(const MVector& other);
    MVector(const std::initializer_list<double>& list);
    ~MVector();

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const double& val);
    void PopBack();
    void Print() const;
    double Front() const;
    double Back() const;

    double const &operator[](const size_t& idx) const;
    double &operator[](const size_t& idx);
};