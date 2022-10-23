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
    // 5
    void AddValue(const double &val);
    void SubValue(const double &val);
    // extra (1)
    // a(1, 10, 2)
    MVector operator()(const size_t& begin, const size_t& end, const int& step = 1) const;

};

// 3
MVector operator+(const MVector &left, const MVector &right);
MVector operator-(const MVector &left, const MVector &right);
MVector operator*(const MVector &left, const MVector &right);

// 5
MVector operator+(const MVector &left, const double &right);
MVector operator-(const MVector &left, const double &right);